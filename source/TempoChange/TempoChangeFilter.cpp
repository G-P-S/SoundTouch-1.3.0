//-------------------------------------------------------------------------------------------
// TempoChangeFilter.cpp
//-------------------------------------------------------------------------------------------
// 20041213JY	-	Updated sample rate to optionally disable forwarding quality notification
//					and copy buffer with correct striding for vmr.  This mode is activated
//					by TODO: 
//					and used for AdobeHDV's preview before capture because the
//					MainConcept Decoder honors VMR qualty messages and ends up at only 5 fps.
//-------------------------------------------------------------------------------------------
#include <windows.h>
#include <streams.h>
#include <bdatypes.h>

#include "TempoChangeFilter.h"
#include "TempoChangeInputPin.h"
#include "TempoChangeOutputPin.h"
#include <initguid.h>
#include "ids.h"


#include <time.h>
#include <stdio.h>

#define FILTER_NAME MAKE_FILTER_NAME(L"TempoChange")

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
const AMOVIESETUP_MEDIATYPE sudInputPinTypes =
{
	&MEDIATYPE_Video, 
	&MEDIASUBTYPE_NULL
};

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
const AMOVIESETUP_MEDIATYPE sudOutputPinTypes =
{
	&MEDIATYPE_Video,
	&MEDIASUBTYPE_NULL
};

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
const AMOVIESETUP_PIN sudpPins[] =
{
	{ L"Input", 			// Pin string name
	  FALSE,				// Is it rendered?
	  FALSE,				// Is it an output?
	  FALSE,				// Okay to have no input pins?
	  FALSE,				// Can have many input pins?
	  &CLSID_NULL,			// Connects to filter
	  NULL, 				// Connects to pin
	  1,					// Number of types
	  &sudInputPinTypes 	// Pin information
	},
	{ L"Output",			// Pin string name
	  FALSE,				// Is it rendered?
	  TRUE, 				// Is it an output?
	  FALSE,				// Okay to have no output pins?
	  FALSE,				// Can have many output pins?
	  &CLSID_NULL,			// Connects to filter
	  NULL, 				// Connects to pin
	  1,					// Number of types
	  &sudOutputPinTypes	// Pin information
	}
};

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
const AMOVIESETUP_FILTER sudFilter =
{
	&CLSID_CFTempoChange,	// Filter CLSID
	FILTER_NAME, 			// String name
	MERIT_DO_NOT_USE,		// Filter merit
	2,						// Number of pins
	sudpPins				// Pin information
};

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
CFactoryTemplate g_Templates[]=
{	{ FILTER_NAME,
	  &CLSID_CFTempoChange,
	  CTempoChangeFilter::CreateInstance,
	  NULL,
	  &sudFilter 
	}
};

int g_cTemplates = sizeof(g_Templates)/sizeof(g_Templates[0]);

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
CUnknown * WINAPI CTempoChangeFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	CTempoChangeFilter *pFilter = new CTempoChangeFilter(punk, phr);
	if(pFilter == NULL)
	{
		*phr = E_OUTOFMEMORY;
	}

	return (CUnknown*)pFilter;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
CTempoChangeFilter::CTempoChangeFilter(IUnknown* pUnknown, HRESULT* pHR) :
	CBaseFilter(NAME("CFTempoChange"), pUnknown, &m_lock, CLSID_CFTempoChange)
{
	m_TempoDelta = 0.0; // -4.0
	m_lastMediaTime = 0;
	m_lastVideoMediaTime = 0;
	m_lastRefTime = 0;
	m_lastVideoRefTime = 0;

	m_SoundTouch.setSampleRate(48000);
	m_SoundTouch.setChannels(2);

	m_SoundTouch.setTempoChange(m_TempoDelta);
	m_SoundTouch.setPitchSemiTones(0);
	m_SoundTouch.setRateChange(0);

	m_SoundTouch.setSetting(SETTING_USE_QUICKSEEK, 0);
	m_SoundTouch.setSetting(SETTING_USE_AA_FILTER, 1);

	m_pInputPin = new CTempoChangeInputPin(this, pHR);
	if(m_pInputPin == 0) 
	{
		*pHR = E_OUTOFMEMORY;
	}
	m_pOutputPin = new CTempoChangeOutputPin(this, pHR);
	if(m_pOutputPin == 0)
	{
		*pHR = E_OUTOFMEMORY;
	}
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
CTempoChangeFilter::~CTempoChangeFilter()
{
	delete m_pInputPin;
	delete m_pOutputPin;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
int	CTempoChangeFilter::GetPinCount()
{
	return 2;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
CBasePin* CTempoChangeFilter::GetPin(int n)
{
	if(n == 0) return m_pInputPin;
	if(n == 1) return m_pOutputPin;
	return 0;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeFilter::Run(REFERENCE_TIME tStart)
{
	DbgLog((LOG_TRACE, 4, TEXT("CTempoChangeFilter::Run")));

	CAutoLock lock(&m_lock);
	HR_BAIL(CBaseFilter::Run(tStart));
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeFilter::Stop()
{
	CAutoLock lock(&m_lock);
	if(m_pInputPin && m_pInputPin->IsConnected()) m_pInputPin->Inactive();
	CAutoLock lock2(&m_receiveLock);
	if(m_pOutputPin && m_pOutputPin->IsConnected()) m_pOutputPin->Inactive();
	m_State = State_Stopped;

	m_lastMediaTime = 0;
	m_lastVideoMediaTime = 0;
	m_lastRefTime = 0;
	m_lastVideoRefTime = 0;

	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeFilter::Pause()
{
	DbgLog((LOG_TRACE, 4, TEXT("CTempoChangeFilter::Pause")));

	CAutoLock lock(&m_lock);

	HR_BAIL(CBaseFilter::Pause());
	return S_OK;
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeFilter::SetTempoDelta(float newTempoDelta)
{
	CAutoLock lock(&m_lock);
	m_TempoDelta = newTempoDelta;
	m_SoundTouch.setTempoChange(m_TempoDelta);
	return S_OK;
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeFilter::SetRateDelta(float newRateDelta)
{
	CAutoLock lock(&m_lock);
	m_RateDelta = newRateDelta;
	m_SoundTouch.setRateChange(m_RateDelta);
	return S_OK;
}



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeFilter::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{
	CAutoLock lock(&m_lock);
	if(riid == IID_ICFTempoChangeStats)
	{
		HRESULT hr = GetInterface((ICFTempoChangeStats*)this, ppv);
		return hr;
	}
	return CBaseFilter::NonDelegatingQueryInterface(riid, ppv);
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeFilter::Reconnect()
{ 
	if(m_pOutputPin->IsConnected())
	{
		m_pGraph->Reconnect(m_pOutputPin);
	}
	return S_OK;
}

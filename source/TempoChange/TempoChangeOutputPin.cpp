//-------------------------------------------------------------------------------------------
// TempoChangeOutputPin.cpp
//-------------------------------------------------------------------------------------------
#include <streams.h>
#include "TempoChangeFilter.h"
#include "TempoChangeInputPin.h"
#include "TempoChangeOutputPin.h"
#include <atlbase.h>
#include <Dvdmedia.h>

#define PIN_NAME	NAME("CFTempoChange_OutputPin")

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
CTempoChangeOutputPin::CTempoChangeOutputPin(CTempoChangeFilter* pFilter, HRESULT* pHR) :
	CBaseOutputPin(PIN_NAME, pFilter, &pFilter->m_lock, pHR, L"Output"),
	m_pOutputQueue(0)
{
	m_outputWidth = m_outputHeight = 0;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
CTempoChangeOutputPin::~CTempoChangeOutputPin()
{
	if(m_pOutputQueue)
	{
		delete m_pOutputQueue;
		m_pOutputQueue = 0;
	}
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::CheckMediaType(const CMediaType *pmt)
{
	CAutoLock lock(m_pLock);

	const GUID* pType = pmt->Type();
	const GUID* pSubType = pmt->Subtype();

	DbgLog((LOG_TRACE, 2, 
		TEXT("CTempoChangeOutputPin::CheckMediaType(type=%s, subType=%s)"),
		GuidNames[*pType], GuidNames[*pSubType]));

	// ask upstream filter if this is okay
	IPin* pConnected = ((CTempoChangeFilter*)m_pFilter)->m_pInputPin->GetConnectedPin();
	if(pConnected == 0) return E_FAIL;		// must connect input pin first
    HR_BAIL(pConnected->QueryAccept(pmt));

	return S_OK;
}

#define SET_IF_LESS(a, b, f)	if(a->f < b.f) a->f = b.f

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::DecideBufferSize(IMemAllocator * pAlloc, 
												  ALLOCATOR_PROPERTIES * pProps)
{
	CAutoLock lock(m_pLock);
	DbgLog((LOG_TRACE, 2, TEXT("CTempoChangeOutputPin::DecideBufferSize()")));

	if(pAlloc == 0) return E_POINTER;
	if(pProps == 0) return E_POINTER;

	// Use Input Pin's allocator's properties
	IPin* pConnected = ((CTempoChangeFilter*)m_pFilter)->m_pInputPin->GetConnectedPin();
	if(pConnected == 0) return E_FAIL;		

	ALLOCATOR_PROPERTIES inputProps;
	IMemAllocator* pInputAlloc = ((CTempoChangeFilter*)m_pFilter)->m_pInputPin->Allocator();
	pInputAlloc->GetProperties(&inputProps);

	SET_IF_LESS(pProps, inputProps, cBuffers);
	SET_IF_LESS(pProps, inputProps, cbBuffer);
	SET_IF_LESS(pProps, inputProps, cbPrefix);
	SET_IF_LESS(pProps, inputProps, cbAlign);

	CTempoChangeFilter* pFilter = (CTempoChangeFilter*)m_pFilter;
	
	ALLOCATOR_PROPERTIES actualProps;
	HRESULT hr = pAlloc->SetProperties(pProps, &actualProps);
	if(FAILED(hr))
	{
		DbgLog((LOG_ERROR, 1, TEXT("CTempoChangeOutputPin::DecideBufferSize() SetProperties failed 0x%08x"), hr));
		return hr;
	}

	if(actualProps.cBuffers < pProps->cBuffers || actualProps.cbBuffer < pProps->cbBuffer)
	{
		DbgLog((LOG_ERROR, 1, TEXT("CTempoChangeOutputPin::DecideBufferSize() actual properties don't match.")));
		return E_FAIL;
	}
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::GetMediaType(int iPosition, CMediaType *pmt)
{
	if(iPosition < 0) return E_INVALIDARG;

	// ask upstream filter if this is okay
	CAutoLock lock(m_pLock);
	IPin* pConnected = ((CTempoChangeFilter*)m_pFilter)->m_pInputPin->GetConnectedPin();
	if(pConnected == 0) return E_FAIL;		// must connect input pin first

	// ALT: enum media types once and then return info from stored MT array

	CComPtr<IEnumMediaTypes> enumMT;
	HR_BAIL(pConnected->EnumMediaTypes(&enumMT));
	for(int count = 0;; count++)
	{
		AM_MEDIA_TYPE* pMT;
		HRESULT hr = enumMT->Next(1, &pMT, 0);
		if(hr == S_FALSE) return VFW_S_NO_MORE_ITEMS;
		if(FAILED(hr)) return hr;
		if(count == iPosition)
		{
			DWORD avgframetime = 0;
			GUID FType;
			CMediaType MT(*pMT);

			FType = *MT.FormatType();
			

			if(FType == FORMAT_VideoInfo)
			{
				VIDEOINFO* pVI = (VIDEOINFO*)MT.Format();
				if(pVI)
				{
					avgframetime = pVI->AvgTimePerFrame;
					avgframetime = (DWORD)((double)avgframetime / (100.0 + ((CTempoChangeFilter*)m_pFilter)->m_TempoDelta) * 100);
					pVI->AvgTimePerFrame = avgframetime;
				}
			}
			else if(FType == FORMAT_VideoInfo2)
			{
				VIDEOINFOHEADER2* pVI = (VIDEOINFOHEADER2*)MT.Format();
				if(pVI)
				{
					avgframetime = pVI->AvgTimePerFrame;
					avgframetime = (DWORD)((double)avgframetime / (100.0 + ((CTempoChangeFilter*)m_pFilter)->m_TempoDelta) * 100);
					pVI->AvgTimePerFrame = avgframetime;
				}
			}

			pmt->Set(MT);
			DeleteMediaType(pMT);
			return S_OK;
		}
		DeleteMediaType(pMT);
	}
}

#include <stdio.h>

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeOutputPin::Notify(IBaseFilter* pSender, Quality q)
{
	// pass upstream
	DbgLog((LOG_TRACE, 4, TEXT("CTempoChangeOutputPin::Notify() q = %u"), q));
	CAutoLock lock(m_pLock);
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeOutputPin::QueryAccept(const AM_MEDIA_TYPE* pMT)
{
	HRESULT hr = CBaseOutputPin::QueryAccept(pMT);
	return hr;
}

//-------------------------------------------------------------------------------------------
// Active
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::Active()
{
    CAutoLock lock(m_pLock);
	HRESULT hr = S_OK;

    if(m_Connected == 0) return S_OK;

	CTempoChangeFilter* pFilter = (CTempoChangeFilter*)m_pFilter;
    hr = CBaseOutputPin::Active();
    return S_OK;
}

//-------------------------------------------------------------------------------------------
// Inactive
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::Inactive()
{
    CAutoLock lock(m_pLock);

    if(m_pOutputQueue)
    {
		DbgLog((LOG_TRACE, 1, TEXT("CTempoChangeOutputPin::Inactive: Waiting for output queue to empty")));
		int nQueueCount = m_pOutputQueue->GetCount();
		while (nQueueCount > 0)
		{
			DbgLog((LOG_TRACE, 1, TEXT("CTempoChangeOutputPin::Inactive: Output queue count: %d"),
					m_pOutputQueue->GetCount()));
			Sleep(10);
			nQueueCount = m_pOutputQueue->GetCount();
		}
		DbgLog((LOG_TRACE, 1, TEXT("CTempoChangeOutputPin::Inactive: Output queue count: %d"),
				m_pOutputQueue->GetCount()));

		DbgLog((LOG_TRACE, 1, TEXT("CTempoChangeOutputPin::Inactive: Deleting output queue")));
        delete m_pOutputQueue;
        m_pOutputQueue = 0;
    }

    CBaseOutputPin::Inactive();
    return S_OK;
}

//-------------------------------------------------------------------------------------------
// Deliver
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::Deliver(IMediaSample *pMediaSample)
{
	if(pMediaSample == 0) return E_INVALIDARG;
    
	if(m_pOutputQueue == 0) 
	{
		HR_BAIL(CBaseOutputPin::Deliver(pMediaSample));
		return S_OK;
	}

    pMediaSample->AddRef();
    HR_BAIL(m_pOutputQueue->Receive(pMediaSample));

	DbgLog((LOG_TRACE, 1,
			TEXT("CTempoChangeOutputPin::Deliver: Queue count: %d, idle: %d, flushing: %d, terminated: %d, hr: 0x%08X"),
			m_pOutputQueue->GetCount(), m_pOutputQueue->IsIdle(), m_pOutputQueue->IsFlushing(), m_pOutputQueue->IsTerminated(), m_pOutputQueue->HR()));

	return S_OK;
}

//-------------------------------------------------------------------------------------------
// DeliverEndOfStream
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::DeliverEndOfStream()
{
    if(m_pOutputQueue == 0) 
	{
		HR_BAIL(CBaseOutputPin::DeliverEndOfStream());
		return S_OK;
	}

	DbgLog((LOG_TRACE, 1, TEXT("CTempoChangeOutputPin::DeliverEndOfStream: Calling EOS")));

	m_pOutputQueue->EOS();
    return S_OK;
}

//-------------------------------------------------------------------------------------------
// DeliverBeginFlush
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::DeliverBeginFlush()
{
    if(m_pOutputQueue == 0) 
	{
		HR_BAIL(CBaseOutputPin::DeliverBeginFlush());
		return S_OK;
	}

	DbgLog((LOG_TRACE, 1, TEXT("CTempoChangeOutputPin::DeliverBeginFlush: Calling BeginFlush")));

	m_pOutputQueue->BeginFlush();
    return S_OK;

}

//-------------------------------------------------------------------------------------------
// DeliverEndFlush
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::DeliverEndFlush()
{
    if(m_pOutputQueue == 0) 
	{
		HR_BAIL(CBaseOutputPin::DeliverEndFlush());
		return S_OK;
	}

	DbgLog((LOG_TRACE, 1, TEXT("CTempoChangeOutputPin::DeliverEndFlush: Calling EndFlush")));

	m_pOutputQueue->EndFlush();
	return S_OK;
}

//-------------------------------------------------------------------------------------------
// DeliverNewSegment
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeOutputPin::DeliverNewSegment(REFERENCE_TIME tStart, REFERENCE_TIME tStop,  
											double dRate)
{
    if(m_pOutputQueue == 0) 
	{
		HR_BAIL(CBaseOutputPin::DeliverNewSegment(tStart, tStop, dRate));
		return S_OK;
	}

    m_pOutputQueue->NewSegment(tStart, tStop, dRate);
	return S_OK;
}

//-------------------------------------------------------------------------------------------
// GetCount
//-------------------------------------------------------------------------------------------
int CTempoChangeOutputPin::GetCount()
{
	int nOutputCount = 0;

	if (m_pOutputQueue)
	{
		nOutputCount = m_pOutputQueue->GetCount();
	}

	return nOutputCount;
}

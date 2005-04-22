//-------------------------------------------------------------------------------------------
// TempoChangeFilter.h: interface for the CTempoChangeFilter class.
//-------------------------------------------------------------------------------------------
#pragma once

class CTempoChangeFilter;
class CTempoChangeInputPin;
class CTempoChangeOutputPin;

//#include <stdexcept.h>
#include <stdio.h>
#include "SoundTouch.h"
#include "BPMDetect.h"

using namespace soundtouch;
//using namespace std;

#include "TempoChange_i.h"

#define HR_BAIL(x)	\
	{ HRESULT _hr = x; if(FAILED(_hr)) { \
		DbgLog((LOG_TRACE, 1, TEXT(" %s(%d) - " #x " :: Failed - 0x%08x"), __FILE__, __LINE__, _hr)); return _hr; }}

#define HR_WIN32(x) if(x == FALSE) { \
	HRESULT _hr = HRESULT_FROM_WIN32(GetLastError());	\
	DbgLog((LOG_TRACE, 1, TEXT(#x " failed - 0x%08x"), _hr)); return _hr;  }

//-------------------------------------------------------------------------------------------
// CTempoChangeFilter 
//-------------------------------------------------------------------------------------------
class CTempoChangeFilter : public CBaseFilter, public ICFTempoChangeStats
{
public:
	CTempoChangeFilter(IUnknown* pUnknown, HRESULT* pHR);
	virtual ~CTempoChangeFilter();

public:
	int			GetPinCount();
	CBasePin*	GetPin(int n);

public:
	STDMETHODIMP Run(REFERENCE_TIME tStart);
	STDMETHODIMP Stop();
	STDMETHODIMP Pause();

public:
	DECLARE_IUNKNOWN;
	STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv);
	HRESULT Reconnect();

public:
	static CUnknown *WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

public:	// ICFTempoChangeStats
	STDMETHODIMP SetTempoDelta(float newTempoDelta);
	STDMETHODIMP SetRateDelta(float newRateDelta);

public:
	CCritSec				m_lock;
	CCritSec				m_receiveLock;
	CTempoChangeInputPin*	m_pInputPin;
	CTempoChangeOutputPin*	m_pOutputPin;

public:
	float		m_TempoDelta;
	float		m_RateDelta;

	bool		m_remove_pulldown;
	int			m_pulldown_framecount;

    SoundTouch	m_SoundTouch;
	LONGLONG	m_lastMediaTime;
	LONGLONG	m_lastVideoMediaTime;
	REFERENCE_TIME m_lastRefTime;
	REFERENCE_TIME m_lastVideoRefTime;
};


//-------------------------------------------------------------------------------------------
// TempoChangeOutputPin.h
//-------------------------------------------------------------------------------------------
#pragma once

class CTempoChangeFilter;

//-------------------------------------------------------------------------------------------
// CSROutputQueue	- Wrap the COutputQueue class to expose protected variables
//-------------------------------------------------------------------------------------------
class CSROutputQueue : public COutputQueue
{
public:
	CSROutputQueue(IPin *pInputPin, HRESULT *phr, DWORD threadPriority, DWORD queueSize) :
		COutputQueue(pInputPin, phr, FALSE, TRUE, 1, FALSE, queueSize, threadPriority)
	{
	}

	int GetCount()
	{
		return m_List->GetCount();
	}

	BOOL IsFlushing()
	{
		return m_bFlushing;
	}

	BOOL IsTerminated()
	{
		return m_bTerminate;
	}

	HRESULT HR()
	{
		return m_hr;
	}

	// Override reset to fix bug per 
	// http://groups-beta.google.com/group/microsoft.public.win32.programmer.directx.video/browse_frm/thread/6734ccb4cdcbf80c
	void Reset()
	{
		if (!IsQueued()) {
			m_hr = S_OK;
		} else {
			{
				CAutoLock lck(this);
				QueueSample(RESET_PACKET);
				NotifyThread();
			}
			m_evFlushComplete.Wait();
		}
	}
};

//-------------------------------------------------------------------------------------------
// CTempoChangeOutputPin
//-------------------------------------------------------------------------------------------
class CTempoChangeOutputPin : public CBaseOutputPin 
{
public:
	CTempoChangeOutputPin(CTempoChangeFilter* pFilter, HRESULT* pHR);
	virtual ~CTempoChangeOutputPin();

public:
	HRESULT CheckMediaType(const CMediaType *pmt);
	HRESULT DecideBufferSize(IMemAllocator * pAlloc, ALLOCATOR_PROPERTIES * ppropInputRequest);
	HRESULT GetMediaType(int iPosition, CMediaType *pmt);

	STDMETHODIMP Notify(IBaseFilter* pSender, Quality q);
	IMemAllocator* GetAllocator() { return m_pAllocator; }

	STDMETHODIMP QueryAccept(const AM_MEDIA_TYPE* pMT);

public:
	HRESULT Active();
	HRESULT Inactive();
	HRESULT Deliver(IMediaSample *pMediaSample);
	HRESULT DeliverEndOfStream();
	HRESULT DeliverBeginFlush();
	HRESULT DeliverEndFlush();
	HRESULT DeliverNewSegment(REFERENCE_TIME tStart, REFERENCE_TIME tStop, double dRate);

public:
	int m_outputWidth;
	int m_outputHeight;

protected:
	CSROutputQueue*	m_pOutputQueue;

public:
	int GetCount();

};


//-------------------------------------------------------------------------------------------
// TempoChangeInputPin.h
//-------------------------------------------------------------------------------------------
#pragma once

class CTempoChangeFilter;

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
class CTempoChangeInputPin : public CBaseInputPin
{
public:
	CTempoChangeInputPin(CTempoChangeFilter* pFilter, HRESULT* pHR);
	virtual ~CTempoChangeInputPin();

public:
	HRESULT CheckMediaType(const CMediaType *pmt);
	HRESULT GetMediaType(int iPosition, CMediaType *pmt);
	HRESULT CompleteConnect(IPin *pReceivePin);
	HRESULT BreakConnect();

	STDMETHODIMP Receive(IMediaSample* pSample);
	STDMETHODIMP BeginFlush();
	STDMETHODIMP EndFlush();

	STDMETHODIMP EndOfStream();
	STDMETHODIMP Notify(IBaseFilter* pSender, Quality q);

	HRESULT InitializeOutputSample(IMediaSample *pSample, IMediaSample **ppOutSample);
	HRESULT CopyInputSampleToOutputSample(IMediaSample* pInputSample, IMediaSample** ppOutputSample);

	IPin*			GetConnectedPin() { return m_Connected; }
	IMemAllocator*	Allocator() { return m_pAllocator; }

public:
	BOOL m_isRGBMediaType;
};

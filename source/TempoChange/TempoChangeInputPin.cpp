//-------------------------------------------------------------------------------------------
// TempoChangeInputPin.cpp
//-------------------------------------------------------------------------------------------
#include <streams.h>
#include <Dvdmedia.h>
#include "TempoChangeInputPin.h"
#include "TempoChangeOutputPin.h"
#include "TempoChangeFilter.h"
#include <atlbase.h>

#define PIN_NAME	NAME("CFTempoChange_InputPin")

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
CTempoChangeInputPin::CTempoChangeInputPin(CTempoChangeFilter* pFilter, HRESULT* pHR) :
	 CBaseInputPin(PIN_NAME, pFilter, &pFilter->m_lock, pHR, L"Input")
{
	DbgLog((LOG_TRACE, 2, TEXT("CTempoChangeInputPin::CTempoChangeInputPin(), this = 0x%08x"), this));
	m_isRGBMediaType = FALSE;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
CTempoChangeInputPin::~CTempoChangeInputPin()
{

}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeInputPin::CheckMediaType(const CMediaType *pmt)
{
	CAutoLock lock(m_pLock);

	const GUID* pType = pmt->Type();
	const GUID* pSubType = pmt->Subtype();

	DbgLog((LOG_TRACE, 2, 
		TEXT("CTempoChangeInputPin::CheckMediaType(type=%s, subType=%s), this = 0x%08x"),
		GuidNames[*pType], GuidNames[*pSubType], this));
	
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeInputPin::GetMediaType(int iPosition, CMediaType *pmt)
{
	DbgLog((LOG_TRACE, 2, TEXT("CTempoChangeInputPin::GetMediaType(), this = 0x%08x"), this));

	if(iPosition < 0) return E_INVALIDARG;
	if(iPosition > 0) return VFW_S_NO_MORE_ITEMS;

	pmt->Set(m_mt);

#if 0
    pmt->SetType(&MEDIATYPE_Stream);
 	pmt->SetSubtype(&MEDIASUBTYPE_MPEG2_TRANSPORT);
    pmt->SetFormatType(&FORMAT_None);
    pmt->SetTemporalCompression(FALSE);
    pmt->SetSampleSize(1);
#endif
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeInputPin::CompleteConnect(IPin *pReceivePin)
{
	DbgLog((LOG_TRACE, 2, TEXT("CTempoChangeInputPin::CompleteConnect(pin=0x%08X), this = 0x%08x"), pReceivePin, this));
	CAutoLock lock(m_pLock);
	if(pReceivePin == 0) return E_POINTER;

	HRESULT hr = CBaseInputPin::CompleteConnect(pReceivePin);
	if(FAILED(hr)) 
	{
		return hr;
	}
	((CTempoChangeFilter*)m_pFilter)->Reconnect();

	const GUID* pSubType = m_mt.Subtype();
	if(*pSubType == MEDIASUBTYPE_RGB1 || 
		*pSubType == MEDIASUBTYPE_RGB4 || 
		*pSubType == MEDIASUBTYPE_RGB8 || 
		*pSubType == MEDIASUBTYPE_RGB565 || 
		*pSubType == MEDIASUBTYPE_RGB555 || 
		*pSubType == MEDIASUBTYPE_RGB24 || 
		*pSubType == MEDIASUBTYPE_RGB32)
	{
		m_isRGBMediaType = TRUE;
	}
	else
	{
		m_isRGBMediaType = FALSE;
	}
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeInputPin::BreakConnect()
{
	DbgLog((LOG_TRACE, 2, TEXT("CTempoChangeInputPin::BreakConnect(), this = 0x%08x"), this));
	CAutoLock lock(m_pLock);
	HRESULT hr = CBaseInputPin::BreakConnect();
	if(FAILED(hr))
	{
		return hr;
	}
	// TODO:
	return S_OK;
}

// COPY_SAMPLES	-	copy input to output samples ... required when writing to avi mux filter

#define COPY_SAMPLES

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeInputPin::Receive(IMediaSample* pSample)
{
	DbgLog((LOG_TRACE, 2, TEXT("CTempoChangeInputPin::Receive(pSample = 0x%08x), this = 0x%08x"), pSample, this));
	if(pSample == 0) return E_POINTER;

	CTempoChangeFilter* pFilter = (CTempoChangeFilter*)m_pFilter;

	CAutoLock lock(&pFilter->m_receiveLock);
	HR_BAIL(CBaseInputPin::Receive(pSample));

	// This Sleep help item playback from using 100% of the CPU (sometimes glitching audio.)
	//TODO : make this interface controlable.
	//Sleep(5); 

	// TODO: make copy of sample for avi mux ... needs copy for alignment padding?
#ifdef COPY_SAMPLES
	CComPtr<IMediaSample> outputSample;
	HR_BAIL(CopyInputSampleToOutputSample(pSample, &outputSample));
	HR_BAIL(pFilter->m_pOutputPin->Deliver(outputSample));
#else
	HR_BAIL(pFilter->m_pOutputPin->Deliver(pSample));
#endif
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeInputPin::BeginFlush()
{
	DbgLog((LOG_TRACE, 2, TEXT("CTempoChangeInputPin::BeginFlush(), this = 0x%08x"), this));
	CAutoLock lock(m_pLock);
	HR_BAIL(CBaseInputPin::BeginFlush());
	// TODO:
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeInputPin::EndFlush()
{
	DbgLog((LOG_TRACE, 2, TEXT("CTempoChangeInputPin::EndFlush(), this = 0x%08x"), this));
	CAutoLock lock(m_pLock);
	HR_BAIL(CBaseInputPin::EndFlush());
	// TODO:
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeInputPin::EndOfStream(void)
{
	DbgLog((LOG_TRACE, 4, TEXT("CTempoChangeInputPin::EndOfStream()")));
	// just deliver down stream right now
	CAutoLock lock(m_pLock);
	HR_BAIL(((CTempoChangeFilter*)m_pFilter)->m_pOutputPin->DeliverEndOfStream());
	return S_OK;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
STDMETHODIMP CTempoChangeInputPin::Notify(IBaseFilter* pSender, Quality q)
{
	// pass upstream
	DbgLog((LOG_TRACE, 4, TEXT("CTempoChangeInputPin::Notify() q = %u"), q));
	CAutoLock lock(m_pLock);
	HR_BAIL(PassNotify(q));
	return S_OK;
}

//-------------------------------------------------------------------------------------------
// InitializeOutputSample  - from transfrm.cpp
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeInputPin::InitializeOutputSample(IMediaSample *pSample, IMediaSample **ppOutSample)
{
	CTempoChangeOutputPin* pOutputPin = ((CTempoChangeFilter*)m_pFilter)->m_pOutputPin;
    IMediaSample *pOutSample;
	BOOL m_bSampleSkipped = FALSE;
    // default - times are the same

    AM_SAMPLE2_PROPERTIES * const pProps = SampleProps();
    DWORD dwFlags = m_bSampleSkipped ? AM_GBF_PREVFRAMESKIPPED : 0;

    // This will prevent the image renderer from switching us to DirectDraw
    // when we can't do it without skipping frames because we're not on a
    // keyframe.  If it really has to switch us, it still will, but then we
    // will have to wait for the next keyframe
    if (!(pProps->dwSampleFlags & AM_SAMPLE_SPLICEPOINT)) {
	dwFlags |= AM_GBF_NOTASYNCPOINT;
    }

	IMemAllocator* pAllocator = pOutputPin->GetAllocator();
    ASSERT(pAllocator);
    if(pAllocator == 0) return E_FAIL;
	HRESULT hr = pAllocator->GetBuffer(
             &pOutSample
             , pProps->dwSampleFlags & AM_SAMPLE_TIMEVALID ?
                   &pProps->tStart : NULL
             , pProps->dwSampleFlags & AM_SAMPLE_STOPVALID ?
                   &pProps->tStop : NULL
             , dwFlags
         );
    *ppOutSample = pOutSample;
    if (FAILED(hr)) {
        return hr;
    }

    ASSERT(pOutSample);
    IMediaSample2 *pOutSample2;
    if (SUCCEEDED(pOutSample->QueryInterface(IID_IMediaSample2,
                                             (void **)&pOutSample2))) {
        /*  Modify it */
        AM_SAMPLE2_PROPERTIES OutProps;
        EXECUTE_ASSERT(SUCCEEDED(pOutSample2->GetProperties(
            FIELD_OFFSET(AM_SAMPLE2_PROPERTIES, tStart), (PBYTE)&OutProps)
        ));
        OutProps.dwTypeSpecificFlags = pProps->dwTypeSpecificFlags;
        OutProps.dwSampleFlags =
            (OutProps.dwSampleFlags & AM_SAMPLE_TYPECHANGED) |
            (pProps->dwSampleFlags & ~AM_SAMPLE_TYPECHANGED);
        OutProps.tStart = pProps->tStart;
        OutProps.tStop  = pProps->tStop;
        OutProps.cbData = FIELD_OFFSET(AM_SAMPLE2_PROPERTIES, dwStreamId);
        hr = pOutSample2->SetProperties(
            FIELD_OFFSET(AM_SAMPLE2_PROPERTIES, dwStreamId),
            (PBYTE)&OutProps
        );
        if (pProps->dwSampleFlags & AM_SAMPLE_DATADISCONTINUITY) {
            m_bSampleSkipped = FALSE;
        }
        pOutSample2->Release();
    } else {
        if (pProps->dwSampleFlags & AM_SAMPLE_TIMEVALID) {
            pOutSample->SetTime(&pProps->tStart,
                                &pProps->tStop);
        }
        if (pProps->dwSampleFlags & AM_SAMPLE_SPLICEPOINT) {
            pOutSample->SetSyncPoint(TRUE);
        }
        if (pProps->dwSampleFlags & AM_SAMPLE_DATADISCONTINUITY) {
            pOutSample->SetDiscontinuity(TRUE);
            m_bSampleSkipped = FALSE;
        }
        // Copy the media times

        LONGLONG MediaStart, MediaEnd;
        if (pSample->GetMediaTime(&MediaStart,&MediaEnd) == NOERROR) {
            pOutSample->SetMediaTime(&MediaStart,&MediaEnd);
        }
    }
    return S_OK;
}

//-------------------------------------------------------------------------------------------
// ExtractFrameSize
//-------------------------------------------------------------------------------------------
BOOL ExtractFrameSize(const CMediaType& mt, int& rWidth, int& rHeight, int& rBPP)
{
	BOOL extractedFrameSize = FALSE;
	if(*mt.FormatType() == FORMAT_VideoInfo)
	{
		VIDEOINFO* pVI = (VIDEOINFO*)mt.Format();
		if(pVI)
		{
			extractedFrameSize = TRUE;
			rWidth = pVI->bmiHeader.biWidth;
			rHeight = pVI->bmiHeader.biHeight;
			rBPP = pVI->bmiHeader.biBitCount;
		}
	}
	else if(*mt.FormatType() == FORMAT_VideoInfo2)
	{
		VIDEOINFOHEADER2* pVI = (VIDEOINFOHEADER2*)mt.Format();
		if(pVI)
		{
			extractedFrameSize = TRUE;
			rWidth = pVI->bmiHeader.biWidth;
			rHeight = pVI->bmiHeader.biHeight;
			rBPP = pVI->bmiHeader.biBitCount;
		}
	}
	return extractedFrameSize;
}


//-------------------------------------------------------------------------------------------
// ExtractFrameSize
//-------------------------------------------------------------------------------------------
BOOL GetType(const CMediaType& mt, DWORD &avgframetime )
{
	BOOL videotype = FALSE;
	GUID FType = *mt.FormatType();
//	GUID FTypeNULL = {0};
	avgframetime = 0;

	if(FType == FORMAT_VideoInfo)
	{
		VIDEOINFO* pVI = (VIDEOINFO*)mt.Format();
		if(pVI)
		{
			videotype = TRUE;
			avgframetime = pVI->AvgTimePerFrame;
		}
	}
	else if(FType == FORMAT_VideoInfo2)
	{
		VIDEOINFOHEADER2* pVI = (VIDEOINFOHEADER2*)mt.Format();
		if(pVI)
		{
			videotype = TRUE;
			avgframetime = pVI->AvgTimePerFrame;
		}
	}
	return !videotype;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
HRESULT CTempoChangeInputPin::CopyInputSampleToOutputSample(IMediaSample* pInputSample, 
														 IMediaSample** ppOutputSample)
{
	HR_BAIL(InitializeOutputSample(pInputSample, ppOutputSample));

	// Copy input buffer to output buffer
	IMediaSample* pOutputSample = *ppOutputSample;
	BYTE* pIn = 0, *pOut = 0;
	HR_BAIL(pInputSample->GetPointer(&pIn));
	HR_BAIL(pOutputSample->GetPointer(&pOut));
	DWORD length = pInputSample->GetActualDataLength();
	DWORD outputlength = pOutputSample->GetActualDataLength();
	CTempoChangeFilter* pFilter = (CTempoChangeFilter*)m_pFilter;

	if(pFilter->m_TempoDelta)
	{
		int returnedsamples = 0;
		DWORD avgframetime = 0;
		bool  IsAudio = GetType(m_mt, avgframetime);

		if(IsAudio)
		{
			pFilter->m_SoundTouch.putSamples((SAMPLETYPE *)pIn, length / 4);

			returnedsamples = pFilter->m_SoundTouch.receiveSamples((SAMPLETYPE *)pOut, 32768);

			HR_BAIL(pOutputSample->SetActualDataLength(returnedsamples*4));


			IMediaSample2 *pOutSample2;
			if (SUCCEEDED(pOutputSample->QueryInterface(IID_IMediaSample2,
													 (void **)&pOutSample2))) {
				/*  Modify it */
				AM_SAMPLE2_PROPERTIES OutProps;
				EXECUTE_ASSERT(SUCCEEDED(pOutSample2->GetProperties(
					FIELD_OFFSET(AM_SAMPLE2_PROPERTIES, tStart), (PBYTE)&OutProps)
				));


		//		OutProps.dwTypeSpecificFlags = pProps->dwTypeSpecificFlags;
		//		OutProps.dwSampleFlags =
		//			(OutProps.dwSampleFlags & AM_SAMPLE_TYPECHANGED) |
		//			(pProps->dwSampleFlags & ~AM_SAMPLE_TYPECHANGED);
				OutProps.cbData = FIELD_OFFSET(AM_SAMPLE2_PROPERTIES, dwStreamId);
 
		//		if (pProps->dwSampleFlags & AM_SAMPLE_DATADISCONTINUITY) {
		//			m_bSampleSkipped = FALSE;
		//		}
		

				OutProps.tStart = pFilter->m_lastRefTime;
				pFilter->m_lastRefTime += (REFERENCE_TIME)returnedsamples * 10000000 / 48000;
				OutProps.tStop  = pFilter->m_lastRefTime;

				HRESULT hr = pOutSample2->SetProperties(
					FIELD_OFFSET(AM_SAMPLE2_PROPERTIES, dwStreamId),
					(PBYTE)&OutProps
				);
				pOutSample2->Release();
			} else {
			
				// Copy the media times

				LONGLONG MediaStart,MediaEnd;
				LONGLONG NewMediaStart = pFilter->m_lastMediaTime;
				LONGLONG NewMediaEnd = pFilter->m_lastMediaTime + (LONGLONG)returnedsamples;

				pInputSample->GetMediaTime(&MediaStart,&MediaEnd);
				pOutputSample->SetMediaTime(&NewMediaStart,&NewMediaEnd);
				
				pFilter->m_lastMediaTime = NewMediaEnd;
			}
		}
		else
		{
			HR_BAIL(pOutputSample->SetActualDataLength(length));
			CopyMemory(pOut, pIn, length);

			avgframetime = (DWORD)((double)avgframetime / (100.0 + pFilter->m_TempoDelta) * 100);


			IMediaSample2 *pOutSample2;
			if (SUCCEEDED(pOutputSample->QueryInterface(IID_IMediaSample2,
													 (void **)&pOutSample2))) {
				/*  Modify it */
				AM_SAMPLE2_PROPERTIES OutProps;
				EXECUTE_ASSERT(SUCCEEDED(pOutSample2->GetProperties(
					FIELD_OFFSET(AM_SAMPLE2_PROPERTIES, tStart), (PBYTE)&OutProps)
				));


		//		OutProps.dwTypeSpecificFlags = pProps->dwTypeSpecificFlags;
		//		OutProps.dwSampleFlags =
		//			(OutProps.dwSampleFlags & AM_SAMPLE_TYPECHANGED) |
		//			(pProps->dwSampleFlags & ~AM_SAMPLE_TYPECHANGED);
				OutProps.cbData = FIELD_OFFSET(AM_SAMPLE2_PROPERTIES, dwStreamId);
 
		//		if (pProps->dwSampleFlags & AM_SAMPLE_DATADISCONTINUITY) {
		//			m_bSampleSkipped = FALSE;
		//		}
		

				OutProps.tStart = pFilter->m_lastVideoRefTime;
				pFilter->m_lastVideoRefTime += (REFERENCE_TIME)avgframetime;
				OutProps.tStop  = pFilter->m_lastVideoRefTime;

				HRESULT hr = pOutSample2->SetProperties(
					FIELD_OFFSET(AM_SAMPLE2_PROPERTIES, dwStreamId),
					(PBYTE)&OutProps
				);
				pOutSample2->Release();
			} else {
			
				// Copy the media times

				LONGLONG MediaStart,MediaEnd;
				LONGLONG NewMediaStart = pFilter->m_lastVideoMediaTime;
				LONGLONG NewMediaEnd = pFilter->m_lastVideoMediaTime + (LONGLONG)avgframetime;

				pInputSample->GetMediaTime(&MediaStart,&MediaEnd);
				pOutputSample->SetMediaTime(&NewMediaStart,&NewMediaEnd);
				
				pFilter->m_lastVideoMediaTime = NewMediaEnd;
			}
		}
	}
	else
	{
		HR_BAIL(pOutputSample->SetActualDataLength(length));
		CopyMemory(pOut, pIn, length);
	}


	
/*	if(pFilter->m_fixStridingToVMR)
	{
		// get frame size from input pin
		int width = 0;
		int bpp = 0;
		int  height = 0;
		BOOL  copyStrided = ExtractFrameSize(m_mt, width, height, bpp);
		int outputWidth = pFilter->m_pOutputPin->m_outputWidth;
		int outputHeight = pFilter->m_pOutputPin->m_outputHeight;

		// only copy strided if really have width diff between output and input width
		if(copyStrided)
		{
			if(outputWidth == width && outputHeight == height)
			{
				copyStrided = FALSE;
			}
		}

		// do strided copy
		if(copyStrided)
		{
			bpp /= 8;
			int bytesPerLineIn = width * bpp;
			int bytesPerLineOut = outputWidth * bpp;

			// YUV media types cannot be upside down despite -biHeight field, so treat them the same
			if(outputHeight < 0 && m_isRGBMediaType)
			{
				// and RGB with -biHeight really is upsdie down ... fix
				BYTE* pBase = pIn;
				int h = abs(outputHeight);
				for(int i = 0; i < h; i++)
				{
					pIn = pBase + (bytesPerLineIn * (h-(i+1)));
					CopyMemory(pOut, pIn, bytesPerLineIn);
					pOut += bytesPerLineOut;
				}
			}
			else
			{
				for(int i = 0; i < abs(outputHeight); i++)
				{
					CopyMemory(pOut, pIn, bytesPerLineIn);
					pOut += bytesPerLineOut;
					pIn += bytesPerLineIn;
				}
			}
			return S_OK;
		}
	}
	*/

	// fallback to full copy if not fixing striding for preview rate fix
	return S_OK;
}

// TODO: TempoChange doesn't handle format size changes correctly.  So you 
// build a graph with a TS thru the Demux & MCDecoder, the video will
// resize but sample rate keeps the vmr at the orig resolution (1440x1080).


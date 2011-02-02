

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Feb 02 12:03:25 2011
 */
/* Compiler settings for TempoChange.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TempoChange_i_h__
#define __TempoChange_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICFTempoChangeStats_FWD_DEFINED__
#define __ICFTempoChangeStats_FWD_DEFINED__
typedef interface ICFTempoChangeStats ICFTempoChangeStats;
#endif 	/* __ICFTempoChangeStats_FWD_DEFINED__ */


#ifndef __CFTempoChangeClass_FWD_DEFINED__
#define __CFTempoChangeClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class CFTempoChangeClass CFTempoChangeClass;
#else
typedef struct CFTempoChangeClass CFTempoChangeClass;
#endif /* __cplusplus */

#endif 	/* __CFTempoChangeClass_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICFTempoChangeStats_INTERFACE_DEFINED__
#define __ICFTempoChangeStats_INTERFACE_DEFINED__

/* interface ICFTempoChangeStats */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICFTempoChangeStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9CE7AB1A-61B0-48bb-BE36-0B4B177EEEF7")
    ICFTempoChangeStats : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetTempoDelta( 
            /* [in] */ float newTempoDeltas) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRateDelta( 
            /* [in] */ float newRateDeltas) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICFTempoChangeStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICFTempoChangeStats * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICFTempoChangeStats * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICFTempoChangeStats * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetTempoDelta )( 
            ICFTempoChangeStats * This,
            /* [in] */ float newTempoDeltas);
        
        HRESULT ( STDMETHODCALLTYPE *SetRateDelta )( 
            ICFTempoChangeStats * This,
            /* [in] */ float newRateDeltas);
        
        END_INTERFACE
    } ICFTempoChangeStatsVtbl;

    interface ICFTempoChangeStats
    {
        CONST_VTBL struct ICFTempoChangeStatsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICFTempoChangeStats_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICFTempoChangeStats_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICFTempoChangeStats_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICFTempoChangeStats_SetTempoDelta(This,newTempoDeltas)	\
    ( (This)->lpVtbl -> SetTempoDelta(This,newTempoDeltas) ) 

#define ICFTempoChangeStats_SetRateDelta(This,newRateDeltas)	\
    ( (This)->lpVtbl -> SetRateDelta(This,newRateDeltas) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICFTempoChangeStats_INTERFACE_DEFINED__ */



#ifndef __CFTempoChangeLibrary_LIBRARY_DEFINED__
#define __CFTempoChangeLibrary_LIBRARY_DEFINED__

/* library CFTempoChangeLibrary */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_CFTempoChangeLibrary;

EXTERN_C const CLSID CLSID_CFTempoChangeClass;

#ifdef __cplusplus

class DECLSPEC_UUID("EAC6F857-8243-4022-B888-9334976D780F")
CFTempoChangeClass;
#endif
#endif /* __CFTempoChangeLibrary_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



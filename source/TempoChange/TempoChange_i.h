/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Apr 05 11:59:44 2005
 */
/* Compiler settings for C:\HD\RTPipe\SoundTouch\source\TempoChange\TempoChange.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


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

#ifdef __cplusplus
extern "C"{
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

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

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
        
    };
    
#else 	/* C style interface */

    typedef struct ICFTempoChangeStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICFTempoChangeStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICFTempoChangeStats __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICFTempoChangeStats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTempoDelta )( 
            ICFTempoChangeStats __RPC_FAR * This,
            /* [in] */ float newTempoDeltas);
        
        END_INTERFACE
    } ICFTempoChangeStatsVtbl;

    interface ICFTempoChangeStats
    {
        CONST_VTBL struct ICFTempoChangeStatsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICFTempoChangeStats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICFTempoChangeStats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICFTempoChangeStats_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICFTempoChangeStats_SetTempoDelta(This,newTempoDeltas)	\
    (This)->lpVtbl -> SetTempoDelta(This,newTempoDeltas)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICFTempoChangeStats_SetTempoDelta_Proxy( 
    ICFTempoChangeStats __RPC_FAR * This,
    /* [in] */ float newTempoDeltas);


void __RPC_STUB ICFTempoChangeStats_SetTempoDelta_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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

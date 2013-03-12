

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Mar 11 22:35:03 2013
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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "TempoChange_i.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   57                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _TempoChange_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } TempoChange_MIDL_TYPE_FORMAT_STRING;

typedef struct _TempoChange_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } TempoChange_MIDL_PROC_FORMAT_STRING;

typedef struct _TempoChange_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } TempoChange_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const TempoChange_MIDL_TYPE_FORMAT_STRING TempoChange__MIDL_TypeFormatString;
extern const TempoChange_MIDL_PROC_FORMAT_STRING TempoChange__MIDL_ProcFormatString;
extern const TempoChange_MIDL_EXPR_FORMAT_STRING TempoChange__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ICFTempoChangeStats_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICFTempoChangeStats_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, float, double or hyper in -Oif or -Oicf.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const TempoChange_MIDL_PROC_FORMAT_STRING TempoChange__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SetTempoDelta */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newTempoDeltas */

/* 16 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 24 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetRateDelta */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 38 */	NdrFcShort( 0x8 ),	/* 8 */
/* 40 */	NdrFcShort( 0x8 ),	/* 8 */
/* 42 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newRateDeltas */

/* 44 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 46 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 48 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 52 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const TempoChange_MIDL_TYPE_FORMAT_STRING TempoChange__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ICFTempoChangeStats, ver. 0.0,
   GUID={0x9CE7AB1A,0x61B0,0x48bb,{0xBE,0x36,0x0B,0x4B,0x17,0x7E,0xEE,0xF7}} */

#pragma code_seg(".orpc")
static const unsigned short ICFTempoChangeStats_FormatStringOffsetTable[] =
    {
    0,
    28
    };

static const MIDL_STUBLESS_PROXY_INFO ICFTempoChangeStats_ProxyInfo =
    {
    &Object_StubDesc,
    TempoChange__MIDL_ProcFormatString.Format,
    &ICFTempoChangeStats_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICFTempoChangeStats_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    TempoChange__MIDL_ProcFormatString.Format,
    &ICFTempoChangeStats_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _ICFTempoChangeStatsProxyVtbl = 
{
    &ICFTempoChangeStats_ProxyInfo,
    &IID_ICFTempoChangeStats,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ICFTempoChangeStats::SetTempoDelta */ ,
    (void *) (INT_PTR) -1 /* ICFTempoChangeStats::SetRateDelta */
};

const CInterfaceStubVtbl _ICFTempoChangeStatsStubVtbl =
{
    &IID_ICFTempoChangeStats,
    &ICFTempoChangeStats_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    TempoChange__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _TempoChange_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ICFTempoChangeStatsProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _TempoChange_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ICFTempoChangeStatsStubVtbl,
    0
};

PCInterfaceName const _TempoChange_InterfaceNamesList[] = 
{
    "ICFTempoChangeStats",
    0
};


#define _TempoChange_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _TempoChange, pIID, n)

int __stdcall _TempoChange_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_TempoChange_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo TempoChange_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _TempoChange_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _TempoChange_StubVtblList,
    (const PCInterfaceName * ) & _TempoChange_InterfaceNamesList,
    0, /* no delegation */
    & _TempoChange_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


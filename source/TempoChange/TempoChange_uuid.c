/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 04 18:20:00 2005
 */
/* Compiler settings for C:\HD\RTPipe\SoundTouch\source\TempoChange\TempoChange.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ICFTempoChangeStats = {0x9CE7AB1A,0x61B0,0x48bb,{0xBE,0x36,0x0B,0x4B,0x17,0x7E,0xEE,0xF7}};


const IID LIBID_CFTempoChangeLibrary = {0xC4697889,0x8B32,0x4096,{0xB3,0xC1,0x7E,0x90,0x22,0xDB,0x29,0x2B}};


const CLSID CLSID_CFTempoChangeClass = {0xEAC6F857,0x8243,0x4022,{0xB8,0x88,0x93,0x34,0x97,0x6D,0x78,0x0F}};


#ifdef __cplusplus
}
#endif


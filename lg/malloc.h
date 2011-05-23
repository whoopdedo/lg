/*****************************
 * LGS Malloc Implementation
 */

#ifndef _LG_MALLOC_H
#define _LG_MALLOC_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#define INTERFACE IDebugMalloc
DECLARE_GUID(IDebugMalloc);
DECLARE_INTERFACE_(IDebugMalloc,IMalloc)
{
	STDMETHOD_(void*,AllocEx)(THIS_ ulong,const char*,int) PURE;
	STDMETHOD_(void*,ReallocEx)(THIS_ void*,ulong,const char*,int) PURE;
	STDMETHOD_(void,FreeEx)(THIS_ void*,const char*,int) PURE;
	STDMETHOD(VerifyAlloc)(THIS_ void*) PURE;
	STDMETHOD(VerifyHeap)(THIS) PURE;
	STDMETHOD_(void,DumpHeapInfo)(THIS) PURE;
	STDMETHOD_(void,DumpStats)(THIS) PURE;
	STDMETHOD_(void,DumpBlocks)(THIS) PURE;
	STDMETHOD_(void,DumpModules)(THIS) PURE;
	STDMETHOD_(void,PushCredit)(THIS_ const char*,int) PURE;
	STDMETHOD_(void,PopCredit)(THIS) PURE;
};
DEFINE_IIDSTRUCT2(IDebugMalloc,IMalloc,IID_IDebugMalloc);
#undef INTERFACE

#endif // _LG_MALLOC_H

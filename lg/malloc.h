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
	STDMETHOD_(void*,AllocEx)(unsigned long,const char*,int) PURE;
	STDMETHOD_(void*,ReallocEx)(void*,unsigned long,const char*,int) PURE;
	STDMETHOD_(void,FreeEx)(void*,const char*,int) PURE;
	STDMETHOD_(long,VerifyAlloc)(void*) PURE;
	STDMETHOD_(long,VerifyHeap)(void) PURE;
	STDMETHOD_(void,DumpHeapInfo)(void) PURE;
	STDMETHOD_(void,DumpStats)(void) PURE;
	STDMETHOD_(void,DumpBlocks)(void) PURE;
	STDMETHOD_(void,DumpModules)(void) PURE;
	STDMETHOD_(void,PushCredit)(const char*,int) PURE;
	STDMETHOD_(void,PopCredit)(void) PURE;
};
DEFINE_IIDSTRUCT2(IDebugMalloc,IMalloc,IID_IDebugMalloc);
#undef INTERFACE

/*
DECLARE_GUID(IScriptModuleAlloc);
DECLARE_INTERFACE_(IScriptModuleAlloc,IMalloc)
{
	STDMETHOD_(void*,AllocEx)(unsigned long,const char*,int) PURE;
	STDMETHOD_(void*,ReallocEx)(void*,unsigned long,const char*,int) PURE;
	STDMETHOD_(void,FreeEx)(void*,const char*,int) PURE;
	STDMETHOD_(long,VerifyAlloc)(void*) PURE;
	STDMETHOD_(long,VerifyHeap)(void) PURE;
	STDMETHOD_(void,DumpHeapInfo)(void) PURE;
	STDMETHOD_(void,DumpStats)(void) PURE;
	STDMETHOD_(void,DumpBlocks)(void) PURE;
	STDMETHOD_(void,DumpModules)(void) PURE;
	STDMETHOD_(void,PushCredit)(const char*,int) PURE;
	STDMETHOD_(void,PopCredit)(void) PURE;
	virtual void Attach(IMalloc **) PURE;
	void Remove(void);
	int HaveRecord(void*);
	sScriptAllocRecord* VoidToRecord(void*);
	void* RealAddress(void*);
	void GrowBlocks(void);
};
DEFINE_IIDSTRUCT2(IScriptModuleAlloc,IMalloc,IID_IScriptModuleAlloc);
*/


#endif // _LG_MALLOC_H

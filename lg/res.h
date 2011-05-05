/**********************
 * LGS Resource loaders
 */

#ifndef _LG_RES_H
#define _LG_RES_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>
#include <lg/scrmanagers.h>

interface IAsyncReadControl;
interface IAsyncReadFulfiller;
interface IAsyncStreamer;
interface IStream;
interface ICache;

struct sARQRequest
{
	IAsyncReadFulfiller* pFulfiller;
	uint queue;
	int iPriority;
	ulong dwData[6];
	const char* pszTrace;
};

struct sARQStreamRequest
{
	IStream* pSource;
	long offset;
	long length;
	uint queue;
	int iPriority;
	uint flags;
	void* pOutBuf;
	long bufSize;
	const char* pszTrace;
};

struct sARQStreamerDesc
{
	IStream* pSource;
	long offset;
	long length;
	uint queue;
	int iPriority;
	uint flags;
	void* pOutBuf;
	long bufSize;
	const char* pszTrace;
};

struct sARQResult
{
	long result;
	void* pOutBuf;
	long bufSize;
	uint flags;
	int readCount;
};

#define INTERFACE IAsyncReadQueue
DECLARE_GUID(IAsyncReadQueue);
DECLARE_INTERFACE_(IAsyncReadQueue,IUnknown)
{
	STDMETHOD(QueueRequest)(THIS_ const sARQRequest *,IAsyncReadControl * *) PURE;
	STDMETHOD(QueueStreamRequest)(THIS_ const sARQStreamRequest *,IAsyncReadControl * *) PURE;
	STDMETHOD(GetAsyncStreamer)(THIS_ const sARQStreamerDesc *,IAsyncStreamer * *) PURE;
	STDMETHOD(Suspend)(THIS) PURE;
	STDMETHOD(Resume)(THIS) PURE;
	STDMETHOD_(Bool,IsStreamerBlocking)(THIS) PURE;
	STDMETHOD(FulfillAll)(THIS) PURE;
	STDMETHOD(FulfillToPriority)(THIS_ int) PURE;
	STDMETHOD(KillAll)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IAsyncReadQueue,IID_IAsyncReadQueue);
#undef INTERFACE

#define INTERFACE IAsyncReadFulfiller
DECLARE_GUID(IAsyncReadFulfiller);
DECLARE_INTERFACE_(IAsyncReadFulfiller,IUnknown)
{
	STDMETHOD(DoFulfill)(THIS_ const sARQRequest *,sARQResult *) PURE;
	STDMETHOD(DoKill)(THIS_ const sARQRequest *,Bool) PURE;
};
DEFINE_IIDSTRUCT(IAsyncReadFulfiller,IID_IAsyncReadFulfiller);
#undef INTERFACE

struct sCacheState
{
	ulong bytes;
	ulong maxBytes;
	ulong items;
	ulong maxItems;
	ulong readCount;
	ulong useCount;
};

struct sCacheStats
{
	ulong unknown;
	ulong memUsed;
	ulong ramTotal;
	ulong ramFree;
	ulong swapTotal;
	ulong swapFree;
	ulong memTotal;
	ulong memFree;
	ulong memCap;
	ulong mallocUsed;
	ulong mallocLocked;
	ulong mallocCached;
};

struct sCacheMsg
{
	ulong message;
	void* pContext;
	ulong item;
	void* pData;
	ulong length;
};

typedef long (__stdcall *CacheCallbackFunc)(const sCacheMsg *);

struct sCacheClientDesc
{
	const IID* pIID_Client;
	void* pContext;
	CacheCallbackFunc pfnCallback;
	ulong maxBytes;
	ulong maxItems;
	uint flags;
};

#define INTERFACE ICache
DECLARE_GUID(ICache);
DECLARE_INTERFACE_(ICache,IUnknown)
{
	STDMETHOD_(void,GetState)(THIS_ sCacheState*) PURE;
	STDMETHOD(Add)(THIS_ ulong,void *,ulong) PURE;
	STDMETHOD(Retrieve)(THIS_ ulong,void * *) PURE;
	STDMETHOD(Remove)(THIS_ ulong,void * *) PURE;
	STDMETHOD(Touch)(THIS_ ulong) PURE;
	STDMETHOD(Age)(THIS_ ulong) PURE;
	STDMETHOD(Flush)(THIS_ ulong) PURE;
	STDMETHOD(FlushAll)(THIS) PURE;
	STDMETHOD_(ulong,Purge)(THIS_ ulong) PURE;
};
DEFINE_IIDSTRUCT(ICache,IID_ICache);
#undef INTERFACE

#define INTERFACE ISharedCache
DECLARE_GUID(ISharedCache);
DECLARE_INTERFACE_(ISharedCache,IUnknown)
{
	STDMETHOD_(void,GetState)(THIS_ sCacheState *) PURE;
	STDMETHOD(AddClient)(THIS_ const sCacheClientDesc *,ICache * *) PURE;
	STDMETHOD(FindClient)(THIS_ const GUID *,ICache * *) PURE;
	STDMETHOD(Touch)(THIS_ const GUID *) PURE;
	STDMETHOD(Age)(THIS_ const GUID *) PURE;
	STDMETHOD(Flush)(THIS_ const GUID *) PURE;
	STDMETHOD(FlushAll)(THIS) PURE;
	STDMETHOD_(ulong,Purge)(THIS_ ulong) PURE;
	STDMETHOD_(void,GetStats)(THIS_ sCacheStats *) PURE;
};
DEFINE_IIDSTRUCT(ISharedCache,IID_ISharedCache);
#undef INTERFACE

#define INTERFACE ISearchPath
DECLARE_GUID(ISearchPath);
DECLARE_INTERFACE_(ISearchPath,IUnknown)
{
	STDMETHOD_(void,Clear)(THIS) PURE;
	STDMETHOD_(ISearchPath*,Copy)(THIS) PURE;
	STDMETHOD_(void,AddPath)(THIS_ const char *) PURE;
	STDMETHOD_(void,AddPathTrees)(THIS_ const char *,Bool) PURE;
	STDMETHOD_(void,Ready)(THIS) PURE;
	STDMETHOD_(void,Refresh)(THIS) PURE;
	STDMETHOD_(void,SetContext)(THIS_ ISearchPath *) PURE;
	STDMETHOD_(void,SetVariants)(THIS_ ISearchPath *) PURE;
	STDMETHOD_(IStore*,Find)(THIS_ const char *,uint,IStore * *,const char *) PURE;
	STDMETHOD_(void*,BeginContents)(THIS_ const char*,uint,const char *) PURE;
	STDMETHOD_(int,Next)(THIS_ void *,IStore * *,char *,char *) PURE;
	STDMETHOD_(void,EndContents)(THIS_ void *) PURE;
	STDMETHOD_(void,Iterate)(THIS_ void (__cdecl *)(ISearchPath*,const char*,int,void*),int,void *) PURE;
};
DEFINE_IIDSTRUCT(ISearchPath,IID_ISearchPath);
#undef INTERFACE

#define INTERFACE IResManHelper
DECLARE_GUID(IResManHelper);
DECLARE_INTERFACE_(IResManHelper,IUnknown)
{
	STDMETHOD_(void*,LockResource)(THIS_ IRes *) PURE;
	STDMETHOD_(void*,ExtractResource)(THIS_ IRes *,void *) PURE;
	STDMETHOD_(void*,FindResource)(THIS_ IRes *,long *) PURE;
	STDMETHOD_(void,UnlockResource)(THIS_ IRes *) PURE;
	STDMETHOD_(uint,GetResourceLockCount)(THIS_ IRes *) PURE;
	STDMETHOD_(Bool,DropResource)(THIS_ IRes *) PURE;
	STDMETHOD_(long,GetResourceSize)(THIS_ IRes *) PURE;
	STDMETHOD_(void,UnregisterResource)(THIS_ IRes *,ulong) PURE;
	STDMETHOD_(Bool,AsyncLock)(THIS_ IRes *,int) PURE;
	STDMETHOD_(Bool,AsyncExtract)(THIS_ IRes *,int,void *,long) PURE;
	STDMETHOD_(Bool,AsyncPreload)(THIS_ IRes *) PURE;
	STDMETHOD_(Bool,IsAsyncFulfilled)(THIS_ IRes *) PURE;
	STDMETHOD(AsyncKill)(THIS_ IRes *) PURE;
	STDMETHOD(GetAsyncResult)(THIS_ IRes *,void * *) PURE;
};
DEFINE_IIDSTRUCT(IResManHelper,IID_IResManHelper);
#undef INTERFACE

enum eResStatMode {
	kResStatAll,
	kResStatSummary,
	kResStatByType,
	kResStatByPath,
	kResStatRes,
	kResStatMRU,
	kResStatNumModes
};

#define INTERFACE IResStats
DECLARE_GUID(IResStats);
DECLARE_INTERFACE_(IResStats,IUnknown)
{
	STDMETHOD_(void,SetMode)(THIS_ eResStatMode,Bool) PURE;
	STDMETHOD_(void,Dump)(THIS_ const char *) PURE;
	STDMETHOD_(void,DumpSnapshot)(THIS_ const char *) PURE;
};
DEFINE_IIDSTRUCT(IResStats,IID_IResStats);
#undef INTERFACE

DECLARE_GUID(IResControl);
DECLARE_GUID(IResHack);
DECLARE_GUID(IResMemOverride);

interface IResMemOverride;

#define INTERFACE IRes
DECLARE_GUID(IRes);
DECLARE_INTERFACE_(IRes,IUnknown)
{
	STDMETHOD_(void*,Lock)(THIS) PURE;
	STDMETHOD_(void,Unlock)(THIS) PURE;
	STDMETHOD_(uint,GetLockCount)(THIS) PURE;
	STDMETHOD_(IResType*,GetType)(THIS) PURE;
	STDMETHOD_(const char*,GetName)(THIS) PURE;
	STDMETHOD_(void,GetCanonPath)(THIS_ char * *) PURE;
	STDMETHOD_(void,GetCanonPathName)(THIS_ char * *) PURE;
	STDMETHOD_(IStore*,GetCanonStore)(THIS) PURE;
	STDMETHOD_(void,GetStreamName)(THIS_ Bool,char * *) PURE;
	STDMETHOD_(void*,DataPeek)(THIS) PURE;
	STDMETHOD_(Bool,Drop)(THIS) PURE;
	STDMETHOD_(long,GetSize)(THIS) PURE;
	STDMETHOD_(void*,Extract)(THIS_ void *) PURE;
	STDMETHOD_(void*,PreLoad)(THIS) PURE;
	STDMETHOD_(int,ExtractPartial)(THIS_ long,long,void*) PURE;
	STDMETHOD_(void,ExtractBlocks)(THIS_ void *,long,long (__cdecl *)(IRes*,void*,long,long,void*),void*) PURE;
	STDMETHOD_(Bool,AsyncLock)(THIS_ int) PURE;
	STDMETHOD_(Bool,AsyncExtract)(THIS_ int,void *,long) PURE;
	STDMETHOD_(Bool,AsyncPreload)(THIS) PURE;
	STDMETHOD_(Bool,IsAsyncFulfilled)(THIS) PURE;
	STDMETHOD(AsyncKill)(THIS) PURE;
	STDMETHOD(GetAsyncResult)(THIS_ void * *) PURE;
	STDMETHOD_(void,SetAppData)(ulong) PURE;
	STDMETHOD_(ulong,GetAppData)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IRes,IID_IRes);
#undef INTERFACE

#define INTERFACE IResMem
DECLARE_GUID(IResMem);
DECLARE_INTERFACE_(IResMem,IUnknown)
{
	STDMETHOD_(void,EnablePaging)(THIS_ Bool) PURE;
	STDMETHOD_(void,Compact)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IResMem,IID_IResMem);
#undef INTERFACE

#define INTERFACE IResType
DECLARE_GUID(IResType);
DECLARE_INTERFACE_(IResType,IUnknown)
{
	STDMETHOD_(const char*,GetName)(THIS) PURE;
	STDMETHOD_(void,EnumerateExts)(THIS_ void (__cdecl *)(const char *,IResType *,void *),void *) PURE;
	STDMETHOD_(int,IsLegalExt)(THIS_ const char *) PURE;
	STDMETHOD_(IRes*,CreateRes)(THIS_ IStore *,char const *,char const *,IResMemOverride * *) PURE;
};
DEFINE_IIDSTRUCT(IResType,IID_IResType);
#undef INTERFACE

#define INTERFACE IStringRes
DECLARE_GUID(IStringRes);
DECLARE_INTERFACE_(IStringRes,IRes)
{
	STDMETHOD_(void,StringPreload)(THIS_ const char *) PURE;
	STDMETHOD_(char*,StringLock)(THIS_ const char *) PURE;
	STDMETHOD_(void,StringUnlock)(THIS_ const char *) PURE;
	STDMETHOD_(Bool,StringExtract)(THIS_ const char *,char *,int) PURE;
};
DEFINE_IIDSTRUCT2(IStringRes,IRes,IID_IStringRes);
#undef INTERFACE

#endif // _LG_RES_H

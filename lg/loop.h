/**********************
 * LGS Loop Dispatch
 */

#ifndef _LG_LOOP_H
#define _LG_LOOP_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

LG_DECLARE_HANDLE(tLoopMessageData);
LG_DECLARE_HANDLE(tLoopClientData);
struct sLoopModeInitParmList
{
	const IID* pIID_Loop;
	tLoopClientData data;
};
struct sLoopInstantiator
{
	const IID* pIID_Loop;
	int minorMode;
	sLoopModeInitParmList init;
};
struct sLoopTransition
{
	sLoopInstantiator from;
	sLoopInstantiator to;
};
struct sLoopModeName
{
	const IID* pIID_Loop;
	char szName[32];
};
struct sLoopModeDesc
{
	sLoopModeName name;
	const IID** ppClientIDs;
	uint nClients;
};
struct sLoopFrameInfo
{
	int fMinorMode;
	uint nClients;
	ulong nTicks;
	ulong dTicks;
};
struct sLoopClientDesc
{
};

#define INTERFACE ILoopClient
DECLARE_GUID(ILoopClient);
DECLARE_INTERFACE_(ILoopClient,IUnknown)
{
	STDMETHOD_(short,GetVersion)(THIS) PURE;
	STDMETHOD_(const sLoopClientDesc*,GetDescription)(THIS) PURE;
	STDMETHOD_(int,ReceiveMessage)(THIS_ int,tLoopMessageData) PURE;
};
DEFINE_IIDSTRUCT(ILoopClient,IID_ILoopClient);
#undef INTERFACE

#define INTERFACE ILoopClientFactory
DECLARE_GUID(ILoopClientFactory);
DECLARE_INTERFACE_(ILoopClientFactory,IUnknown)
{
	STDMETHOD_(short,GetVersion)(THIS) PURE;
	STDMETHOD_(const GUID**,QuerySupport)(THIS) PURE;
	STDMETHOD_(Bool,DoesSupport)(THIS_ const GUID *) PURE;
	STDMETHOD(GetClient)(THIS_ const GUID *,tLoopClientData,ILoopClient**) PURE;
};
DEFINE_IIDSTRUCT(ILoopClientFactory,IID_ILoopClientFactory);
#undef INTERFACE

#define INTERFACE ILoopDispatch
DECLARE_GUID(ILoopDispatch);
DECLARE_INTERFACE_(ILoopDispatch,IUnknown)
{
	STDMETHOD(SendMessage)(THIS_ int,tLoopMessageData,int) PURE;
	STDMETHOD(SendSimpleMessage)(THIS_ int) PURE;
	STDMETHOD(PostMessage)(THIS_ int,tLoopMessageData,int) PURE;
	STDMETHOD(PostSimpleMessage)(THIS_ int) PURE;
	STDMETHOD(ProcessQueue)(THIS) PURE;
	STDMETHOD_(const sLoopModeName*,Describe)(THIS_ sLoopModeInitParmList *) PURE;
	STDMETHOD_(void,SetDiagnostics)(THIS_ uint,ulong) PURE;
	STDMETHOD_(void,GetDiagnostics)(THIS_ uint*,ulong*) PURE;
	STDMETHOD_(void,SetProfile)(THIS_ ulong,const GUID*) PURE;
	STDMETHOD_(void,GetProfile)(THIS_ ulong*,const GUID**) PURE;
	STDMETHOD_(void,ClearTimers)(THIS) PURE;
	STDMETHOD_(void,DumpTimerInfo)(THIS) PURE;
};
DEFINE_IIDSTRUCT(ILoopDispatch,IID_ILoopDispatch);
#undef INTERFACE

#define INTERFACE ILoopMode
DECLARE_GUID(ILoopMode);
DECLARE_INTERFACE_(ILoopMode,IUnknown)
{
	STDMETHOD_(const sLoopModeName*,GetName)(THIS) PURE;
	STDMETHOD(CreateDispatch)(THIS_ sLoopModeInitParmList,ILoopDispatch**) PURE;
	STDMETHOD(CreatePartialDispatch)(THIS_ sLoopModeInitParmList,ulong,ILoopDispatch**) PURE;
	STDMETHOD_(const sLoopModeDesc*,Describe)(THIS) PURE;
};
DEFINE_IIDSTRUCT(ILoopMode,IID_ILoopMode);
#undef INTERFACE

#define INTERFACE ILoopManager
DECLARE_GUID(ILoopManager);
DECLARE_INTERFACE_(ILoopManager,IUnknown)
{
	STDMETHOD(AddClient)(THIS_ ILoopClient *,ulong *) PURE;
	STDMETHOD(RemoveClient)(THIS_ ulong) PURE;
	STDMETHOD(AddClientFactory)(THIS_ ILoopClientFactory *,ulong *) PURE;
	STDMETHOD(RemoveClientFactory)(THIS_ ulong) PURE;
	STDMETHOD(GetClient)(THIS_ const GUID *,tLoopClientData,ILoopClient **) PURE;
	STDMETHOD(AddMode)(THIS_ const sLoopModeDesc *) PURE;
	STDMETHOD_(ILoopMode*,GetMode)(THIS_ const GUID *) PURE;
	STDMETHOD(RemoveMode)(THIS_ const GUID *) PURE;
	STDMETHOD(SetBaseMode)(THIS_ const GUID *) PURE;
	STDMETHOD_(ILoopMode*,GetBaseMode)(THIS) PURE;
};
DEFINE_IIDSTRUCT(ILoopManager,IID_ILoopManager);
#undef INTERFACE

#define INTERFACE ILoop
DECLARE_GUID(ILoop);
DECLARE_INTERFACE_(ILoop,IUnknown)
{
	STDMETHOD_(int,Go)(THIS_ sLoopInstantiator*) PURE;
	STDMETHOD(EndAllModes)(THIS_ int) PURE;
	STDMETHOD(Terminate)(THIS) PURE;
	STDMETHOD_(const sLoopFrameInfo*,GetFrameInfo)(THIS) PURE;
	STDMETHOD(ChangeMode)(THIS_ int,sLoopInstantiator*) PURE;
	STDMETHOD(EndMode)(THIS_ int) PURE;
	STDMETHOD_(ILoopMode*,GetCurrentMode)(THIS) PURE;
	STDMETHOD_(ILoopDispatch*,GetCurrentDispatch)(THIS) PURE;
	STDMETHOD_(void,Pause)(THIS_ Bool) PURE;
	STDMETHOD_(Bool,IsPaused)(THIS) PURE;
	STDMETHOD(ChangeMinorMode)(THIS_ int) PURE;
	STDMETHOD_(int,GetMinorMode)(THIS) PURE;
	STDMETHOD(SendMessage)(THIS_ int,tLoopMessageData,int) PURE;
	STDMETHOD(SendSimpleMessage)(THIS_ int) PURE;
	STDMETHOD(PostMessage)(THIS_ int,tLoopMessageData,int) PURE;
	STDMETHOD(PostSimpleMessage)(THIS_ int) PURE;
	STDMETHOD(ProcessQueue)(THIS) PURE;
	STDMETHOD_(void,SetDiagnostics)(THIS_ uint,ulong) PURE;
	STDMETHOD_(void,GetDiagnostics)(THIS_ uint*,ulong*) PURE;
	STDMETHOD_(void,SetProfile)(THIS_ ulong,const GUID*) PURE;
	STDMETHOD_(void,GetProfile)(THIS_ ulong*,const GUID**) PURE;
};
DEFINE_IIDSTRUCT(ILoop,IID_ILoop);
#undef INTERFACE

#endif // _LG_LOOP_H

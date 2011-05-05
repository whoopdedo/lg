/**********************
 * LGS Networking
 */

#ifndef _LG_NET_H
#define _LG_NET_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
/*
#define IDIRECTPLAY2_OR_GREATER
#include <dplay.h>
*/
#include <lg/iiddef.h>

#include <lg/types.h>
#include <lg/defs.h>

DECLARE_GUID(INet);
/*
DECLARE_INTERFACE_(INet,IDirectPlay4)
{
	STDMETHOD(JoinOrCreate)(THIS_ char*,char*,Bool*,void*) PURE;
	STDMETHOD_(Bool,Host)(THIS_ char*,char*) PURE;
	STDMETHOD_(Bool,Join)(THIS_ char*,char*,char*) PURE;
	STDMETHOD_(ulong,SimpleCreatePlayer)(THIS_ char*) PURE;
	STDMETHOD_(ulong,IdForName)(THIS_ char*) PURE;
	STDMETHOD(GetPlayerAddress)(THIS_ ulong,char*,int) PURE;
	STDMETHOD_(void,UseInternetSimulation)(THIS_ Bool) PURE;
	STDMETHOD_(Bool,IsSimulatingInternet)(THIS) PURE;
	STDMETHOD_(void,SetFullInternetParameters)(THIS_ double,double,double,ulong,ulong,ulong) PURE;
	STDMETHOD_(void,SetInternetParameters)(THIS_ double,double,double,ulong) PURE;
	STDMETHOD_(void,ResetPlayerData)(THIS_ ulong,void*) PURE;
	STDMETHOD_(double,ToThisGameTime)(THIS_ double,ulong) PURE;
	STDMETHOD_(double,PlayerTimeScale)(THIS_ ulong) PURE;
	STDMETHOD_(double,PlayerTimeDelta)(THIS_ ulong) PURE;
	STDMETHOD_(void,UpdatePlayerTime)(THIS_ double,double,ulong) PURE;
	STDMETHOD_(const char*,DPlayErrorAsString)(THIS_ HResult) PURE;
};
DEFINE_IIDSTRUCT2(INet,IDirectPlay4,IID_INet);
*/

struct sPropertyObjIter;

struct sGlobalObjID
{
	uchar host;
	short id;
};

struct sNetMsg_Generic
{
	uchar type;
};

typedef int tNetListenerHandle;

#define INTERFACE INetManager
DECLARE_GUID(INetManager);
DECLARE_INTERFACE_(INetManager,IUnknown)
{
	STDMETHOD_(Bool,Networking)(THIS) PURE;
	STDMETHOD_(Bool,IsNetworkGame)(THIS) PURE;
	STDMETHOD_(ulong,NumPlayers)(THIS) PURE;
	STDMETHOD_(ulong,MyPlayerNum)(THIS) PURE;
	STDMETHOD_(ulong,ObjToPlayerNum)(THIS_ int) PURE;
	STDMETHOD_(int,PlayerNumToObj)(THIS_ ulong) PURE;
	STDMETHOD_(void,SetPlayerName)(THIS_ const char*) PURE;
	STDMETHOD_(const char*,GetPlayerName)(THIS_ int) PURE;
	STDMETHOD_(const char*,GetPlayerAddress)(THIS_ int) PURE;
	STDMETHOD_(Bool,Host)(THIS_ const char*,const char*) PURE;
	STDMETHOD_(Bool,Join)(THIS_ const char*,const char*,const char*) PURE;
	STDMETHOD_(ulong,GetTimeout)(THIS) PURE;
	STDMETHOD_(void,SetTimeout)(THIS_ ulong) PURE;
	STDMETHOD_(void,SuspendMessaging)(THIS) PURE;
	STDMETHOD_(int,Suspended)(THIS) PURE;
	STDMETHOD_(void,ResumeMessaging)(THIS) PURE;
	STDMETHOD_(void,Send)(THIS_ int,void*,ulong,Bool) PURE;
	STDMETHOD_(void,Broadcast)(THIS_ void*,ulong,Bool) PURE;
	STDMETHOD_(void,MetagameBroadcast)(THIS_ void*,ulong,Bool) PURE;
	STDMETHOD_(int,DefaultHost)(THIS) PURE;
	STDMETHOD_(Bool,AmDefaultHost)(THIS) PURE;
	STDMETHOD_(const char*,GetDefaultHostName)(THIS) PURE;
	STDMETHOD_(uchar,RegisterMessageParser)(THIS_ void (__stdcall *)(const sNetMsg_Generic*,ulong,int,void*),const char*,ulong,void*) PURE;
	STDMETHOD_(void,NetPlayerIterStart)(THIS_ sPropertyObjIter*) const PURE;
	STDMETHOD_(Bool,NetPlayerIterNext)(THIS_ sPropertyObjIter*,int*) const PURE;
	STDMETHOD_(tNetListenerHandle,Listen)(THIS_ void (__stdcall *)(ulong,ulong,void*),ulong,void*) PURE;
	STDMETHOD_(sGlobalObjID*,ToGlobalObjID)(THIS_ sGlobalObjID&,int) PURE;
	STDMETHOD_(int,FromGlobalObjID)(THIS_ sGlobalObjID*) PURE;
	STDMETHOD_(int,OriginatingPlayer)(THIS) PURE;
	STDMETHOD_(void,StartSynch)(THIS) PURE;
	STDMETHOD_(void,NonNetworkLevel)(THIS) PURE;
	STDMETHOD_(void,NormalLevel)(THIS) PURE;
	STDMETHOD_(void,PreFlush)(THIS) PURE;
	STDMETHOD_(Bool,SynchFlush)(THIS_ int (__stdcall *)(void*),void*) PURE;
	STDMETHOD_(const char*,GetPlayerNameByNum)(THIS_ int) PURE;
	STDMETHOD_(const char*,GetPlayerAddressByNum)(THIS_ int) PURE;
	STDMETHOD_(void,Leave)(THIS) PURE;
	STDMETHOD_(void,Unlisten)(THIS_ tNetListenerHandle) PURE;
	STDMETHOD_(void,SetMaxPlayers)(THIS_ int) PURE;
};
/*
	virtual void* d0(unsigned int) = 0;
	STDMETHOD_(ulong,ToNetPlayerID)(THIS_ int) PURE;
	STDMETHOD_(int,FromNetPlayerID)(THIS_ ulong) PURE;
*/
DEFINE_IIDSTRUCT(INetManager,IID_INetManager);
#undef INTERFACE

#define INTERFACE INetStats
DECLARE_GUID(INetStats);
DECLARE_INTERFACE_(INetStats,IUnknown)
{
	STDMETHOD_(void,BandwidthStats)(THIS_ float*,ulong*,ulong*,char**) PURE;
	STDMETHOD_(void,FrameStats)(THIS_ ulong*,ulong*,char**) PURE;
	STDMETHOD_(void,MaxStats)(THIS_ ulong*,ulong*) PURE;
};
DEFINE_IIDSTRUCT(INetStats,IID_INetStats);
#undef INTERFACE

#define INTERFACE IObjectNetworking
DECLARE_GUID(IObjectNetworking);
DECLARE_INTERFACE_(IObjectNetworking,IUnknown)
{
	STDMETHOD_(void,ClearTables)(THIS) PURE;
	STDMETHOD_(void,ObjRegisterProxy)(THIS_ int,short,int) PURE;
	STDMETHOD_(int,ObjGetProxy)(THIS_ int,short) PURE;
	STDMETHOD_(void,ObjDeleteProxy)(THIS_ int) PURE;
	STDMETHOD_(Bool,ObjIsProxy)(THIS_ int) PURE;
	STDMETHOD_(Bool,ObjHostedHere)(THIS_ int) PURE;
	STDMETHOD_(Bool,ObjLocalOnly)(THIS_ int) PURE;
	STDMETHOD_(int,ObjHostPlayer)(THIS_ int) PURE;
	STDMETHOD_(short,ObjHostObjID)(THIS_ int) PURE;
	STDMETHOD_(void,ObjHostInfo)(THIS_ int,int*,short*) PURE;
	STDMETHOD_(void,ObjTakeOver)(THIS_ int) PURE;
	STDMETHOD_(void,ObjGiveTo)(THIS_ int,int,int) PURE;
	STDMETHOD_(void,ObjGiveWithoutObjID)(THIS_ int,int) PURE;
	STDMETHOD_(void,StartBeginCreate)(THIS_ int,int) PURE;
	STDMETHOD_(void,FinishBeginCreate)(THIS_ int) PURE;
	STDMETHOD_(void,StartEndCreate)(THIS_ int) PURE;
	STDMETHOD_(void,FinishEndCreate)(THIS_ int) PURE;
	STDMETHOD_(void,StartDestroy)(THIS_ int) PURE;
	STDMETHOD_(void,FinishDestroy)(THIS_ int) PURE;
	STDMETHOD_(Bool,HandlingProxy)(THIS) PURE;
	STDMETHOD_(void,NotifyObjRemapped)(THIS_ int,int) PURE;
	STDMETHOD_(void,ResolveRemappings)(THIS_ ulong,int) PURE;
	STDMETHOD_(void,RequestDestroy)(THIS_ int) PURE;
};
DEFINE_IIDSTRUCT(IObjectNetworking,IID_IObjectNetworking);
#undef INTERFACE

struct sAIImpulse
{
	mxs_vector vec;
	float facing;
	ulong flags;
};

struct sAINetTransfer
{
	uint uSize;
	void* pData;
};

#define INTERFACE IAINetManager
DECLARE_GUID(IAINetManager);
DECLARE_INTERFACE_(IAINetManager,IUnknown)
{
	STDMETHOD_(Bool,IsProxy)(THIS_ int) PURE;
	STDMETHOD(GetAITransferInfo)(THIS_ int,sAINetTransfer * *) PURE;
	STDMETHOD(MakeProxyAI)(THIS_ int,int) PURE;
	STDMETHOD(MakeFullAI)(THIS_ int,const sAINetTransfer *) PURE;
	STDMETHOD(RecheckAIOwnership)(THIS) PURE;
	STDMETHOD_(uint,NetMsgHandlerID)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IAINetManager,IID_IAINetManager);
#undef INTERFACE

typedef int sAIPlayerList[8];

#define INTERFACE IAINetServices
DECLARE_GUID(IAINetServices);
DECLARE_INTERFACE_(IAINetServices,IUnknown)
{
	STDMETHOD_(Bool,Networking)(THIS) PURE;
	STDMETHOD_(int,GetPlayers)(THIS_ sAIPlayerList *) PURE;
	STDMETHOD_(void,SetObjImpulse)(THIS_ int,float,float,float,float,Bool) PURE;
	STDMETHOD_(Bool,TransferAI)(THIS_ int,int) PURE;
	STDMETHOD_(Bool,GetTargetVel)(THIS_ int,sAIImpulse *) PURE;
};
DEFINE_IIDSTRUCT(IAINetServices,IID_IAINetServices);
#undef INTERFACE

#define INTERFACE IScriptNet
DECLARE_GUID(IScriptNet);
DECLARE_INTERFACE_(IScriptNet,IUnknown)
{
	STDMETHOD_(Bool,ObjIsProxy)(THIS_ int) PURE;
	STDMETHOD(PostToOwner)(THIS_ int,int,const char*,const cMultiParm&,const cMultiParm&,const cMultiParm&) PURE;
};
DEFINE_IIDSTRUCT(IScriptNet,IID_IScriptNet);
#undef INTERFACE

#define INTERFACE IAvatar
DECLARE_GUID(IAvatar);
DECLARE_INTERFACE_(IAvatar,IUnknown)
{
	STDMETHOD_(ulong,PlayerNum)(THIS) PURE;
	STDMETHOD_(int,PlayerObjID)(THIS) PURE;
	STDMETHOD_(void,WriteTagInfo)(THIS_ ITagFile *) PURE;
};
DEFINE_IIDSTRUCT(IAvatar,IID_IAvatar);
#undef INTERFACE

#endif // _LG_NET_H

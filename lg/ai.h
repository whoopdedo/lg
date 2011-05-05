/**********************
 * LGS AI
 */

#ifndef _LG_AI_H
#define _LG_AI_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>
#include <lg/scrmanagers.h>
#include <lg/dynarray.h>

class cTagSet;

#define INTERFACE IAIAppServices
DECLARE_GUID(IAIAppServices);
DECLARE_INTERFACE_(IAIAppServices,IUnknown)
{
	STDMETHOD(AddSoundTags)(THIS_ cTagSet *) PURE;
};
DEFINE_IIDSTRUCT(IAIAppServices,IID_IAIAppServices);
#undef INTERFACE

interface IInternalAI;

DECLARE_GUID(IAIPathfindControl);
DECLARE_GUID(IAIPathQuery);

class cAIPathEdge;

#define INTERFACE IAIPath
DECLARE_GUID(IAIPath);
DECLARE_INTERFACE_(IAIPath,IUnknown)
{
	STDMETHOD_(Bool,Active)(THIS) PURE;
	STDMETHOD_(void,Clear)(THIS) PURE;
	STDMETHOD_(ulong,Advance)(THIS_ unsigned char) PURE;
	STDMETHOD_(Bool,Backup)(THIS) PURE;
	STDMETHOD_(int,GetPathEdgeCount)(THIS) const PURE;
	STDMETHOD_(void,GetPathEdge)(THIS_ int,cAIPathEdge *) const PURE;
	STDMETHOD_(const cAIPathEdge*,GetCurEdge)(THIS) const PURE;
	STDMETHOD_(void,GetFinalDestination)(THIS_ mxs_vector *) const PURE;
	STDMETHOD_(Bool,MoreEdges)(THIS) const PURE;
	STDMETHOD_(Bool,IsDestVisible)(THIS_ const mxs_vector &,uint,unsigned char) const PURE;
	STDMETHOD_(int,UpdateTargetEdge)(THIS_ const mxs_vector &,const mxs_angvec &,uint,unsigned char) PURE;
	STDMETHOD_(float,ComputeXYLength)(THIS_ const mxs_vector &) const PURE;
	STDMETHOD_(void,SetStressBits)(THIS_ unsigned char) PURE;
	STDMETHOD_(unsigned char,GetStressBits)(THIS) PURE;
	STDMETHOD_(Bool,IsCellInPath)(THIS_ uint) PURE;
};
DEFINE_IIDSTRUCT(IAIPath,IID_IAIPath);
#undef INTERFACE

class cAIActions;
class cAIGoal;

enum eAIPriority
{
	kAIP_None,
	kAIP_VeryLow,
	kAIP_Low,
	kAIP_Normal,
	kAIP_High,
	kAIP_VeryHigh,
	kAIP_Absolute,
	kAIP_Num
};

struct sAIAction;
struct sAIAlertness;
struct sAISoundType;

interface IAIActor;

#define INTERFACE IAIAction
DECLARE_GUID(IAIAction);
DECLARE_INTERFACE_(IAIAction,IUnknown)
{
	STDMETHOD_(void,Describe)(THIS_ cAnsiStr *) PURE;
	STDMETHOD_(Bool,InProgress)(THIS) PURE;
	STDMETHOD_(int,GetType)(THIS) PURE;
	STDMETHOD_(eAIResult,GetResult)(THIS) PURE;
	STDMETHOD_(ulong,GetData)(THIS_ uint) PURE;
	STDMETHOD_(const sAIAction*,Access)(THIS) PURE;
	STDMETHOD_(Bool,IsProxy)(THIS) PURE;
	STDMETHOD_(IAIAction*,GetInnerAction)(THIS) PURE;
	STDMETHOD_(IAIAction*,GetTrueAction)(THIS) PURE;
	STDMETHOD_(IAIActor*,GetTrueOwner)(THIS) PURE;
	STDMETHOD_(eAIResult,Update)(THIS) PURE;
	STDMETHOD_(eAIResult,Enact)(THIS_ uint) PURE;
	STDMETHOD_(eAIResult,End)(THIS) PURE;
	STDMETHOD_(Bool,Save)(THIS_ ITagFile *) PURE;
	STDMETHOD_(Bool,Load)(THIS_ ITagFile *) PURE;
	STDMETHOD_(IAIPath*,GetPath)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IAIAction,IID_IAIAction);
#undef INTERFACE

enum eAIPropUpdateKind
{
	kAIPropUpdateZero
};

struct sAIDefendPoint;
struct sAISignal;
struct sAIMoveGoal;
class cAIMoveSuggestions;

struct sPhysListenMsg;
struct sPropertyListenMsg;
struct sDamageMsg;

#define INTERFACE IAIComponent
DECLARE_GUID(IAIComponent);
DECLARE_INTERFACE_(IAIComponent,IUnknown)
{
	STDMETHOD_(void,GetSubComponents)(THIS_ cDynArray<IAIComponent *> *) PURE;
	STDMETHOD_(void,ConnectComponent)(THIS_ IInternalAI *,unsigned int * *) PURE;
	STDMETHOD_(void,Init)(THIS) PURE;
	STDMETHOD_(void,End)(THIS) PURE;
	STDMETHOD_(int,Object)(THIS) PURE;
	STDMETHOD_(const char*,GetName)(THIS) PURE;
	STDMETHOD_(void,OnSimStart)(THIS) PURE;
	STDMETHOD_(void,OnSimEnd)(THIS) PURE;
	STDMETHOD_(void,OnBeginFrame)(THIS) PURE;
	STDMETHOD_(void,OnEndFrame)(THIS) PURE;
	STDMETHOD_(void,OnUpdateProperties)(THIS_ eAIPropUpdateKind) PURE;
	STDMETHOD_(void,OnActionProgress)(THIS_ IAIAction *) PURE;
	STDMETHOD_(void,OnGoalProgress)(THIS_ const cAIGoal *) PURE;
	STDMETHOD_(void,OnModeChange)(THIS_ eAIMode,eAIMode) PURE;
	STDMETHOD_(void,OnGoalChange)(THIS_ const cAIGoal *,const cAIGoal *) PURE;
	STDMETHOD_(void,OnActionChange)(THIS_ IAIAction *,IAIAction *) PURE;
	STDMETHOD_(void,OnAwareness)(THIS_ int,eAIAwareLevel,const sAIAlertness *) PURE;
	STDMETHOD_(void,OnAlertness)(THIS_ int,eAIAwareLevel,eAIAwareLevel,const sAIAlertness *) PURE;
	STDMETHOD_(void,OnHighAlert)(THIS_ int,eAIAwareLevel,eAIAwareLevel,const sAIAlertness *) PURE;
	STDMETHOD_(void,OnDamage)(THIS_ const sDamageMsg *,int) PURE;
	STDMETHOD_(void,OnDeath)(THIS_ const sDamageMsg *) PURE;
	STDMETHOD_(void,OnWeapon)(THIS_ int,int,int) PURE;
	STDMETHOD_(void,OnSound)(THIS_ const sSoundInfo *,const sAISoundType *) PURE;
	STDMETHOD_(void,OnFastObj)(THIS_ int,int,const mxs_vector &) PURE;
	STDMETHOD_(void,OnFoundBody)(THIS_ int) PURE;
	STDMETHOD_(void,OnFoundSuspicious)(THIS_ int) PURE;
	STDMETHOD_(void,OnScriptCommand)(THIS_ uint,void *) PURE;
	STDMETHOD_(void,OnProperty)(THIS_ IProperty *,const sPropertyListenMsg *) PURE;
	STDMETHOD_(void,OnDefend)(THIS_ const sAIDefendPoint *) PURE;
	STDMETHOD_(void,OnSignal)(THIS_ const sAISignal *) PURE;
	STDMETHOD_(void,OnWitnessCombat)(THIS) PURE;
	STDMETHOD_(void,OnGoalsReset)(THIS_ const cAIGoal *) PURE;
	STDMETHOD_(void,OnCollision)(THIS_ const sPhysListenMsg *) PURE;
	STDMETHOD_(void,OnTripwire)(THIS_ int,int) PURE;
	STDMETHOD_(void,OnFrustration)(THIS_ int,int,IAIPath *) PURE;
	STDMETHOD_(void,OnGameEvent)(THIS_ void *) PURE;
	STDMETHOD_(int,PreSave)(THIS) PURE;
	STDMETHOD_(int,Save)(THIS_ ITagFile *) PURE;
	STDMETHOD_(int,PostSave)(THIS) PURE;
	STDMETHOD_(int,PreLoad)(THIS) PURE;
	STDMETHOD_(int,Load)(THIS_ ITagFile *) PURE;
	STDMETHOD_(int,PostLoad)(void) PURE;
};
/*
	STDMETHOD_(int,SaveActions(THIS_ ITagFile *,cAIActions *)
	STDMETHOD_(int,LoadActions(THIS_ ITagFile *,cAIActions *)
	STDMETHOD_(long,SuggestActions(THIS_ cAIGoal *,const cAIActions &,cAIActions *)
	STDMETHOD_(void,ConnectAbility(THIS_ unsigned int * *)
	STDMETHOD_(int,SaveGoal(THIS_ ITagFile *,cAIGoal *)
	STDMETHOD_(int,LoadGoal(THIS_ ITagFile *,cAIGoal * *)
*/
DEFINE_IIDSTRUCT(IAIComponent,IID_IAIComponent);
#undef INTERFACE

enum eAIConverseState
{
	kAIConvNotStarted,
	kAIConvStarted,
	kAIConvFinished = 7
};

#define INTERFACE IAIConversation
DECLARE_GUID(IAIConversation);
DECLARE_INTERFACE_(IAIConversation,IUnknown)
{
	STDMETHOD_(void,OnStateChange)(THIS_ int,eAIConverseState,eAIConverseState) PURE;
	STDMETHOD_(void,OnAlertness)(THIS_ eAIAwareLevel) PURE;
	STDMETHOD_(void,Frame)(THIS) PURE;
	STDMETHOD_(int,GetConversationID)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IAIConversation,IID_IAIConversation);
#undef INTERFACE

struct sAIPsdScrAct;

#define INTERFACE IAIConverse
DECLARE_GUID(IAIConverse);
DECLARE_INTERFACE_(IAIConverse,IUnknown)
{
	STDMETHOD_(void,Start)(THIS_ IAIConversation *,int) PURE;
	STDMETHOD_(void,NewActions)(THIS_ sAIPsdScrAct *,uint) PURE;
	STDMETHOD_(void,Terminate)(THIS) PURE;
	STDMETHOD_(void,OnSpeechStart)(THIS_ int) PURE;
	STDMETHOD_(void,OnSpeechEnd)(THIS_ int) PURE;
	STDMETHOD_(void,SetPriority)(THIS_ eAIPriority) PURE;
	STDMETHOD_(int,GetCurrentAction)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IAIConverse,IID_IAIConverse);
#undef INTERFACE

DECLARE_GUID(IAIAbility);
DECLARE_GUID(IAIInform);
DECLARE_GUID(IAIMoveRegulator);
interface IAIMoveAction;
interface IAILocoAction;
interface IAIMotionAction;
interface IAISoundAction;
interface IAIOrientAction;
interface IAIFrobAction;
interface IAIFollowAction;
interface IAIInvestAction;
interface IAIWanderAction;
interface IAIPsdScrAction;
interface IAIWaitAction;
interface IAILaunchAction;
interface IAIJointRotateAction;
interface IAIJointSlideAction;
interface IAIJointScanAction;

class cAIActor;

#define INTERFACE IAIBehaviorSet
DECLARE_GUID(IAIBehaviorSet);
DECLARE_INTERFACE_(IAIBehaviorSet,IUnknown)
{
	STDMETHOD_(const char*,GetName)(THIS) PURE;
	STDMETHOD_(IAI*,CreateAI)(THIS_ int) PURE;
	STDMETHOD(CreateComponents)(THIS_ cDynArray<IAIComponent *> *) PURE;
	STDMETHOD_(IAIMoveAction*,CreateMoveAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAILocoAction*,CreateLocoAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIMotionAction*,CreateMotionAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAISoundAction*,CreateSoundAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIOrientAction*,CreateOrientAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIFrobAction*,CreateFrobAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIFollowAction*,CreateFollowAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIInvestAction*,CreateInvestAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIWanderAction*,CreateWanderAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIPsdScrAction*,CreatePsdScrAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIWaitAction*,CreateWaitAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAILaunchAction*,CreateLaunchAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIJointRotateAction*,CreateJointRotateAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIJointSlideAction*,CreateJointSlideAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIJointScanAction*,CreateJointScanAction)(THIS_ cAIActor *,ulong) PURE;
	STDMETHOD_(IAIAction*,CreateGestureAction)(THIS_ int,cAIActor *,ulong) PURE;
	STDMETHOD_(IAIAction*,CreateCustomAction)(THIS_ int,cAIActor *,ulong) PURE;
	STDMETHOD_(void,EnactProxyLaunchAction)(THIS_ IAI *,void *) PURE;
	STDMETHOD_(void,EnactProxyJointRotateAction)(THIS_ IAI *,void *) PURE;
	STDMETHOD_(void,EnactProxyJointSlideAction)(THIS_ IAI *,void *) PURE;
	STDMETHOD_(void,EnactProxyJointScanAction)(THIS_ IAI *,void *) PURE;
	STDMETHOD_(void,EnactProxyCustomAction)(THIS_ int,IAI *,void *) PURE;
	STDMETHOD_(void,SaveAction)(THIS_ ITagFile *,IAIAction *) PURE;
	STDMETHOD_(IAIAction*,LoadAndCreateAction)(THIS_ ITagFile *,cAIActor *) PURE;
};
DEFINE_IIDSTRUCT(IAIBehaviorSet,IID_IAIBehaviorSet);
#undef INTERFACE

DECLARE_GUID(IAIMoveEnactor);
DECLARE_GUID(IAISoundEnactor);
DECLARE_GUID(IAISenses);
DECLARE_GUID(IAIPathfinder);

interface IAIMoveEnactor;
interface IAISoundEnactor;
interface IAISenses;
interface IAIPathfinder;

struct sAIAwareness;

#define INTERFACE IAI
DECLARE_GUID(IAI);
DECLARE_INTERFACE_(IAI,IUnknown)
{
	STDMETHOD_(int,GetID)(THIS) PURE;
	STDMETHOD_(void,NotifyGameEvent)(THIS_ void *) PURE;
	STDMETHOD_(void,NotifyTripwire)(THIS_ int,Bool) PURE;
	STDMETHOD_(void,Kill)(THIS) PURE;
	STDMETHOD_(void,Resurrect)(THIS) PURE;
	STDMETHOD_(Bool,IsDead)(THIS) PURE;
	STDMETHOD_(Bool,IsDying)(THIS) PURE;
	STDMETHOD_(void,Freeze)(THIS_ uint) PURE;
	STDMETHOD_(void,Unfreeze)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IAI,IID_IAI);
#undef INTERFACE

class cAIState;

#define INTERFACE IInternalAI
DECLARE_GUID(IInternalAI);
DECLARE_INTERFACE_(IInternalAI,IAI)
{
	STDMETHOD_(IInternalAI*,AccessOtherAI)(THIS_ int) PURE;
	STDMETHOD_(void,AccessAIs)(THIS_ IInternalAI * * *,int *) PURE;
	STDMETHOD(Init)(THIS_ int,IAIBehaviorSet *) PURE;
	STDMETHOD(End)(THIS) PURE;
	STDMETHOD(GetComponent)(THIS_ const char *,IAIComponent * *) PURE;
	STDMETHOD_(IAIComponent*,GetFirstComponent)(THIS_ tAIIter *) PURE;
	STDMETHOD_(IAIComponent*,GetNextComponent)(THIS_ tAIIter *) PURE;
	STDMETHOD_(void,GetComponentDone)(THIS_ tAIIter *) PURE;
	STDMETHOD_(IAIMoveEnactor*,AccesMoveEnactor)(THIS) PURE;
	STDMETHOD_(IAISoundEnactor*,AccessSoundEnactor)(THIS) PURE;
	STDMETHOD_(IAISenses*,AccessSenses)(THIS) PURE;
	STDMETHOD_(IAIPathfinder*,AccessPathfinder)(THIS) PURE;
	STDMETHOD_(IAIBehaviorSet*,AccessBehaviorSet)(THIS) PURE;
	// the rest of this is probably wrong
	STDMETHOD_(const cAIState*,GetState)(THIS) PURE;
	STDMETHOD_(uint,UpdatePathCell)(THIS) PURE;
	STDMETHOD_(void,GetRecentCells)(THIS_ cDynArray<uint> *) PURE;
	STDMETHOD_(float,GetGroundOffset)(THIS) PURE;
	STDMETHOD_(int,GetClosestPlayer)(THIS) PURE;
	STDMETHOD_(const sAIAwareness*,GetAwareness)(THIS_ int) PURE;
	STDMETHOD_(void,NotifySimStart)(THIS) PURE;
	STDMETHOD_(void,NotifySimEnd)(THIS) PURE;
	STDMETHOD_(ulong,NotifyDamage)(THIS_ const sDamageMsg *) PURE;
	STDMETHOD_(void,NotifyWeapon)(THIS_ int,int,int) PURE;
	STDMETHOD_(void,NotifyFastObj)(THIS_ int,int,const mxs_vector &) PURE;
	STDMETHOD_(void,NotifySound)(THIS_ const sSoundInfo *,const sAISoundType *) PURE;
	STDMETHOD_(void,NotifyFoundBody)(THIS_ int) PURE;
	STDMETHOD_(void,NotifyFoundSuspicious)(THIS_ int) PURE;
	STDMETHOD_(void,NotifyScriptCommand)(THIS_ unsigned int,void *) PURE;
	STDMETHOD_(void,NotifyProperty)(THIS_ IProperty *,const sPropertyListenMsg *) PURE;
	STDMETHOD_(void,NotifyDefend)(THIS_ const sAIDefendPoint *) PURE;
	STDMETHOD_(void,NotifySignal)(THIS_ const sAISignal *) PURE;
	STDMETHOD_(void,NotifyWitnessCombat)(THIS) PURE;
	STDMETHOD_(void,NotifyCollision)(THIS_ const sPhysListenMsg *) PURE;
	STDMETHOD_(Bool,IsNetworkProxy)(THIS) PURE;
	STDMETHOD_(void,StartProxyAction)(THIS_ IAIAction *,uint) PURE;
	STDMETHOD_(IAIAction *,GetTheActionOfType)(THIS_ int) PURE;
	STDMETHOD_(void,StopActionOfType)(THIS_ int) PURE;
	STDMETHOD_(void,SetGoal)(THIS_ cAIGoal *) PURE;
	STDMETHOD_(void,SetModeAndNotify)(THIS_ eAIMode) PURE;
	STDMETHOD_(void,SetIsBrainsOnly)(THIS_ Bool) PURE;
	STDMETHOD_(int,PreSave)(THIS) PURE;
	STDMETHOD_(Bool,Save)(THIS_ ITagFile *) PURE;
	STDMETHOD_(Bool,PostSave)(THIS) PURE;
	STDMETHOD_(Bool,PreLoad)(THIS) PURE;
	STDMETHOD_(Bool,Load)(THIS_ ITagFile *) PURE;
	STDMETHOD_(Bool,PostLoad)(THIS) PURE;
	// WARNING Dromed only
	STDMETHOD_(void,DebugDraw)(THIS) PURE;
	STDMETHOD_(void,DebugSetPrimitiveMove)(THIS_ const cAIMoveSuggestions *,const sAIMoveGoal *) PURE;
	STDMETHOD_(void,DebugGetPrimitiveMove)(THIS_ const cAIMoveSuggestions * *,const sAIMoveGoal * *) PURE;
};
DEFINE_IIDSTRUCT2(IInternalAI,IAI,IID_IInternalAI);
#undef INTERFACE

#endif // _LG_AI_H

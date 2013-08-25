/**********************
 * LGS Script Managers
 */

#ifndef _LG_SCRMANAGERS_H
#define _LG_SCRMANAGERS_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/objstd.h>
#include <lg/iiddef.h>

#include <lg/types.h>
#include <lg/defs.h>


// Forward declarations.
interface IAI;
interface IAIBehaviorSet;
interface IAIConversationManager;
interface IMotor;
interface IInputDevice;
interface ILinkQuery;
interface ILinkQueryDatabase;
interface IObjectQuery;
interface IProperty;
interface IRelation;
interface IRes;
interface IResType;
interface ISearchPath;
interface IStore;
interface IStoreFactory;
interface ITagFile;
interface ITrait;


LG_DECLARE_HANDLE(tAIIter);

#define INTERFACE IAIManager
DECLARE_GUID(IAIManager);
DECLARE_INTERFACE_(IAIManager,IUnknown)
{
	STDMETHOD(InstallBehaviorSet)(THIS_ IAIBehaviorSet *) PURE;
	STDMETHOD_(IAI*,GetAI)(THIS_ int) PURE;
	STDMETHOD_(Bool,CreateAI)(THIS_ int,const char *) PURE;
	STDMETHOD_(Bool,DestroyAI)(THIS_ int) PURE;
	STDMETHOD_(Bool,SelfSlayAI)(THIS_ int) PURE;
	STDMETHOD_(uint,CountAIs)(THIS) PURE;
	STDMETHOD_(IAI*,GetFirst)(THIS_ tAIIter *) PURE;
	STDMETHOD_(IAI*,GetNext)(THIS_ tAIIter *) PURE;
	STDMETHOD_(void,GetDone)(THIS_ tAIIter *) PURE;
	STDMETHOD(SetMotor)(THIS_ int,IMotor *) PURE;
	STDMETHOD(ResetMotionTags)(THIS_ int) PURE;
	STDMETHOD(NotifyFastObj)(THIS_ int,int,const mxs_vector &) PURE;
	STDMETHOD(NotifySound)(THIS_ const sSoundInfo *) PURE;
	STDMETHOD_(void,SetIgnoreSoundTime)(THIS_ uint) PURE;
	STDMETHOD_(Bool,StartConversation)(THIS_ int) PURE;
	STDMETHOD_(IAIConversationManager*,GetConversationManager)(THIS) PURE;
	STDMETHOD_(void,ListenToProperty)(THIS_ IProperty *) PURE;
	STDMETHOD_(void,ListenForCollisions)(THIS_ int) PURE;
	STDMETHOD_(void,UnlistenForCollisions)(THIS_ int) PURE;
};
DEFINE_IIDSTRUCT(IAIManager,IID_IAIManager);
#undef INTERFACE

#define INTERFACE IAIConversationManager
DECLARE_GUID(IAIConversationManager);
DECLARE_INTERFACE_(IAIConversationManager,IUnknown)
{
	STDMETHOD_(Bool,Start)(THIS_ int) PURE;
	STDMETHOD_(void,SetActorObj)(THIS_ int,int,int) PURE;
	STDMETHOD_(Bool,GetActorObj)(THIS_ int,int,int *) PURE;
	STDMETHOD_(void,RemoveActorObj)(THIS_ int,int) PURE;
	STDMETHOD_(int,GetNumActors)(THIS_ int) PURE;
	STDMETHOD_(int,GetActorIDs)(THIS_ int,int *) PURE;
	STDMETHOD_(void,Frame)(THIS) PURE;
	STDMETHOD_(void,ListenConversationEnd)(THIS_ void (__cdecl *)(int)) PURE;
	STDMETHOD_(void,NotifyConversationEnd)(THIS_ int) PURE;
};
DEFINE_IIDSTRUCT(IAIConversationManager,IID_IAIConversationManager);;
#undef INTERFACE

struct sInputDeviceIter
{
	void* pData;
};

#define INTERFACE IInputManager
DECLARE_GUID(IInputManager);
DECLARE_INTERFACE_(IInputManager,IUnknown)
{
	STDMETHOD_(void,IterStart)(THIS_ sInputDeviceIter *,GUID) PURE;
	STDMETHOD_(void,IterNext)(THIS_ sInputDeviceIter *) PURE;
	STDMETHOD_(IInputDevice*,IterGet)(THIS_ sInputDeviceIter *) PURE;
	STDMETHOD_(Bool,IterFinished)(THIS_ sInputDeviceIter *) PURE;
};
DEFINE_IIDSTRUCT(IInputManager,IID_IInputManager);
#undef INTERFACE

struct sRelationIter
{
    short id;
	IRelation* rel;
};

#define INTERFACE ILinkManager
DECLARE_GUID(ILinkManager);
DECLARE_INTERFACE_(ILinkManager,IUnknown)
{
/*** GetRelation - Get the interface for direct access to a link flavor.
 *  	= IRelation* - Relation interface.
 *  	: short - ID of the link flavor.
 */
	STDMETHOD_(IRelation*,GetRelation)(THIS_ short) PURE;
/*** GetRelationNamed - Lookup a relation by name.
 *  	= IRelation* - Relation interface.
 *  	: const char * - Link flavor name.
 */
	STDMETHOD_(IRelation*,GetRelationNamed)(THIS_ const char *) PURE;
	STDMETHOD(Notify)(THIS_ ulong,void *) PURE;
/*** IterStart - Begin iterating all relations.
 *  	= long -
 *  	: sRelationIter * - Data used by the iterator.
 */
	STDMETHOD(IterStart)(THIS_ sRelationIter *) PURE;
/*** IterNext - Get the next relation.
 *  	= Bool - Returns false when there are no more relations.
 *  	: sRelationIter * - Data used by the iterator.
 *  	: short * - Puts the current relation ID into this pointer.
 */
	STDMETHOD_(Bool,IterNext)(THIS_ sRelationIter *,short *) PURE;
/*** IterStop - Ends the iteration.
 *  	= long -
 *  	: sRelationIter * - Data used by the iterator.
 */
	STDMETHOD(IterStop)(THIS_ sRelationIter *) PURE;
/*** Add - Add a link between two objects.
 *  	= long - The ID of the created link.
 *  	: int - ID of the source object.
 *  	: int - ID of the destination object.
 *  	: short - Flavor of the link.
 */
	STDMETHOD_(long,Add)(THIS_ int,int,short) PURE;
/*** AddFull - Add a link with data between two objects.
 *  	= long - The ID of the created link.
 *  	: int - ID of the source object.
 *  	: int - ID of the destination object.
 *  	: short - Flavor of the link.
 *  	: void * - Pointer to the data for the link.
 */
	STDMETHOD_(long,AddFull)(THIS_ int,int,short,void *) PURE;
/*** Remove - Deletes a link.
 *  	= long -
 *  	: long - ID of the link to delete.
 */
	STDMETHOD(Remove)(THIS_ long) PURE;
/*** Get - Retrieve information about a link.
 *  	= Bool - True if the link is valid.
 *  	: long - ID of the link to query.
 *  	: sLink * - Address that the information will be copied to.
 */
	STDMETHOD_(Bool,Get)(THIS_ long,sLink *) const PURE;
/*** SetData - Set the associated data for a link.
 *  	= long -
 *  	: long - ID of the link to change.
 *  	: void * - Pointer to the data that will be copied into the link.
 */
	STDMETHOD(SetData)(THIS_ long,void *) PURE;
	// Is this pointer Alloced? Are we supposed to Free?
/*** GetData - Retreive the associated data for a link.
 *  	= void * - Pointer to the link data. (Is it alloced? Are we supposed to free it?)
 *  	: long - ID of the link to query.
 */
	STDMETHOD_(void*,GetData)(THIS_ long) PURE;
/*** Query - Get all links of a particular flavor between two objects. Any parameter can be set to 0 to query all objects or flavors.
 *  	= ILinkQuery * - The query instance.
 *  	: int - ID of the source object.
 *  	: int - ID of the destination object.
 *  	: short - Flavor of the links.
 */
	STDMETHOD_(ILinkQuery*,Query)(THIS_ int,int,short) PURE;
	STDMETHOD_(long,RemapOnLoad)(THIS_ long) PURE;
	// Can touch the ones below, but I recommend using IRelation
/*** GetSingleLink - Retrieve a link between two objects. Will cause an error if there is more than one link of the same flavor.
 *  	= long - The link ID.
 *  	: short - Flavor of the links.
 *  	: int - ID of the source object.
 *  	: int - ID of the destination object.
 */
	STDMETHOD_(long,GetSingleLink)(THIS_ short,int,int) PURE;
/*** AnyLinks - Check if there is a link between two objects.
 *  	= Bool - True if there is a link.
 *  	: short - Flavor of the links.
 *  	: int - ID of the source object.
 *  	: int - ID of the destination object.
 */
	STDMETHOD_(Bool,AnyLinks)(THIS_ short,int,int) PURE;
};
DEFINE_IIDSTRUCT(ILinkManager,IID_ILinkManager);
#undef INTERFACE

#define INTERFACE ILinkManagerInternal
DECLARE_GUID(ILinkManagerInternal);
DECLARE_INTERFACE_(ILinkManagerInternal,ILinkManager)
{
	STDMETHOD_(short,AddRelation)(THIS_ IRelation *) PURE;
	STDMETHOD(RemoveRelation)(THIS_ short) PURE;
	STDMETHOD(ReplaceRelation)(THIS_ short,IRelation *) PURE;
	STDMETHOD(AddQueryDB)(THIS_ ILinkQueryDatabase *,ulong) PURE;
	STDMETHOD(RemoveQueryDB)(THIS_ ILinkQueryDatabase *,ulong) PURE;
	STDMETHOD_(uint,Lock)(THIS) PURE;
	STDMETHOD(Unlock)(THIS_ uint) PURE;
	STDMETHOD_(long,GetLockCount)(THIS) PURE;
	STDMETHOD_(Bool,LinkValid)(THIS_ long,uint) PURE;
	STDMETHOD(LinkBirth)(THIS_ long) PURE;
	STDMETHOD_(Bool,LinkDeath)(THIS_ long) PURE;
};
DEFINE_IIDSTRUCT2(ILinkManagerInternal,ILinkManager,IID_ILinkManagerInternal);
#undef INTERFACE

struct sPropertyIter
{
	int id;
};

#define INTERFACE IPropertyManager
DECLARE_GUID(IPropertyManager);
DECLARE_INTERFACE_(IPropertyManager,IUnknown)
{
/*** GetProperty - Get the interface for direct access to a property type.
 *  	= IProperty* - Property interface.
 *  	: int - ID of the property class.
 */
	STDMETHOD_(IProperty*,GetProperty)(THIS_ int) const PURE;
/*** GetPropertyNamed - Lookup a property by name.
 *  	= IProperty* - Property interface.
 *  	: const char * - Name of the property.
 */
	STDMETHOD_(IProperty*,GetPropertyNamed)(THIS_ const char *) const PURE;
	STDMETHOD(Notify)(THIS_ ulong,void *) PURE;
/*** BeginIter - Start iterating all property types.
 *  	= long -
 *  	: sPropertyIter * - Data used by the iterator.
 */
	STDMETHOD(BeginIter)(THIS_ sPropertyIter *) PURE;
/*** NextIter - Get the next property.
 *  	= IProperty* - Property interface. Returns NULL when there are no more properties.
 *  	: sPropertyIter * - Structure that receives the property ID.
 */
	STDMETHOD_(IProperty*,NextIter)(THIS_ sPropertyIter *) PURE;
/*** AddProperty - Create a new property class. Should only be used by the game engine.
 *  	= Bool - True on success.
 *  	: IProperty * - The property interface.
 *  	: int * - Receives the property ID.
 */
	STDMETHOD_(Bool,AddProperty)(THIS_ IProperty *,int *) PURE;
/*** DelProperty - Removes a property class. Should never be used.
 *  	= Bool - True on success.
 *  	: IProperty * - The property interface.
 */
	STDMETHOD_(Bool,DelProperty)(THIS_ IProperty *) PURE;
};
DEFINE_IIDSTRUCT(IPropertyManager,IID_IPropertyManager);
#undef INTERFACE

#define INTERFACE IResMan
DECLARE_GUID(IResMan);
DECLARE_INTERFACE_(IResMan,IUnknown)
{
	STDMETHOD_(ISearchPath*,NewSearchPath)(THIS_ const char *) PURE;
	STDMETHOD_(void,SetDefaultPath)(THIS_ ISearchPath *) PURE;
	STDMETHOD_(void,SetGlobalContext)(THIS_ ISearchPath *) PURE;
	STDMETHOD_(void,SetDefaultVariants)(THIS_ ISearchPath *) PURE;
	STDMETHOD_(IRes*,Bind)(THIS_ const char *,const char *,ISearchPath *,const char *,uint) PURE;
	STDMETHOD_(void,BindAll)(THIS_ const char *,const char *,ISearchPath *,void (__cdecl *)(IRes *,IStore *,void *),void *,const char *,uint) PURE;
	STDMETHOD_(IRes*,BindSpecific)(THIS_ const char *,const char *,IStore *,IStore *,uint) PURE;
	STDMETHOD_(IRes *,Retype)(THIS_ IRes *,const char *,uint) PURE;
	STDMETHOD_(IRes*,Lookup)(THIS_ const char *,const char *,const char *) PURE;
	STDMETHOD_(IStore*,GetStore)(THIS_ const char *) PURE;
	STDMETHOD_(Bool,RegisterResType)(THIS_ IResType *) PURE;
	STDMETHOD_(Bool,RegisterStoreFactory)(THIS_ IStoreFactory *) PURE;
	STDMETHOD_(void,UnregisterResType)(THIS_ IResType *) PURE;
	STDMETHOD_(void,MarkForRefresh)(THIS_ IRes *) PURE;
	STDMETHOD_(void,GlobalRefresh)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IResMan,IID_IResMan);
#undef INTERFACE

struct Datapath;
typedef int (__cdecl *PersistSaveLoadFunc)(void*,void*,uint);

class cScrTraceHashKey
{
	// sprintf(m_Combo, "%s:%d", msgName, objID)
	char m_Combo[40];
};
class cScrTrace
{
	int m_HostObjID;
	eScrTraceAction m_TraceAction;
	int m_iTraceLine;
	cScrTraceHashKey m_TraceHashKey;
};
struct sScrMsg;

#define INTERFACE IScriptMan
DECLARE_GUID(IScriptMan);
DECLARE_INTERFACE_(IScriptMan,IUnknown)
{
	STDMETHOD(GameInit)(THIS) PURE;
	STDMETHOD(GameEnd)(THIS) PURE;
	STDMETHOD(BeginScripts)(THIS) PURE;
	STDMETHOD(EndScripts)(THIS) PURE;
	STDMETHOD(SetModuleDatapath)(THIS_ const Datapath *) PURE;
	STDMETHOD(AddModule)(THIS_ const char *) PURE;
	STDMETHOD(RemoveModule)(THIS_ const char *) PURE;
	STDMETHOD(ClearModules)(THIS) PURE;
	STDMETHOD(ExposeService)(THIS_ IUnknown *,REFGUID) PURE;
	STDMETHOD_(IUnknown *,GetService)(THIS_ REFGUID) PURE;
	STDMETHOD_(const sScrClassDesc*,GetFirstClass)(THIS_ tScrIter *) PURE;
	STDMETHOD_(const sScrClassDesc*,GetNextClass)(THIS_ tScrIter *) PURE;
	STDMETHOD_(void,EndClassIter)(THIS_ tScrIter *) PURE;
	STDMETHOD_(const sScrClassDesc*,GetClass)(THIS_ const char *) PURE;
	STDMETHOD(SetObjScripts)(THIS_ int,const char * *,uint) PURE;
/*** ForgetObj - Drop the scripts for a single object. The scripts will be restarted when the Scripts property is reloaded.
 *  	= long -
 *  	: int - Object ID
 */
	STDMETHOD(ForgetObj)(THIS_ int) PURE;
/*** ForgetAllObjs - Terminates all scripts.
 *  	= long -
 */
	STDMETHOD(ForgetAllObjs)(THIS) PURE;
	STDMETHOD_(Bool,WantsMessage)(THIS_ int,const char *) PURE;
/*** SendMessage - Send a message to another object. Returns when the message has been completely processed.
 *  	= long -
 *  	: sScrMsg * - The message that will be sent. Can be allocated on the stack.
 *  	: sMultiParm * - The return result of the message. This is the pRet argument in ReceiveMessage. A string or vector type should be freed by the caller.
 */
	STDMETHOD(SendMessage)(THIS_ sScrMsg *,sMultiParm *) PURE;
/*** KillTimedMessage - Abort a message that was sent with SetTimedMessage or SetTimedMessage2.
 *  	: tScrTimer - The pointer returned from SetTimedMessage or SetTimedMessage2.
 */
	STDMETHOD_(void,KillTimedMessage)(THIS_ tScrTimer) PURE;
	STDMETHOD_(int,PumpMessages)(THIS) PURE;
/*** PostMessage - Send a message without waiting for a reply.
 *  	: sScrMsg * - The message to post. Must be allocated on the heap.
 */
	STDMETHOD_(void,PostMessage)(THIS_ sScrMsg *) PURE;
/*** SetTimedMessage - Send a message at some future time.
 *  	= tScrTimer - Pointer to the timer struct for the queued message.
 *  	: sScrMsg * - The message to send. Must be allocated on the heap. It doesn't have to be, but most timed messages are "Timer" in a sScrTimerMsg struct.
 *  	: ulong - How many milliseconds to wait before sending the message.
 *  	: eScrTimedMsgKind - Whether to send the message just once, or every time the period lapses.
 */
	STDMETHOD_(tScrTimer,SetTimedMessage)(THIS_ sScrMsg *,ulong,eScrTimedMsgKind) PURE;
/*** SendMessage2 - Construct and send a message.
 *  	= cMultiParm - The reply from the message. Aggregate return. A string or vector type should be freed by the caller.
 *  	: int - The source object. sScrMsg::from
 *  	: int - The destination object. sScrMsg::to
 *  	: const char * - The message string. sScrMsg::message
 *  	: const cMultiParm & - Extra data. sScrMsg::data
 *  	: const cMultiParm & - Extra data. sScrMsg::data2
 *  	: const cMultiParm & - Extra data. sScrMsg::data3
 */
	STDMETHOD_(cMultiParm*,SendMessage2)(THIS_ cMultiParm &,int,int,const char *,const cMultiParm &,const cMultiParm &,const cMultiParm &) PURE;
/*** PostMessage2 - Construct and post a message. The parameters are copied, so they can be on the stack.
 *  	: int - The source object. sScrMsg::from
 *  	: int - The destination object. sScrMsg::to
 *  	: const char * - The message string. sScrMsg::message
 *  	: const cMultiParm & - Extra data. sScrMsg::data
 *  	: const cMultiParm & - Extra data. sScrMsg::data2
 *  	: const cMultiParm & - Extra data. sScrMsg::data3
 *  	: ulong - Message options. Not in Thief 1. sScrMsg::flags
 */
#if (_DARKGAME==1)
	STDMETHOD_(void,PostMessage2)(THIS_ int,int,const char *,const cMultiParm &,const cMultiParm &,const cMultiParm &) PURE;
#else
	STDMETHOD_(void,PostMessage2)(THIS_ int,int,const char *,const cMultiParm &,const cMultiParm &,const cMultiParm &,ulong) PURE;
#endif
/*** SetTimedMessage2 - Construct and send a "Timer" message.
 *  	= tScrTimer - Pointer to the timer struct for the queued message.
 *  	: int - The object to send the message to.
 *  	: const char * - The message name. sScrTimedMsg::name
 *  	: ulong - How many milliseconds to wait before sending the message.
 *  	: eScrTimedMsgKind - Whether to send the message just once, or every time the period lapses.
 *  	: const cMultiParm & - Extra data. sScrMsg::data
 */
	STDMETHOD_(tScrTimer,SetTimedMessage2)(THIS_ int,const char *,ulong,eScrTimedMsgKind,const cMultiParm &) PURE;
/*** IsScriptDataSet - Checks if the persistent script data is valid.
 *  	= Bool - Returns true if the data exists.
 *  	: const sScrDatumTag * - Description of the data to check for.
 */
	STDMETHOD_(Bool,IsScriptDataSet)(THIS_ const sScrDatumTag *) PURE;
/*** GetScriptData - Returns the data stored in the persistent script database.
 *	= long - Returns zero on success.
 *	: const sScrDatumTag * - Description of the data to retrieve.
 *	: sMultiParm * - Address that the data will be stored in. String and vector types will have allocated members.
 */
	STDMETHOD(GetScriptData)(THIS_ const sScrDatumTag *,sMultiParm *) PURE;
/*** SetScriptData - Copies arbitrary data into a persistent database.
 *	= long - Returns zero on success.
 *	: const sScrDatumTag * - Description of the data being saved.
 *	: const sMultiParm * - The data that will be saved.
 */
	STDMETHOD(SetScriptData)(THIS_ const sScrDatumTag *,const sMultiParm *) PURE;
/*** ClearScriptData - Removes a data item from the persistent script database.
 *	= long - Returns zero on success.
 *	: const sScrDatumTag * - Description of the data being deleted.
 *	: sMultiParm * - Receives the data that was stored in the database.
 */
	STDMETHOD(ClearScriptData)(THIS_ const sScrDatumTag *,sMultiParm *) PURE;
	STDMETHOD(AddTrace)(THIS_ int,char *,eScrTraceAction,int) PURE;
	STDMETHOD(RemoveTrace)(THIS_ int,char *) PURE;
	STDMETHOD_(Bool,GetTraceLine)(THIS_ int) PURE;
	STDMETHOD_(void,SetTraceLine)(THIS_ int,int) PURE;
	STDMETHOD_(int,GetTraceLineMask)(THIS) PURE;
	STDMETHOD_(void,SetTraceLineMask)(THIS_ int) PURE;
	STDMETHOD_(const cScrTrace*,GetFirstTrace)(THIS_ tScrIter *) PURE;
	STDMETHOD_(const cScrTrace*,GetNextTrace)(THIS_ tScrIter *) PURE;
	STDMETHOD_(void,EndTraceIter)(THIS_ tScrIter *) PURE;
	STDMETHOD(SaveLoad)(THIS_ PersistSaveLoadFunc,void *,Bool) PURE;
	STDMETHOD_(void,PostLoad)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IScriptMan,IID_IScriptMan);
#undef INTERFACE

struct sDispatchListenerDesc;
struct sDispatchMsg;

typedef int (__cdecl *DispatchListenFunc)(const sDispatchMsg*, const sDispatchListenerDesc*);
struct sDispatchListenerDesc
{
	const IID*	pIID_Listener;
	ulong	dwFlags;
	DispatchListenFunc	pfnListener;
	void*	pData;
};
struct sDispatchMsg
{
	ulong	dwEventId;
	ulong	dwDispatchId;
};
enum eSimEvent
{
	kSimStart   = 1,
	kSimStop    = 2,
	kSimSuspend = 4,
	kSimResume  = 8
};

#define INTERFACE ISimManager
DECLARE_GUID(ISimManager);
DECLARE_INTERFACE_(ISimManager,IUnknown)
{
	// IBaseSimMan
	STDMETHOD(Listen)(THIS_ const sDispatchListenerDesc *) PURE;
	STDMETHOD(Unlisten)(THIS_ const GUID *) PURE;
	STDMETHOD(SendMsg)(THIS_ const sDispatchMsg *) PURE;
	STDMETHOD(StartSim)(THIS) PURE;
	STDMETHOD(SuspendSim)(THIS) PURE;
	STDMETHOD(StopSim)(THIS) PURE;
	STDMETHOD_(ulong,LastMsg)(THIS) PURE;
	STDMETHOD(DatabaseMsg)(THIS_ ulong,ITagFile *) PURE;
};
DEFINE_IIDSTRUCT(ISimManager,IID_ISimManager);
#undef INTERFACE

#define INTERFACE
DECLARE_GUID(IStorageManager);
DECLARE_INTERFACE_(IStorageManager,IUnknown)
{
	STDMETHOD_(void,RegisterFactory)(THIS_ IStoreFactory *) PURE;
	STDMETHOD_(IStore*,GetStore)(THIS_ const char *,Bool) PURE;
	STDMETHOD_(Bool,HeteroStoreExists)(THIS_ IStore *,char * const *) PURE;
	STDMETHOD_(IStore*,CreateSubstore)(THIS_ IStore *,const char *) PURE;
	STDMETHOD_(void,SetGlobalContext)(THIS_ ISearchPath *) PURE;
	STDMETHOD_(void,SetDefaultVariants)(THIS_ ISearchPath *) PURE;
	STDMETHOD_(ISearchPath*,NewSearchPath)(THIS_ const char *) PURE;
	STDMETHOD_(void,Close)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IStorageManager,IID_IStorageManager);
#undef INTERFACE

struct sTraitPredicate
{
	Bool (__cdecl *TraitPredicateFunc)(int,void*);
	void* pData;
};
enum eTraitQuery
{
	kTraitQueryFull = 0x80000000,
	kTraitQueryDefault = 0,
	kTraitQueryMetaProps = 1,
	kTraitQueryChildren = 2,
};
typedef void (__stdcall *TraitListenFunc)(const sHierarchyMsg*,void*);

#define INTERFACE ITraitManager
DECLARE_GUID(ITraitManager);
DECLARE_INTERFACE_(ITraitManager,IUnknown)
{
	STDMETHOD(CreateBaseArchetype)(THIS_ const char *,int *) PURE;
	STDMETHOD_(int,CreateArchetype)(THIS_ const char *,int) PURE;
	STDMETHOD_(int,CreateConcreteArchetype)(THIS_ const char *,int) PURE;
	STDMETHOD_(int,GetArchetype)(THIS_ int) PURE;
	STDMETHOD(SetArchetype)(THIS_ int,int) PURE;
	STDMETHOD_(Bool,IsArchetype)(THIS_ int) PURE;
	STDMETHOD_(int,RootMetaProperty)(THIS) PURE;
	STDMETHOD_(int,CreateMetaProperty)(THIS_ const char *,int) PURE;
	STDMETHOD_(Bool,IsMetaProperty)(THIS_ int) PURE;
	STDMETHOD(AddObjMetaProperty)(THIS_ int,int) PURE;
	STDMETHOD(AddObjMetaPropertyPrioritized)(THIS_ int,int,long) PURE;
	STDMETHOD(RemoveObjMetaProperty)(THIS_ int,int) PURE;
	STDMETHOD(RemoveObjMetaPropertyPrioritized)(THIS_ int,int,long) PURE;
	STDMETHOD_(Bool,ObjHasDonor)(THIS_ int,int) PURE;
	STDMETHOD_(Bool,ObjHasDonorIntrinsically)(THIS_ int,int) PURE;
	STDMETHOD_(Bool,ObjIsDonor)(THIS_ int) PURE;
	STDMETHOD_(IObjectQuery*,Query)(THIS_ int,ulong) PURE;
	STDMETHOD_(ITrait*,CreateTrait)(THIS_ const sTraitDesc *,const sTraitPredicate *) PURE;
	STDMETHOD(Listen)(THIS_ TraitListenFunc,void *) PURE;
	STDMETHOD(AddObject)(THIS_ int,int) PURE;
	STDMETHOD(RemoveObject)(THIS) PURE;
	STDMETHOD(Notify)(THIS_ ulong,void *) PURE;
};
DEFINE_IIDSTRUCT(ITraitManager,IID_ITraitManager);
#undef INTERFACE

#endif // _LG_SCRMANAGERS_H

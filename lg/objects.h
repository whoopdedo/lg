/**********************
 * LGS Objects &c.
 */

#ifndef _LG_OBJECTS_H
#define _LG_OBJECTS_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#include <lg/types.h>
#include <lg/defs.h>

interface ILinkQuery;
interface IProperty;
interface IIntProperty;
interface ITagFile;

#define INTERFACE IObjectQuery
DECLARE_GUID(IObjectQuery);
DECLARE_INTERFACE_(IObjectQuery,IUnknown)
{
	STDMETHOD_(Bool,Done)(THIS) PURE;
	STDMETHOD_(int,Object)(THIS) PURE;
	STDMETHOD(Next)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IObjectQuery,IID_IObjectQuery);
#undef INTERFACE

typedef void (__cdecl *ObjSysListenFunc)(int,unsigned long,void*);

struct sObjListenerDesc
{
	ObjSysListenFunc pfnListenFunc;
	void* pData;
};

typedef int tObjListenerHandle;

struct sObjPartitionFilter
{
};

#define INTERFACE IObjectSystem
DECLARE_GUID(IObjectSystem);
DECLARE_INTERFACE_(IObjectSystem,IUnknown)
{
	STDMETHOD_(int,Create)(THIS_ int,ulong) PURE;
	STDMETHOD_(int,BeginCreate)(THIS_ int,ulong) PURE;
	STDMETHOD(EndCreate)(THIS_ int) PURE;
	STDMETHOD(Destroy)(THIS_ int) PURE;
	STDMETHOD(CloneObject)(THIS_ int,int) PURE;
	STDMETHOD(Reset)(THIS) PURE;
	STDMETHOD_(Bool,Exists)(THIS_ int) PURE;
	STDMETHOD(NameObject)(THIS_ int,const char*) PURE;
	STDMETHOD_(const char*,GetName)(THIS_ int) PURE;
	STDMETHOD_(int,GetObjectNamed)(THIS_ const char*) PURE;
	STDMETHOD(SetObjTransience)(THIS_ int,Bool) PURE;
	STDMETHOD_(Bool,ObjIsTransient)(THIS_ int) PURE;
	STDMETHOD(SetObjImmobility)(THIS_ int,Bool) PURE;
	STDMETHOD_(Bool,ObjIsImmobile)(THIS_ int) PURE;
	STDMETHOD_(IObjectQuery*,Iter)(THIS_ ulong) PURE;
	STDMETHOD_(IProperty*,GetCoreProperty)(THIS_ ulong) PURE;
	STDMETHOD(DatabaseNotify)(THIS_ ulong,void*) PURE;
	STDMETHOD(PurgeObjects)(THIS) PURE;
	STDMETHOD_(tObjListenerHandle,Listen)(THIS_ sObjListenerDesc*) PURE;
	STDMETHOD(Unlisten)(THIS_ tObjListenerHandle) PURE;
	STDMETHOD_(int,MaxObjID)(THIS) PURE;
	STDMETHOD_(int,MinObjID)(THIS) PURE;
	STDMETHOD_(int,ActiveObjects)(THIS) PURE;
	STDMETHOD(Lock)(THIS) PURE;
	STDMETHOD(Unlock)(THIS) PURE;
	STDMETHOD_(Bool,IsObjSavePartition)(THIS_ int,ulong) PURE;
	STDMETHOD_(Bool,IsObjLoadPartition)(THIS_ int,ulong) PURE;
	STDMETHOD_(ulong,ObjDefaultPartition)(THIS_ int) PURE;
	STDMETHOD_(int,RemapOnLoad)(THIS_ int) PURE;
	STDMETHOD(SetSubPartitionFilter)(THIS_ ulong,const sObjPartitionFilter*) PURE;
};
DEFINE_IIDSTRUCT(IObjectSystem,IID_IObjectSystem);
#undef INTERFACE

struct sObjBounds
{
	int iMinObjID;
	int iMaxObjID;
};

#define INTERFACE IObjIDSink
DECLARE_GUID(IObjIDSink);
DECLARE_INTERFACE_(IObjIDSink,IUnknown)
{
	STDMETHOD_(void,OnObjIDSpaceResize)(THIS_ const sObjBounds&) PURE;
};
DEFINE_IIDSTRUCT(IObjIDSink,IID_IObjIDSink);
#undef INTERFACE

#define INTERFACE IObjIDManager
DECLARE_GUID(IObjIDManager);
DECLARE_INTERFACE_(IObjIDManager,IUnknown)
{
	STDMETHOD_(sObjBounds*,GetObjIDBounds)(THIS_ sObjBounds&) PURE;
	STDMETHOD(ResizeObjIDSpace)(THIS_ const sObjBounds&) PURE;
	STDMETHOD(Connect)(THIS_ IObjIDSink*) PURE;
	STDMETHOD(Disconnect)(THIS_ IObjIDSink*) PURE;
};
DEFINE_IIDSTRUCT(IObjIDManager,IID_IObjIDManager);
#undef INTERFACE

enum eDonorCacheFlags
{
	kDonorCacheSpew = 1,
	kDonorCachePermitConcrete = 2,
	kDonorCacheLoading = 4
};

struct sDonorCacheParams
{
	ulong max_cache;
	ulong flags;
};

struct sDonorCacheStats
{
	ulong adds;
	ulong drops;
	ulong hits;
	ulong misses;
	ulong overwrites;
	ulong flushes;
};

#define INTERFACE IDonorCache
DECLARE_GUID(IDonorCache);
DECLARE_INTERFACE_(IDonorCache,IUnknown)
{
	STDMETHOD_(uint,NewTrait)(THIS_ const sTraitDesc*) PURE;
	STDMETHOD(SetDonor)(THIS_ int,uint,int,int) PURE;
	STDMETHOD_(Bool,GetDonor)(THIS_ int,uint,int *,int *) PURE;
	STDMETHOD(Clear)(THIS) PURE;
	STDMETHOD(Flush)(THIS_ int,ulong) PURE;
	STDMETHOD(FlushObjSet)(THIS_ IObjectQuery*,uint) PURE;
	STDMETHOD(SetParams)(THIS_ const sDonorCacheParams*) PURE;
	STDMETHOD(GetParams)(THIS_ sDonorCacheParams*) PURE;
	STDMETHOD(GetTotalStats)(THIS_ sDonorCacheStats*) PURE;
	STDMETHOD(GetStatsByTrait)(THIS_ uint,sDonorCacheStats*) PURE;
	STDMETHOD(GetByTraitName)(THIS_ const char*,sDonorCacheStats*) PURE;
	STDMETHOD(GetMaxID)(THIS) PURE;
	STDMETHOD(GetCacheEntries)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IDonorCache,IID_IDonorCache);
#undef INTERFACE

#define INTERFACE IDonorQuery
DECLARE_GUID(IDonorQuery);
DECLARE_INTERFACE_(IDonorQuery,IUnknown)
{
	STDMETHOD_(Bool,Done)(THIS) PURE;
	STDMETHOD_(int,Object)(THIS) PURE;
	STDMETHOD(Next)(THIS) PURE;
	STDMETHOD_(long,Priority)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IDonorQuery,IID_IDonorQuery);
#undef INTERFACE

#define INTERFACE ITrait
DECLARE_GUID(ITrait);
DECLARE_INTERFACE_(ITrait,IUnknown)
{
	STDMETHOD_(const sTraitDesc*,Describe)(THIS) PURE;
	STDMETHOD_(Bool,PossessedBy)(THIS_ int) PURE;
	STDMETHOD_(Bool,IntrinsicTo)(THIS_ int) PURE;
	STDMETHOD(Touch)(THIS_ int) PURE;
	STDMETHOD_(int,GetDonor)(THIS_ int) PURE;
	STDMETHOD_(IObjectQuery*,GetAllDonors)(THIS_ int) PURE;
	STDMETHOD_(IObjectQuery*,GetAllHeirs)(THIS_ int,ulong) PURE;
};
DEFINE_IIDSTRUCT(ITrait,IID_ITrait);
#undef INTERFACE

struct sChainedEvent
{
	int type;
	int category; // physics - 0x10, damage - 0x1c, act/react - 0x28
	sChainedEvent* next;
};
struct sDamage
{
	int damage;
	int type;
};
struct sImpact
{
	float intensity;
};
struct sDamageMsg
{
	sChainedEvent event;
	int type;
	int dest;
	int source;
	union {
		sImpact* impact;
		sDamage* damage;
		int slay;
	} data;
};

typedef ulong (__stdcall *DamageFilterFunc)(int,int,sDamage *,void *);
typedef ulong (__stdcall *DamageListenerFunc)(const sDamageMsg *,void *);

#define INTERFACE IDamageModel
DECLARE_GUID(IDamageModel);
DECLARE_INTERFACE_(IDamageModel,IUnknown)
{
	STDMETHOD_(ulong,HandleImpact)(THIS_ int,int,sImpact *,sChainedEvent *) PURE;
	STDMETHOD_(ulong,DamageObject)(THIS_ int,int,sDamage *,sChainedEvent *,Bool) PURE;
	STDMETHOD_(ulong,SlayObject)(THIS_ int,int,sChainedEvent *) PURE;
	STDMETHOD_(ulong,TerminateObject)(THIS_ int,sChainedEvent *) PURE;
	STDMETHOD_(ulong,ResurrectObject)(THIS_ int, int, sChainedEvent *) PURE;
	STDMETHOD(Filter)(THIS_ DamageFilterFunc,void*) PURE;
	STDMETHOD(Listen)(THIS_ ulong,DamageListenerFunc,void*) PURE;
};
DEFINE_IIDSTRUCT(IDamageModel,IID_IDamageModel);
#undef INTERFACE

#pragma pack(push,2)
struct sContainIter
{
	Bool Done;
	int ContainType;
	long Link;
	int Object;
	short Count;
	ILinkQuery* Query;
	int MinType;
	int MaxType;
};
#pragma pack(pop)

typedef Bool (__cdecl *ContainsListenFunc)(eContainsEvent,int,int,int,void*);
#define INTERFACE IContainSys
DECLARE_GUID(IContainSys);
DECLARE_INTERFACE_(IContainSys,IUnknown)
{
	STDMETHOD(Listen)(THIS_ int,ContainsListenFunc,void *) PURE;
	STDMETHOD_(Bool,CheckCallback)(THIS_ int,eContainsEvent,int,int,int) PURE;
/*** Add - Adds an object to a container.
 *	= long -
 *	: int - The container to add the object to.
 *	: int - The object to add.
 *	: int - The contains type.
 *	: uint - Combine the object if set to 1.
 */
	STDMETHOD(Add)(THIS_ int,int,int,uint) PURE;
/*** Remove - Remove an object from a container.
 *	= long -
 *	: int - The container to remove the object from.
 *	: int - The object to remove.
 */
	STDMETHOD(Remove)(THIS_ int,int) PURE;
	STDMETHOD(SetContainType)(THIS_ int,int,int) PURE;
/*** IsHeld - Check if an object is contained by another.
 *	= int - The contains type, or MAXINT if there is no link.
 *	: int - The container.
 *	: int - The contained object.
 */
	STDMETHOD_(int,IsHeld)(THIS_ int,int) PURE;
/*** Contains - Recursively check if an object is contained by another.
 *	= Bool - True if the object is in the container, or in something that is held by the container.
 *	: int - The container.
 *	: int - The contained object.
 */
	STDMETHOD_(Bool,Contains)(THIS_ int,int) PURE;
	STDMETHOD_(int,GetContainer)(THIS_ int) PURE;
	STDMETHOD(MoveAllContents)(THIS_ int,int,int) PURE;
	STDMETHOD(CombineTry)(THIS_ int,int,int) PURE;
	STDMETHOD_(int,CombineCount)(THIS_ int,int) PURE;
	STDMETHOD(CombineAdd)(THIS_ int,int,int,ulong) PURE;
	STDMETHOD_(Bool,CanCombine)(THIS_ int,int,int) PURE;
	STDMETHOD_(Bool,CanCombineContainer)(THIS_ int,int,int) PURE;
	STDMETHOD_(int,RemoveFromStack)(THIS_ int,ulong,int) PURE;
/*** StackAdd - Adds a value to the stack count of an object.
 *	= int -
 *	: int - The object to modify.
 *	: int - The amount to add to the stack count. May be negative.
 *	: ulong - If 1, the object will be destroyed if its stack count reaches zero.
 */
	STDMETHOD_(int,StackAdd)(THIS_ int,int,ulong) PURE;
	STDMETHOD_(IIntProperty*,StackCountProp)(THIS) PURE;
/*** IterStart - Starts an iteration through an object's contents.
 *	= sContainIter* - Pointer to a structure that will receive the iteration data.
 *	: int - The container to be iterated.
 */
	STDMETHOD_(sContainIter*,IterStart)(THIS_ int) PURE;
	STDMETHOD_(sContainIter*,IterStartType)(THIS_ int,int,int) PURE;
	STDMETHOD_(sContainIter*,IterStartInherits)(THIS_ int) PURE;
	STDMETHOD_(sContainIter*,IterStartInheritsType)(THIS_ int,int,int) PURE;
/*** IterNext - Continues a container iteration.
 *	= Bool - True if data was written to the iteration structure.
 *	: sContainIter* - Pointer to the iteration data, as returned from IterStart.
 */
	STDMETHOD_(Bool,IterNext)(THIS_ sContainIter*) PURE;
/*** IterEnd - Releases the resources used during an iteration.
 *	: sContainIter* - Pointer to the iteration data, as returned from IterStart.
 */
	STDMETHOD_(void,IterEnd)(THIS_ sContainIter*) PURE;
	STDMETHOD(DatabaseMessage)(THIS_ ulong,IUnknown*) PURE;
};
DEFINE_IIDSTRUCT(IContainSys,IID_IContainSys);
#undef INTERFACE

enum eWhichInvObj
{
	kInvWeapon,
	kInvItem
};
enum eCycleDirection
{
	kForward = 1,
	kBackward = -1
};

#define INTERFACE IInventory
DECLARE_GUID(IInventory);
DECLARE_INTERFACE_(IInventory,IUnknown)
{
	STDMETHOD_(eInventoryType,GetType)(THIS_ int) PURE;
	STDMETHOD(Add)(THIS_ int) PURE;
	STDMETHOD(Remove)(THIS_ int) PURE;
	STDMETHOD(Select)(THIS_ int) PURE;
	STDMETHOD_(int,Selection)(THIS_ eWhichInvObj) PURE;
	STDMETHOD(ClearSelection)(THIS_ eWhichInvObj) PURE;
	STDMETHOD_(int,CycleSelection)(THIS_ eWhichInvObj,eCycleDirection) PURE;
	STDMETHOD(Wield)(THIS_ eWhichInvObj) PURE;
	STDMETHOD_(int,WieldedObj)(THIS) PURE;
	STDMETHOD_(Bool,WieldingJunk)(THIS) PURE;
	STDMETHOD(DatabaseNotify)(THIS_ ulong,ITagFile*) PURE;
};
DEFINE_IIDSTRUCT(IInventory,IID_IInventory);
#undef INTERFACE

#define INTERFACE IKeySys
DECLARE_GUID(IKeySys);
DECLARE_INTERFACE_(IKeySys,IUnknown)
{
	STDMETHOD_(Bool,TryToUseKey)(THIS_ int,int,eKeyUse);
};
DEFINE_IIDSTRUCT(IKeySys,IID_IKeySys);
#undef INTERFACE

#endif // _LG_OBJECTS_H

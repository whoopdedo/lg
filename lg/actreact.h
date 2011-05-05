/**********************
 * LGS Act/React
 */

#ifndef _LG_ACTREACT_H
#define _LG_ACTREACT_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/objstd.h>
#include <lg/iiddef.h>
#include <lg/types.h>
#include <lg/defs.h>

interface IObjectQuery;

interface IPropagator;

union sStimShape
{
	char pad[32];
};

union sStimLifecycle
{
	char pad[32];
};

enum eStimSourceValidFields
{
	kStimSourceShapeValid = 1,
	kStimSourceLifecycleValid = 2
};

struct sStimSourceDesc
{
	int Propagator;
	float Intensity;
	ulong ValidFields;
	sStimShape Shape;
	sStimLifecycle Lifecycle;
};

struct sStimSensitivity
{
};

struct sStimEvent
{
};

struct sStimSensorEvent
{
};

struct sStimSourceEvent
{
};

struct sReactionEvent
{
};

struct sAmplifyParam
{
	float Multiply;
	float Add;
};
struct sWeakPointParam
{
	float Multiply;
	float Add;
	mxs_vector Offset;
	float Radius;
};
struct sStimulateParam
{
	char Stimulus[16];
	float Add;
	float Multiply;
};
struct sStimMsgParam
{
	int RefCount;
	unsigned int Flags;
	char unk1[24];
};
struct sTweqControl
{
	eTweqType Type;
	eTweqAction Action;
	eTweqFlag XtraBits;
	unsigned int unk1;
};
struct sQVarParam
{
	char QuestVariable[28];
	unsigned short Operation;
	short Operand;
};
struct sCollParam
{
	unsigned int Result;
};
struct sPermeate
{
	float Coefficient;
	float MinMagnitude;
};
struct sPropAddParam
{
	char Name[16];
	char unk1[16];
};
struct sPropRemParam
{
	char Name[16];
	char unk1[16];
};
struct sObjCreateParam
{
	mxs_vector Position;
	float Heading;
	float Pitch;
	float Bank;
};
struct sObjMoveParam
{
	mxs_vector Position;
	float Heading;
	float Pitch;
	float Bank;
};
struct sDamageParam
{
	int Add;
	int DamageType;
	float Multiply;
	int UseStimulusAsType;
};
struct sSpoofDamageParam
{
	int Add;
	int DamageType;
	float Multiply;
};
struct sSetModelParam
{
	char Name[16];
	char unk1[16];
};
struct sAware
{
	unsigned int AbortUnless;
	char unk1[28];
};
struct sRadParam
{
	float Increm;
};
struct sStunReactionParam
{
	int DurationMultiplier;
	char Tags[100];
};
struct sFreezeReactionParam
{
	int DurationMultiplier;
};
struct sEnvSoundReactionParam
{
	char Tags[64];
};
union sReactionParam
{
	sAmplifyParam Amplify;
	sWeakPointParam WeakPoint;
	sStimulateParam stimulate;
	sStimMsgParam stim_script_msg;
	sTweqControl tweq_control;
	sQVarParam SetQvar;
	sCollParam impact_result;
	sPermeate permeate;
	sPropAddParam add_prop;
	sPropRemParam rem_prop;
	sObjCreateParam create_obj;
	sObjMoveParam move_obj;
	sDamageParam damage;
	sSpoofDamageParam spoofdamage;
	sSetModelParam set_model;
	sAware AwareFilter;
	sRadParam radiate;
	sStunReactionParam Stun;
	sFreezeReactionParam Freeze;
	sEnvSoundReactionParam EnvSound;
};

struct sReceptron
{
	uint Order;
	float TriggerMin;
	float TriggerMax;
	ulong TriggerFlags;
	int Reaction;
	int DirectObject;
	int IndirectObject;
	char ReactionParam[32];
};

struct sObjStimPair
{
	int objid;
	int stimulus;
};

#define INTERFACE IPropagatorQuery
DECLARE_GUID(IPropagatorQuery);
DECLARE_INTERFACE_(IPropagatorQuery,IUnknown)
{
	STDMETHOD_(long,Start)(THIS) PURE;
	STDMETHOD_(int,Done)(THIS) PURE;
	STDMETHOD_(long,Next)(THIS) PURE;
	STDMETHOD_(unsigned long,ID)(THIS) PURE;
	STDMETHOD_(IPropagator*,Propagator)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IPropagatorQuery,IID_IPropagatorQuery);
#undef INTERFACE

#define INTERFACE IReactionQuery
DECLARE_GUID(IReactionQuery);
DECLARE_INTERFACE_(IReactionQuery,IUnknown)
{
	STDMETHOD_(long,Start)(void) PURE;
	STDMETHOD_(int,Done)(void) PURE;
	STDMETHOD_(long,Next)(void) PURE;
	STDMETHOD_(unsigned long,ID)(void) PURE;
};
DEFINE_IIDSTRUCT(IReactionQuery,IID_IReactionQuery);
#undef INTERFACE

#define INTERFACE IReceptronQuery
DECLARE_GUID(IReceptronQuery);
DECLARE_INTERFACE_(IReceptronQuery,IUnknown)
{
	STDMETHOD_(long,Start)(void) PURE;
	STDMETHOD_(int,Done)(void) PURE;
	STDMETHOD_(long,Next)(void) PURE;
	STDMETHOD_(sObjStimPair*,Elems)(sObjStimPair&) PURE;
	STDMETHOD_(unsigned long,ID)(void) PURE;
	STDMETHOD_(void*,Data)(void) PURE;
};
DEFINE_IIDSTRUCT(IReceptronQuery,IID_IReceptronQuery);
#undef INTERFACE

#define INTERFACE IStimSensorQuery
DECLARE_GUID(IStimSensorQuery);
DECLARE_INTERFACE_(IStimSensorQuery,IUnknown)
{
	STDMETHOD_(long,Start)(void) PURE;
	STDMETHOD_(int,Done)(void) PURE;
	STDMETHOD_(long,Next)(void) PURE;
	STDMETHOD_(sObjStimPair*,Elems)(sObjStimPair&) PURE;
	STDMETHOD_(unsigned long,ID)(void) PURE;
};
DEFINE_IIDSTRUCT(IStimSensorQuery,IID_IStimSensorQuery);
#undef INTERFACE

#define INTERFACE IStimSourceQuery
DECLARE_GUID(IStimSourceQuery);
DECLARE_INTERFACE_(IStimSourceQuery,IUnknown)
{
	STDMETHOD_(long,Start)(void) PURE;
	STDMETHOD_(int,Done)(void) PURE;
	STDMETHOD_(long,Next)(void) PURE;
	STDMETHOD_(unsigned long,ID)(void) PURE;
	STDMETHOD_(sObjStimPair*,Elems)(sObjStimPair&) PURE;
	STDMETHOD_(const sStimSourceDesc*,Source)(void) PURE;
};
DEFINE_IIDSTRUCT(IStimSourceQuery,IID_IStimSourceQuery);
#undef INTERFACE

struct sReactionDesc
{
	char	szName[32];
	char	szLongName[64];
	char	szParamType[32];
	int		unknown;
};

#define INTERFACE IReactions
DECLARE_GUID(IReactions);
DECLARE_INTERFACE_(IReactions,IUnknown)
{
	STDMETHOD_(unsigned long,Add)(sReactionDesc*,unsigned long (__stdcall *)(sReactionEvent*,const sReactionParam*,void*),void*) PURE;
	STDMETHOD_(unsigned long,GetReactionNamed)(const char*) PURE;
	STDMETHOD_(const sReactionDesc*,DescribeReaction)(unsigned long) PURE;
	STDMETHOD_(IReactionQuery*,QueryAll)(void) PURE;
	STDMETHOD_(unsigned long,React)(unsigned long,sReactionEvent*,const sReactionParam) PURE;
};
DEFINE_IIDSTRUCT(IReactions,IID_IReactions);
#undef INTERFACE

#define INTERFACE IStimSensors
DECLARE_GUID(IStimSensors);
DECLARE_INTERFACE_(IStimSensors,IUnknown)
{
	STDMETHOD_(unsigned long,AddReceptron)(int,int,const sReceptron*) PURE;
	STDMETHOD_(long,RemoveReceptron)(unsigned long) PURE;
	STDMETHOD_(sObjStimPair*,GetReceptronElems)(sObjStimPair&,unsigned long) PURE;
	STDMETHOD_(long,GetReceptron)(unsigned long,sReceptron*) PURE;
	STDMETHOD_(long,SetReceptron)(unsigned long,const sReceptron*) PURE;
	STDMETHOD_(IReceptronQuery*,QueryReceptrons)(int,int) PURE;
	STDMETHOD_(IReceptronQuery*,QueryInheritedReceptrons)(int,int) PURE;
	STDMETHOD_(int,ObjParam)(unsigned long) PURE;
	STDMETHOD_(IStimSensorQuery*,QuerySensors)(int,int) PURE;
	STDMETHOD_(unsigned long,LookupSensor)(int,int) PURE;
	STDMETHOD_(sObjStimPair*,GetSensorElems)(sObjStimPair&,unsigned long) PURE;
	STDMETHOD_(long,DatabaseNotify)(unsigned long,IUnknown*) PURE;
	STDMETHOD_(int,Get)(long,void *) PURE;
};
DEFINE_IIDSTRUCT(IStimSensors,IID_IStimSensors);
#undef INTERFACE

#define INTERFACE IStimSources
DECLARE_GUID(IStimSources);
DECLARE_INTERFACE_(IStimSources,IUnknown)
{
	STDMETHOD_(unsigned long,AddSource)(int,int,const sStimSourceDesc*) PURE;
	STDMETHOD_(long,RemoveSource)(unsigned long) PURE;
	STDMETHOD_(sObjStimPair*,GetSourceElems)(sObjStimPair&,unsigned long) PURE;
	STDMETHOD_(unsigned long,GetSourceBirthDate)(unsigned long) PURE;
	STDMETHOD_(long,DescribeSource)(unsigned long,sStimSourceDesc*) PURE;
	STDMETHOD_(IStimSourceQuery*,QuerySources)(int,int) PURE;
	STDMETHOD_(long,DatabaseNotify)(unsigned long,IUnknown*) PURE;
	STDMETHOD_(int,Get)(long,void *) PURE;
};
DEFINE_IIDSTRUCT(IStimSources,IID_IStimSources);
#undef INTERFACE

struct sStimDesc
{
	char name[32];
};

#define INTERFACE IStimuli
DECLARE_GUID(IStimuli);
DECLARE_INTERFACE_(IStimuli,IUnknown)
{
	STDMETHOD_(int,GetRootStimulus)(void) PURE;
	STDMETHOD_(int,CreateStimulus)(const sStimDesc*,int) PURE;
	STDMETHOD_(const char*,GetStimulusName)(int) PURE;
	STDMETHOD_(int,GetStimulusNamed)(const char*) PURE;
	STDMETHOD_(int,IsStimulus)(int) PURE;
	STDMETHOD_(IObjectQuery*,QueryDonors)(int) PURE;
	STDMETHOD_(IObjectQuery*,QueryHeirs)(int) PURE;
	STDMETHOD_(int,InheritsFrom)(int,int) PURE;
	STDMETHOD_(long,DatabaseNotify)(unsigned long,IUnknown*) PURE;
	STDMETHOD_(int,AddStimulus)(int) PURE;
};
DEFINE_IIDSTRUCT(IStimuli,IID_IStimuli);
#undef INTERFACE

#define INTERFACE IStimulator
DECLARE_GUID(IStimulator);
typedef unsigned long (__cdecl *StimEventFilter)(sStimEvent*,void*);
DECLARE_INTERFACE_(IStimulator,IUnknown)
{
	STDMETHOD_(long,StimulateSensor)(unsigned long,const sStimEvent*) PURE;
	STDMETHOD_(long,GetSensitivity)(unsigned long,sStimSensitivity*) PURE;
	STDMETHOD_(const Position*,GetSensorPosition)(unsigned long) PURE;
	STDMETHOD_(long,UpdateFrame)(unsigned long,unsigned long) PURE;
	STDMETHOD_(unsigned long,AddFilter)(StimEventFilter,void*) PURE;
	STDMETHOD_(long,RemoveFilter)(unsigned long) PURE;
};
DEFINE_IIDSTRUCT(IStimulator,IID_IStimulator);
#undef INTERFACE

DECLARE_GUID(IPeriodicPropagator);

#define INTERFACE IPropagation
DECLARE_GUID(IPropagation);
DECLARE_INTERFACE_(IPropagation,IUnknown)
{
	STDMETHOD_(unsigned long,AddPropagator)(IPropagator*) PURE;
	STDMETHOD_(long,AddPropagatorStimulus)(unsigned long,int) PURE;
	STDMETHOD_(long,RemovePropagatorStimulus)(unsigned long,int) PURE;
	STDMETHOD_(int,SupportsStimulus)(unsigned long,int) PURE;
	STDMETHOD_(IPropagator*,GetPropagator)(unsigned long) PURE;
	STDMETHOD_(IPropagator*,GetPropagatorNamed)(const char*) PURE;
	STDMETHOD_(IPropagatorQuery*,GetPropagators)(int) PURE;
	STDMETHOD_(long,SensorEvent)(sStimSensorEvent*) PURE;
	STDMETHOD_(long,SimpleSensorEvent)(unsigned long,unsigned long) PURE;
	STDMETHOD_(long,SourceEvent)(sStimSourceEvent*) PURE;
	STDMETHOD_(long,SimpleSourceEvent)(unsigned long,unsigned long) PURE;
	STDMETHOD_(long,Propagate)(unsigned long,unsigned long) PURE;
	STDMETHOD_(long,Reset)(void) PURE;
	STDMETHOD_(long,AddStimulus)(int) PURE;
};
DEFINE_IIDSTRUCT(IPropagation,IID_IPropagation);
#undef INTERFACE

struct sPropagatorDesc
{
};

#define INTERFACE IPropagator
DECLARE_GUID(IPropagator);
DECLARE_INTERFACE_(IPropagator,IUnknown)
{
	STDMETHOD_(const sPropagatorDesc *,Describe)(void) const PURE;
	STDMETHOD_(unsigned long,GetID)(void) PURE;
	STDMETHOD_(long,AddStimulus)(int) PURE;
	STDMETHOD_(long,RemoveStimulus)(int) PURE;
	STDMETHOD_(int,SupportsStimulus)(int) PURE;
	STDMETHOD_(long,InitSource)(sStimSourceDesc*) PURE;
	STDMETHOD_(const sStructDesc *,DescribeShapes)(void) PURE;
	STDMETHOD_(const sStructDesc *,DescribeLifeCycles)(void) PURE;
	STDMETHOD_(long,SourceEvent)(sStimSourceEvent *) PURE;
	STDMETHOD_(float,GetSourceLevel)(unsigned long) PURE;
	STDMETHOD_(long,DescribeSource)(unsigned long,sStimSourceDesc *) PURE;
	STDMETHOD_(int,f11)(void) PURE;
	STDMETHOD_(long,Connect)(IUnknown *) PURE;
	STDMETHOD_(long,Propagate)(unsigned long,unsigned long) PURE;
	STDMETHOD_(long,Reset)(void) PURE;
	STDMETHOD_(long,Start)(void) PURE;
	STDMETHOD_(long,Stop)(void) PURE;
};
DEFINE_IIDSTRUCT(IPropagator,IID_IPropagator);
#undef INTERFACE

#endif // _LG_ACTREACT_H

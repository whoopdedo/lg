/***************************
 * LGS Property Definitions
 */

#ifndef _LG_PROPDEFS_H
#define _LG_PROPDEFS_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/types.h>
#include <lg/defs.h>
#include <lg/properties.h>

#pragma pack(push,1)
struct Label
{
	uint uiLength;
	char szName[1];
};
#pragma pack(pop)
DECLARE_GUID(ILabelProperty);
DEFINE_PROPERTY_INTERFACE(ILabelProperty,Label*);

enum eEAXType
{
};

struct sAcoustics
{
	eEAXType Eax;
	int Dampening;
	int Height;
};
DECLARE_GUID(IAcousticsProperty);
DEFINE_PROPERTY_INTERFACE(IAcousticsProperty,sAcoustics*);

struct sAdvPickSoundCfg
{
	struct
	{
		char pick1[24];
		char pick2[24];
		char pick3[24];
	} stage[9];
};
DECLARE_GUID(IAdvPickSoundCfgProperty);
DEFINE_PROPERTY_INTERFACE(IAdvPickSoundCfgProperty,sAdvPickSoundCfg*);

struct sAdvPickStateCfg
{
	Bool enable;
	int source1;
	int source2;
	int source3;
	int time[9];
};
DECLARE_GUID(IAdvPickStateCfgProperty);
DEFINE_PROPERTY_INTERFACE(IAdvPickStateCfgProperty,sAdvPickStateCfg*);

struct sAdvPickTransCfg
{
	struct
	{
		int	pick1;
		int	pick2;
		int	pick3;
	} stage[9];
};
DECLARE_GUID(IAdvPickTransCfgProperty);
DEFINE_PROPERTY_INTERFACE(IAdvPickTransCfgProperty,sAdvPickTransCfg*);

struct  sAIAlertCap {
	int  iMax, iMin, iMinRelaxAfterPeak;
};
DECLARE_GUID(IAIAlertCapProperty);
DEFINE_PROPERTY_INTERFACE(IAIAlertCapProperty,sAIAlertCap*);

#define AITEAM_GOOD		0
#define AITEAM_NEUTRAL	1
#define AITEAM_BAD  	2

enum eAIAwarenessType
{
	kAIAware_Seen		= 0x00000001,
	kAIAware_Heard		= 0x00000002,
	kAIAware_CanRaycast	= 0x00000004,
	kAIAware_HaveLOS		= 0x00000008,
	kAIAware_Blind		= 0x00000010,
	kAIAware_Deaf		= 0x00000020,
	kAIAware_Highest		= 0x00000040,
	kAIAware_FirstHand	= 0x00000080,
};

// This should really be in linkdefs.h
struct sAIAwareness {
	int  iObject;
	uint  uFlags;
	eAIAwareLevel  Level;
	eAIAwareLevel  PeakLevel;
	int  LevelEnterTime;
	int  TimeLastContact;
	mxs_vector PosLastContact;
	int  i2;
	int  VisCone;
	int  TimeLastUpdate;
	int  TimeLastUpdateLOS;
	int  i3;
	int  TimeLastFirstHand;
	int  Freshness;
#if (_DARKGAME == 2)
	int  i4;
#endif
};

enum eAIPsdScrAct
{
	kPS_Nothing,
	kPS_ScrMsg,
	kPS_Alert,
	kPS_GoHostile,
	kPS_Investigate,
	kPS_GotoObject,
	kPS_FrobObject,
	kPS_Wait,
	kPS_MPrint,
	kPS_AddRemMetaProp,
	kPS_AddLink,
	kPS_RemLink,
	kPS_Face,
	kPS_DestScrMsg
};

struct sAIPsdScr
{
	eAIPsdScrAct	action;
	char	argument1[64];
	char	argument2[64];
	char	argument3[64];
	char	pad[64];
};

enum eAIWatchKind
{
	kAIWatchPlayerIntrustion,
	kAIWatchSelfEntry
};

enum eAIVisibility
{
	kNoVisibility,
	kLineOfSight,
	kRaycast
};

enum eAIWatchLinkKill
{
};

struct sAIWatchPoint
{
	char 	pad1[60];
	eAIWatchKind	WatchKind;
	eAIAwareLevel	ReqAwareness;
	eAIVisibility	ReqVisibility;
	int 	pad2;
	eAIWatchLinkKill	LinkKill;
	Bool	KillLikeLinks;
	Bool	NoTestOnceTriggered;
	int		ReuseTime;
	int		ResetTime;
	eAIScriptAlertLevel	MinAlertness;
	eAIScriptAlertLevel	MaxAlertness;
	eAIResponsePriority	Priority;
	int		TriggerRadius;
	int		TriggerHeight;
	sAIPsdScr	Response[8];
#if (_DARKGAME == 2)
	sAIPsdScr	Response2[8];
#endif
};
DECLARE_GUID(IAIWatchPointProperty);
DEFINE_PROPERTY_INTERFACE(IAIWatchPointProperty,sAIWatchPoint*);

#if 0
DECLARE_GUID(IAIAlertResponseProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIAlertResponseProperty);
DECLARE_GUID(IAIAlertSenseMultsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIAlertSenseMultsProperty);
DECLARE_GUID(IAIAlertnessProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIAlertnessProperty);
DECLARE_GUID(IAIAwareCapProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIAwareCapProperty);
DECLARE_GUID(IAIAwareDelayProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIAwareDelayProperty);
DECLARE_GUID(IAIBodyResponseProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIBodyResponseProperty);
DECLARE_GUID(IAIBroadcastProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIBroadcastProperty);
DECLARE_GUID(IAICameraProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAICameraProperty);
DECLARE_GUID(IAICombatTimingProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAICombatTimingProperty);
DECLARE_GUID(IAIConversationProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIConversationProperty);
DECLARE_GUID(IAIDeviceProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIDeviceProperty);
DECLARE_GUID(IAIEfficiencyProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIEfficiencyProperty);
DECLARE_GUID(IAIFleeConditionsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIFleeConditionsProperty);
DECLARE_GUID(IAIFrozenProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIFrozenProperty);
DECLARE_GUID(IAIFrustratedProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIFrustratedProperty);
DECLARE_GUID(IAIGrubCombatProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIGrubCombatProperty);
DECLARE_GUID(IAIGunDescProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIGunDescProperty);
DECLARE_GUID(IAIIdleDirsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIIdleDirsProperty);
DECLARE_GUID(IAIIdleOriginProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIIdleOriginProperty);
DECLARE_GUID(IAIInformResponseProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIInformResponseProperty);
DECLARE_GUID(IAIInvestKindProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIInvestKindProperty);
DECLARE_GUID(IAIModeProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIModeProperty);
DECLARE_GUID(IAINonCombatDmgRespProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAINonCombatDmgRespProperty);
DECLARE_GUID(IAINonHostilityProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAINonHostilityProperty);
DECLARE_GUID(IAIObjectAvoidProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIObjectAvoidProperty);
DECLARE_GUID(IAIProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIProperty);
DECLARE_GUID(IAIRangedApplicabilitiesProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIRangedApplicabilitiesProperty);
DECLARE_GUID(IAIRangedFleeProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIRangedFleeProperty);
DECLARE_GUID(IAIRangedRangesProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIRangedRangesProperty);
DECLARE_GUID(IAIRangedShootProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIRangedShootProperty);
DECLARE_GUID(IAIRangedWoundProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIRangedWoundProperty);
DECLARE_GUID(IAIRangedWoundSoundProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIRangedWoundSoundProperty);
DECLARE_GUID(IAIRatingProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIRatingProperty);
DECLARE_GUID(IAIReservedProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIReservedProperty);
DECLARE_GUID(IAISenseCombatResponseProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAISenseCombatResponseProperty);
DECLARE_GUID(IAISignalResponseProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAISignalResponseProperty);
DECLARE_GUID(IAISoundTypeProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAISoundTypeProperty);
DECLARE_GUID(IAISuspiciousResponseProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAISuspiciousResponseProperty);
DECLARE_GUID(IAISwarmProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAISwarmProperty);
DECLARE_GUID(IAIThreatResponseProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIThreatResponseProperty);
DECLARE_GUID(IAITurretProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAITurretProperty);
DECLARE_GUID(IAIVisCtrlProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIVisCtrlProperty);
DECLARE_GUID(IAIVisibilityModProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIVisibilityModProperty);
DECLARE_GUID(IAIVisibilityProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIVisibilityProperty);
DECLARE_GUID(IAIVisionDescProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIVisionDescProperty);
DECLARE_GUID(IAIWanderProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAIWanderProperty);
#endif

enum eAnimLightMode
{
	kAnimLight_FlipMinMax,
	kAnimLight_SlideSmoothly,
	kAnimLight_Random,
	kAnimLight_MinBrightness,
	kAnimLight_MaxBrightness,
	kAnimLight_ZeroBrightness,
	kAnimLight_SmoothlyBrighten,
	kAnimLight_SmoothlyDim,
	kAnimLight_RandomCoherent,
	kAnimLight_FlickerMinMax
};

struct sAnimLight
{
	float Brightness;
	mxs_vector Offset;
	Bool Updated;
	short CellIndex;
	short CellCount;
	short LightID;
	short Mode;
	long TimeToBrighten;
	long TimeToDim;
	float MinBrightness;
	float MaxBrightness;
	float CurrentBrightness;
	Bool IsRising;
	long Countdown;
	Bool IsDisabled;
	float Radius;
	int NotifyObj;
	Bool QuadLit;
	float InnerRadius;
};

struct sFlinders
{
	int	Count;
	float	Impulse;
	Bool	Scatter;
	mxs_vector	Offset;
};

enum eInvRendType
{
	kInvRendDefault,
	kInvRendAltModel,
	kInvRendAltBitmap
};

struct sInvRendType
{
	eInvRendType Type;
	char Resource[16];
};
DECLARE_GUID(IInvRenderProperty);
DEFINE_PROPERTY_INTERFACE(IInvRenderProperty,sInvRendType*);

#pragma pack(push,1)
struct sKeyProp
{
	unsigned char bMasterBit;
#if (_DARKGAME == 2)
	unsigned long iRegionMask;
#else
	unsigned short iRegionMask;
#endif
	unsigned char iLockID;
};
#pragma pack(pop)

struct sLoot {
	int  iGold;
	int  iGems;
	int  iArt;
	int  iSpecial;
};

struct sMovingTerrain
{
	unsigned long	unknown;
	Bool	active;
};
DECLARE_GUID(IMovingTerrainProperty);
DEFINE_PROPERTY_INTERFACE(IMovingTerrainProperty,sMovingTerrain*);

#pragma pack(push,2)
struct sPosition
{
	mxs_vector Location;
	short Cell;
	short unused;
	unsigned short Bank;
	unsigned short Pitch;
	unsigned short Heading;
};
#pragma pack(pop)
DECLARE_GUID(IPositionProperty);
DEFINE_PROPERTY_INTERFACE(IPositionProperty,sPosition*);

struct sScriptProp
{
	char script[4][32];
	Bool noinherit;
};
DECLARE_GUID(IScriptProperty);
DEFINE_PROPERTY_INTERFACE(IScriptProperty,sScriptProp*);

#define PHYS_CONTROL_AXISVELS	1
#define PHYS_CONTROL_VELS		2
#define PHYS_CONTROL_ROTVELS	4
#define PHYS_CONTROL_LOCATION	8
#define PHYS_CONTROL_ROTATION	16

struct sPhysControl {
	int uiActive;
	mxs_vector axis_vels;
	mxs_vector vels;
	mxs_vector rot_vels;
};

struct sPhysState {
	mxs_vector loc;
	mxs_vector facing;
	mxs_vector vels;
	mxs_vector rot_vels;
};

#pragma pack(push,1)
struct sRenderFlash
{
	uchar	red;
	uchar	green;
	uchar	blue;
	uchar	active;
	int	worldduration;
	int	screenduration;
	int	effectduration;
	float	time;
	float	range;
	ulong	starttime;
};
#pragma pack(pop)
DECLARE_GUID(IRendFlashProperty);
DEFINE_PROPERTY_INTERFACE(IRendFlashProperty,sRenderFlash*);

enum eStats
{
	kStatStrength,
	kStatEndurance,
	kStatPsi,
	kStatAgility,
	kStatCyber
};

struct sStatsDesc
{
	int Strength;
	int Endurance;
	int Psi;
	int Agility;
	int Cyber;
};

enum eTechSkills
{
	kHRMHack,
	kHRMRepair,
	kHRMModify,
	kHRMMaintain,
	kHRMResearch,
};

enum eWeaponSkills
{
	kWeaponConventional,
	kWeaponEnergy,
	kWeaponHeavy,
	kWeaponAnnelid
};

struct sWeaponSkills
{
	int Conventional;
	int Energy;
	int Heavy;
	int Annelid;
};

enum ePlayerEquip
{
	kPlayerEquipWeapon = 1000,
	kPlayerEquipArmor = 1002,
	kPlayerEquipImplant1 = 1003,
	kPlayerEquipImplant2 = 1004,
	kPlayerEquipHacksoft = 1006,
	kPlayerEquipRepairsoft = 1007,
	kPlayerEquipModifysoft = 1008,
	kPlayerEquipResearchsoft = 1009,
	kPlayerEquipNanites = 1010,
	kPlayerEquipCookie = 1011,
	kPlayerEquipPDA = 1012,
	kPlayerEquipKeycards = 1013,
	kPlayerEquipCompass = 1014
};

enum ePsiPowers
{
	kPsiPowerLevel1,
	kPsiPowerFeatherFall,
	kPsiPowerStillHand,
	kPsiPowerPull,
	kPsiPowerQuickness,
	kPsiPowerCyber,
	kPsiPowerCryokinesis,
	kPsiPowerCodebreaker,
	kPsiPowerLevel2,
	kPsiPowerStability,
	kPsiPowerBerserk,
	kPsiPowerRadShield,
	kPsiPowerHealing,
	kPsiPowerMight,
	kPsiPowerPsi,
	kPsiPowerImmolate,
	kPsiPowerLevel3,
	kPsiPowerFabricate,
	kPsiPowerElectro,
	kPsiPowerAntiPsi,
	kPsiPowerToxinShield,
	kPsiPowerRadar,
	kPsiPowerPyrokinesis,
	kPsiPowerTerror,
	kPsiPowerLevel4,
	kPsiPowerInvisibility,
	kPsiPowerSeeker,
	kPsiPowerDampen,
	kPsiPowerVitality,
	kPsiPowerAlchemy,
	kPsiPowerCyberHack,
	kPsiPowerPsiSword,
	kPsiPowerLevel5,
	kPsiPowerMajorHeal,
	kPsiPowerSomaDrain,
	kPsiPowerTeleport,
	kPsiPowerEnrage,
	kPsiPowerForceWall,
	kPsiPowerPsiMines,
	kPsiPowerPsiShield,
	kPsiPowerNone,
	kPsiPower42,
	kPsiPower43,
	kPsiPower44,
	kPsiPower45,
	kPsiPower46,
	kPsiPower47,
	kPsiPower48,
	kPsiPower49,
	kPsiPower50,
	kPsiPower51,
	kPsiPower52,
	kPsiPower53,
	kPsiPower54,
	kPsiPower55,
	kPsiPower56,
	kPsiPower57,
	kPsiPower58,
	kPsiPower59,
	kPsiPower60,
	kPsiPower61,
	kPsiPower62,
	kPsiPower63,
	kPsiPower64
};

typedef int eTrait;
#define kTraitRadresistance	1
#define kTraitPatchboost	2
#define kTraitInventory		3
#define kTraitSpeedboost	4
#define kTraitRangedaccuracy	5
#define kTraitCookieboost	6
#define kTraitCyberboost	7
#define kTraitHitpointboost	8
#define kTraitDamageboost	9
#define kTraitAlarmtimeout	10
#define kTraitOverhandmelee	11
#define kTraitDroidpatch	12
#define kTraitReplicatorboost	13
#define kTraitNooverload	14
#define kTraitModifyboost	15
#define kTraitAutomap		16

typedef int eImplant;

#if 0
DECLARE_GUID(IAltLinkProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAltLinkProperty);
DECLARE_GUID(IAmbientProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAmbientProperty);
DECLARE_GUID(IAmbientSoundProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAmbientSoundProperty);
DECLARE_GUID(IAngleLimitProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAngleLimitProperty);
DECLARE_GUID(IAnimLightProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAnimLightProperty);
DECLARE_GUID(IAnimTexProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAnimTexProperty);
DECLARE_GUID(IArmorProperty);
DEFINE_PROPERTY_IIDSTRUCT(IArmorProperty);
DECLARE_GUID(IAutomapProperty);
DEFINE_PROPERTY_IIDSTRUCT(IAutomapProperty);
DECLARE_GUID(IBaseGunDescProperty);
DEFINE_PROPERTY_IIDSTRUCT(IBaseGunDescProperty);
DECLARE_GUID(IBashParamsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IBashParamsProperty);
DECLARE_GUID(IBeltLinkProperty);
DEFINE_PROPERTY_IIDSTRUCT(IBeltLinkProperty);
DECLARE_GUID(IBipedLengthsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IBipedLengthsProperty);
DECLARE_GUID(IBipedModelProperty);
DEFINE_PROPERTY_IIDSTRUCT(IBipedModelProperty);
DECLARE_GUID(IBipedProperty);
DEFINE_PROPERTY_IIDSTRUCT(IBipedProperty);
DECLARE_GUID(IBitmapWorldspaceProperty);
DEFINE_PROPERTY_IIDSTRUCT(IBitmapWorldspaceProperty);
DECLARE_GUID(IBreathProperty);
DEFINE_PROPERTY_IIDSTRUCT(IBreathProperty);
DECLARE_GUID(IBrushProperty);
DEFINE_PROPERTY_IIDSTRUCT(IBrushProperty);
DECLARE_GUID(ICameraObjProperty);
DEFINE_PROPERTY_IIDSTRUCT(ICameraObjProperty);
DECLARE_GUID(ICannisterProperty);
DEFINE_PROPERTY_IIDSTRUCT(ICannisterProperty);
DECLARE_GUID(IChemInfoProperty);
DEFINE_PROPERTY_IIDSTRUCT(IChemInfoProperty);
DECLARE_GUID(IColorProperty);
DEFINE_PROPERTY_IIDSTRUCT(IColorProperty);
DECLARE_GUID(IContainDimsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IContainDimsProperty);
DECLARE_GUID(ICoronaProperty);
DEFINE_PROPERTY_IIDSTRUCT(ICoronaProperty);
DECLARE_GUID(ICoverPtProperty);
DEFINE_PROPERTY_IIDSTRUCT(ICoverPtProperty);
DECLARE_GUID(ICreaturePoseProperty);
DEFINE_PROPERTY_IIDSTRUCT(ICreaturePoseProperty);
DECLARE_GUID(ICreatureProperty);
DEFINE_PROPERTY_IIDSTRUCT(ICreatureProperty);
DECLARE_GUID(IESndTagProperty);
DEFINE_PROPERTY_IIDSTRUCT(IESndTagProperty);
DECLARE_GUID(IEcologyInfoProperty);
DEFINE_PROPERTY_IIDSTRUCT(IEcologyInfoProperty);
DECLARE_GUID(IExpProperty);
DEFINE_PROPERTY_IIDSTRUCT(IExpProperty);
DECLARE_GUID(IExtraLightProperty);
DEFINE_PROPERTY_IIDSTRUCT(IExtraLightProperty);
DECLARE_GUID(IFaceProperty);
DEFINE_PROPERTY_IIDSTRUCT(IFaceProperty);
DECLARE_GUID(IFaceStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(IFaceStateProperty);
DECLARE_GUID(IFlowGroupProperty);
DEFINE_PROPERTY_IIDSTRUCT(IFlowGroupProperty);
DECLARE_GUID(IFrameAnimationConfigProperty);
DEFINE_PROPERTY_IIDSTRUCT(IFrameAnimationConfigProperty);
DECLARE_GUID(IFrameAnimationStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(IFrameAnimationStateProperty);
DECLARE_GUID(IFrobInfoProperty);
DEFINE_PROPERTY_IIDSTRUCT(IFrobInfoProperty);
DECLARE_GUID(IFrobOldProperty);
DEFINE_PROPERTY_IIDSTRUCT(IFrobOldProperty);
DECLARE_GUID(IGlobalIDProperty);
DEFINE_PROPERTY_IIDSTRUCT(IGlobalIDProperty);
DECLARE_GUID(IGunAnimProperty);
DEFINE_PROPERTY_IIDSTRUCT(IGunAnimProperty);
DECLARE_GUID(IGunKickProperty);
DEFINE_PROPERTY_IIDSTRUCT(IGunKickProperty);
DECLARE_GUID(IGunReliabilityProperty);
DEFINE_PROPERTY_IIDSTRUCT(IGunReliabilityProperty);
DECLARE_GUID(IGunStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(IGunStateProperty);
DECLARE_GUID(IHeartbeatListProperty);
DEFINE_PROPERTY_IIDSTRUCT(IHeartbeatListProperty);
DECLARE_GUID(IHeatDiskProperty);
DEFINE_PROPERTY_IIDSTRUCT(IHeatDiskProperty);
DECLARE_GUID(IHomingProperty);
DEFINE_PROPERTY_IIDSTRUCT(IHomingProperty);
DECLARE_GUID(IHostObjIDProperty);
DEFINE_PROPERTY_IIDSTRUCT(IHostObjIDProperty);
DECLARE_GUID(IInvDimsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IInvDimsProperty);
DECLARE_GUID(IInvStringProperty);
DEFINE_PROPERTY_IIDSTRUCT(IInvStringProperty);
DECLARE_GUID(IJointPosProperty);
DEFINE_PROPERTY_IIDSTRUCT(IJointPosProperty);
DECLARE_GUID(IKeyInfoProperty);
DEFINE_PROPERTY_IIDSTRUCT(IKeyInfoProperty);
DECLARE_GUID(ILightProperty);
DEFINE_PROPERTY_IIDSTRUCT(ILightProperty);
DECLARE_GUID(ILogDataProperty);
DEFINE_PROPERTY_IIDSTRUCT(ILogDataProperty);
DECLARE_GUID(ILootInfoProperty);
DEFINE_PROPERTY_IIDSTRUCT(ILootInfoProperty);
DECLARE_GUID(ILootProperty);
DEFINE_PROPERTY_IIDSTRUCT(ILootProperty);
DECLARE_GUID(IMapRefProperty);
DEFINE_PROPERTY_IIDSTRUCT(IMapRefProperty);
DECLARE_GUID(IMeshAttachProperty);
DEFINE_PROPERTY_IIDSTRUCT(IMeshAttachProperty);
DECLARE_GUID(IMeshTexProperty);
DEFINE_PROPERTY_IIDSTRUCT(IMeshTexProperty);
DECLARE_GUID(IMotActorTagListProperty);
DEFINE_PROPERTY_IIDSTRUCT(IMotActorTagListProperty);
DECLARE_GUID(IMotGaitDescProperty);
DEFINE_PROPERTY_IIDSTRUCT(IMotGaitDescProperty);
DECLARE_GUID(IMotPhysLimitsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IMotPhysLimitsProperty);
DECLARE_GUID(IMotPlayerLimbOffsetsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IMotPlayerLimbOffsetsProperty);
DECLARE_GUID(INetPlayerProperty);
DEFINE_PROPERTY_IIDSTRUCT(INetPlayerProperty);
DECLARE_GUID(IObjIconProperty);
DEFINE_PROPERTY_IIDSTRUCT(IObjIconProperty);
DECLARE_GUID(IObjNameProperty);
DEFINE_PROPERTY_IIDSTRUCT(IObjNameProperty);
DECLARE_GUID(IObjSoundNameProperty);
DEFINE_PROPERTY_IIDSTRUCT(IObjSoundNameProperty);
DECLARE_GUID(IPGroupLaunchInfoProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPGroupLaunchInfoProperty);
DECLARE_GUID(IParticleGroupProperty);
DEFINE_PROPERTY_IIDSTRUCT(IParticleGroupProperty);
DECLARE_GUID(IPhysAttrProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPhysAttrProperty);
DECLARE_GUID(IPhysControlProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPhysControlProperty);
DECLARE_GUID(IPhysDimsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPhysDimsProperty);
DECLARE_GUID(IPhysExplodeProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPhysExplodeProperty);
DECLARE_GUID(IPhysPPlateProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPhysPPlateProperty);
DECLARE_GUID(IPhysRopeProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPhysRopeProperty);
DECLARE_GUID(IPhysStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPhysStateProperty);
DECLARE_GUID(IPhysTypeProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPhysTypeProperty);
DECLARE_GUID(IPickCfgProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPickCfgProperty);
DECLARE_GUID(IPickStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPickStateProperty);
DECLARE_GUID(IPlayerGunDescProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPlayerGunDescProperty);
DECLARE_GUID(IProjectileProperty);
DEFINE_PROPERTY_IIDSTRUCT(IProjectileProperty);
DECLARE_GUID(IPsiPowerProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPsiPowerProperty);
DECLARE_GUID(IPsiShieldProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPsiShieldProperty);
DECLARE_GUID(IPsiStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPsiStateProperty);
DECLARE_GUID(IPuppetProperty);
DEFINE_PROPERTY_IIDSTRUCT(IPuppetProperty);
DECLARE_GUID(IQuestVarProperty);
DEFINE_PROPERTY_IIDSTRUCT(IQuestVarProperty);
DECLARE_GUID(IRangedCombatProperty);
DEFINE_PROPERTY_IIDSTRUCT(IRangedCombatProperty);
DECLARE_GUID(IRendFlashProperty);
DEFINE_PROPERTY_IIDSTRUCT(IRendFlashProperty);
DECLARE_GUID(IRepContentsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IRepContentsProperty);
DECLARE_GUID(IRoomGravityProperty);
DEFINE_PROPERTY_IIDSTRUCT(IRoomGravityProperty);
DECLARE_GUID(IRoomScriptProperty);
DEFINE_PROPERTY_IIDSTRUCT(IRoomScriptProperty);
DECLARE_GUID(IRotDoorProperty);
DEFINE_PROPERTY_IIDSTRUCT(IRotDoorProperty);
DECLARE_GUID(IScaleProperty);
DEFINE_PROPERTY_IIDSTRUCT(IScaleProperty);
DECLARE_GUID(ISchemaLoopParamsProperty);
DEFINE_PROPERTY_IIDSTRUCT(ISchemaLoopParamsProperty);
DECLARE_GUID(ISchemaPlayParamsProperty);
DEFINE_PROPERTY_IIDSTRUCT(ISchemaPlayParamsProperty);
DECLARE_GUID(ISchemaTagConstraintProperty);
DEFINE_PROPERTY_IIDSTRUCT(ISchemaTagConstraintProperty);
DECLARE_GUID(IShockRangedProperty);
DEFINE_PROPERTY_IIDSTRUCT(IShockRangedProperty);
DECLARE_GUID(ISparkProperty);
DEFINE_PROPERTY_IIDSTRUCT(ISparkProperty);
DECLARE_GUID(ISpawnInfoProperty);
DEFINE_PROPERTY_IIDSTRUCT(ISpawnInfoProperty);
DECLARE_GUID(ISpeechProperty);
DEFINE_PROPERTY_IIDSTRUCT(ISpeechProperty);
DECLARE_GUID(IStatsDescProperty);
DEFINE_PROPERTY_IIDSTRUCT(IStatsDescProperty);
DECLARE_GUID(ISuspiciousProperty);
DEFINE_PROPERTY_IIDSTRUCT(ISuspiciousProperty);
DECLARE_GUID(ITechInfoProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITechInfoProperty);
DECLARE_GUID(ITechSkillsProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITechSkillsProperty);
DECLARE_GUID(ITraitsDescProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITraitsDescProperty);
DECLARE_GUID(ITransDoorProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITransDoorProperty);
DECLARE_GUID(ITweqEmitterProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqEmitterProperty);
DECLARE_GUID(ITweqJointsProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqJointsProperty);
DECLARE_GUID(ITweqJointsStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqJointsStateProperty);
DECLARE_GUID(ITweqLockProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqLockProperty);
DECLARE_GUID(ITweqLockStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqLockStateProperty);
DECLARE_GUID(ITweqModelsProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqModelsProperty);
DECLARE_GUID(ITweqSimpleProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqSimpleProperty);
DECLARE_GUID(ITweqSimpleStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqSimpleStateProperty);
DECLARE_GUID(ITweqVectorProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqVectorProperty);
DECLARE_GUID(ITweqVectorStateProperty);
DEFINE_PROPERTY_IIDSTRUCT(ITweqVectorStateProperty);
DECLARE_GUID(IVantagePtProperty);
DEFINE_PROPERTY_IIDSTRUCT(IVantagePtProperty);
DECLARE_GUID(IWaterColorProperty);
DEFINE_PROPERTY_IIDSTRUCT(IWaterColorProperty);
DECLARE_GUID(IWeaponOffsetProperty);
DEFINE_PROPERTY_IIDSTRUCT(IWeaponOffsetProperty);
DECLARE_GUID(IWeaponSkillsProperty);
DEFINE_PROPERTY_IIDSTRUCT(IWeaponSkillsProperty);
DECLARE_GUID(IWeatherProperty);
DEFINE_PROPERTY_IIDSTRUCT(IWeatherProperty);
#endif

#endif // _LG_PROPS_H

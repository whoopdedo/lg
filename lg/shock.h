/**********************
 * LGS System Shock 2
 */

#ifndef _LG_SHOCK_H
#define _LG_SHOCK_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#include <lg/types.h>
#include <lg/defs.h>
#include <lg/propdefs.h>

enum eShockCameraMode
{
	kCameraNormal,
	kCameraPlayback,
	kCameraRecord,
	kCameraEdit
};

#define INTERFACE IShockCamera
DECLARE_GUID(IShockCamera);
DECLARE_INTERFACE_(IShockCamera,IUnknown)
{
	STDMETHOD(SetLocation)(THIS_ const mxs_vector*,const mxs_angvec*) PURE;
	STDMETHOD_(Bool,AttachName)(THIS_ const char*) PURE;
	STDMETHOD_(Bool,AttachSymName)(THIS_ const Label*) PURE;
	STDMETHOD_(Bool,AttachID)(THIS_ int) PURE;
	STDMETHOD(Detach)(THIS) PURE;
	STDMETHOD_(int,GetAttachObject)(THIS) PURE;
	STDMETHOD(SetEditState)(THIS_ eShockCameraMode) PURE;
	STDMETHOD(SetScene)(THIS_ const char*) PURE;
	STDMETHOD(SetEditMode)(THIS_ eShockCameraMode) PURE;
	STDMETHOD_(eShockCameraMode,GetEditState)(THIS) PURE;
	STDMETHOD_(eShockCameraMode,GetEditMode)(THIS) PURE;
	STDMETHOD(SwitchCamera)(THIS_ int) PURE;
	STDMETHOD_(int,GetNumCameras)(THIS) PURE;
	STDMETHOD(SetCameraSpeed)(THIS_ float) PURE;
	STDMETHOD_(float,GetCameraSpeed)(THIS) PURE;
	STDMETHOD(SaveScene)(THIS) PURE;
	STDMETHOD(MakeScenes)(THIS) PURE;
	STDMETHOD(Frame)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IShockCamera,IID_IShockCamera);
#undef INTERFACE

#define INTERFACE ICameraObjects
DECLARE_GUID(ICameraObjects);
DECLARE_INTERFACE_(ICameraObjects,IUnknown)
{
	STDMETHOD(Frame)(THIS_ uint) PURE;
};
DEFINE_IIDSTRUCT(ICameraObjects,IID_ICameraObjects);
#undef INTERFACE

#define INTERFACE IShockPlayer
DECLARE_GUID(IShockPlayer);
DECLARE_INTERFACE_(IShockPlayer,IUnknown)
{
	STDMETHOD_(int,StatCost)(THIS_ int) PURE;
	STDMETHOD_(int,WeaponSkillCost)(THIS_ int) PURE;
	STDMETHOD_(int,TechSkillCost)(THIS_ int) PURE;
	STDMETHOD_(int,PsiPowerCost)(THIS_ int) PURE;
	STDMETHOD_(Bool,PsiLevel)(THIS_ int,int) PURE;
	STDMETHOD_(Bool,PsiPower)(THIS_ int,ePsiPowers) PURE;
	STDMETHOD_(int,FindPsiLevel)(THIS_ ePsiPowers) PURE;
	STDMETHOD(AddPsiPower)(THIS_ int,ePsiPowers) PURE;
	STDMETHOD_(Bool,IsPsiTier)(THIS_ ePsiPowers) PURE;
	STDMETHOD_(Bool,CheckStats)(THIS_ sStatsDesc*,sStatsDesc*,Bool) PURE;
	STDMETHOD_(Bool,CheckWeaponSkills)(THIS_ sWeaponSkills*,sWeaponSkills*,Bool) PURE;
	STDMETHOD_(Bool,Equip)(THIS_ int,ePlayerEquip,int,Bool) PURE;
	STDMETHOD(SetEquip)(THIS_ int,ePlayerEquip,int) PURE;
	STDMETHOD_(int,GetEquip)(THIS_ int,ePlayerEquip) PURE;
	STDMETHOD(ClearEquip)(THIS) PURE;
	STDMETHOD(AlternateWeapons)(THIS_ int) PURE;
	STDMETHOD_(void,SetWeaponModel)(THIS_ int,Bool) PURE;
	STDMETHOD_(Bool,CheckRequirements)(THIS_ int,Bool) PURE;
	STDMETHOD_(int,GetCurrentGun)(THIS) PURE;
	STDMETHOD(UseInternalModel)(THIS) PURE;
	STDMETHOD(UseExternalModel)(THIS) PURE;
	STDMETHOD_(char*,GetExternalModel)(THIS) PURE;
	STDMETHOD(RecalcData)(THIS_ int) PURE;
	STDMETHOD_(int,GetStat)(THIS_ eStats) PURE;
	STDMETHOD_(int,GetTechSkill)(THIS_ eTechSkills) PURE;
	STDMETHOD_(int,GetWeaponSkill)(THIS_ eWeaponSkills) PURE;
	STDMETHOD_(Bool,GetWeaponSkills)(THIS_ int,sWeaponSkills*) PURE;
	STDMETHOD_(int,GetPsiSkill)(THIS_ ePsiPowers) PURE;
	STDMETHOD_(Bool,HasTrait)(THIS_ int,eTrait) PURE;
	STDMETHOD_(Bool,HasTraitMulti)(THIS_ eTrait) PURE;
	STDMETHOD_(Bool,HasImplant)(THIS_ int,eImplant) PURE;
	STDMETHOD(AddStats)(THIS_ sStatsDesc*,sStatsDesc*) PURE;
	STDMETHOD_(Bool,GetStats)(THIS_ int,sStatsDesc*) PURE;
	STDMETHOD_(int,GetPool)(THIS_ int) PURE;
	STDMETHOD(AddPool)(THIS_ int,int) PURE;
	STDMETHOD(SetPool)(THIS_ int,int) PURE;
	STDMETHOD_(float,GetStimMultiplier)(THIS_ int) PURE;
};
DEFINE_IIDSTRUCT(IShockPlayer,IID_IShockPlayer);
#undef INTERFACE

#define INTERFACE IPlayerGun
DECLARE_GUID(IPlayerGun);
DECLARE_INTERFACE_(IPlayerGun,IUnknown)
{
	STDMETHOD(Init)(THIS) PURE;
	STDMETHOD(GameInit)(THIS) PURE;
	STDMETHOD(GameTerm)(THIS) PURE;
	STDMETHOD(Set)(THIS_ int) PURE;
	STDMETHOD(SetRaised)(THIS_ int) PURE;
	STDMETHOD_(int,Get)(THIS) PURE;
	STDMETHOD_(int,GetHand)(THIS) PURE;
	STDMETHOD(Frame)(THIS_ uint) PURE;
	STDMETHOD(PullTrigger)(THIS) PURE;
	STDMETHOD(ReleaseTrigger)(THIS) PURE;
	STDMETHOD(Raise)(THIS) PURE;
	STDMETHOD(Lower)(THIS) PURE;
	STDMETHOD(Off)(THIS) PURE;
	STDMETHOD(Load)(THIS) PURE;
	STDMETHOD_(Bool,IsReloading)(THIS) const PURE;
	STDMETHOD_(Bool,IsTriggerPulled)(THIS) const PURE;
	STDMETHOD_(Bool,MatchesCurrentAmmo)(THIS_ int) PURE;
};
DEFINE_IIDSTRUCT(IPlayerGun,IID_IPlayerGun);
#undef INTERFACE

#define INTERFACE IPsiActiveIter
DECLARE_GUID(IPsiActiveIter);
DECLARE_INTERFACE_(IPsiActiveIter,IUnknown)
{
	STDMETHOD_(Bool,Done)(THIS) PURE;
	STDMETHOD(Next)(THIS) PURE;
	STDMETHOD_(const char*,GetName)(THIS) PURE;
	STDMETHOD_(ePsiPowers,GetPower)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IPsiActiveIter,IID_IPsiActiveIter);
#undef INTERFACE

enum ePsiActivateStatus
{
	kPsiOK,
	kPsiInvalidPower,
	kPsiInsufficientPoints
};

#define INTERFACE IPlayerPsi
DECLARE_GUID(IPlayerPsi);
DECLARE_INTERFACE_(IPlayerPsi,IUnknown)
{
	STDMETHOD(Frame)(THIS_ uint) PURE;
	STDMETHOD(Select)(THIS_ ePsiPowers) PURE;
	STDMETHOD_(ePsiPowers,GetSelectedPower)(THIS) PURE;
	STDMETHOD_(ePsiActivateStatus,CanActivate)(THIS) PURE;
	STDMETHOD(Activate)(THIS) PURE;
	STDMETHOD(Deactivate)(THIS_ ePsiPowers) PURE;
	STDMETHOD(OnDeactivate)(THIS_ ePsiPowers) PURE;
	STDMETHOD_(Bool,IsActive)(THIS_ ePsiPowers) PURE;
	STDMETHOD_(int,GetPoints)(THIS) PURE;
	STDMETHOD_(int,GetMaxPoints)(THIS) PURE;
	STDMETHOD(SetMaxPoints)(THIS_ int) PURE;
	STDMETHOD(SetPoints)(THIS_ int) PURE;
	STDMETHOD_(ePsiPowers,GetSustainedPower)(THIS) PURE;
	STDMETHOD_(void,OnSchemaEnd)(THIS_ int) PURE;
	STDMETHOD_(IPsiActiveIter*,Iter)(THIS) PURE;
	STDMETHOD(BeginOverload)(THIS) PURE;
	STDMETHOD_(Bool,EndOverload)(THIS) PURE;
	STDMETHOD(PsiTarget)(THIS_ int) PURE;
};
DEFINE_IIDSTRUCT(IPlayerPsi,IID_IPlayerPsi);
#undef INTERFACE

#endif // _LG_SHOCK_H

/**********************
 * LGS Script Services
 */

#ifndef _LG_SCRSERVICES_H
#define _LG_SCRSERVICES_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/objstd.h>
#include <lg/iiddef.h>

#include <lg/types.h>
#include <lg/defs.h>
#if (_DARKGAME == 3) || (_SHOCKINTERFACES == 1)
#include <lg/propdefs.h>
#endif

interface IScriptServiceBase : IUnknown
{
	STDMETHOD_(void,Init)(void) PURE;
	STDMETHOD_(void,End)(void) PURE;
};

DECLARE_GUID(IActReactScriptService);
interface IActReactSrv : IScriptServiceBase
{
/*** React - Execute a reaction response.
 *  	= long - Returns 0 on success.
 *  	: reaction_kind - ID of the reaction to execute.
 *  	: float - Intensity of the reaction.
 *  	: object - The source object.
 *  	: object - The destination object.
 *  	: cMultiParm & - Argument for the reaction.
 *  	: ...
 */
	STDMETHOD(React)(reaction_kind,float,object,object,const cMultiParm &,const cMultiParm &,const cMultiParm &,const cMultiParm &,const cMultiParm &,const cMultiParm &,const cMultiParm &,const cMultiParm &) PURE;
#if (_DARKGAME == 1)
/*** Stimulate - Stimulate an object.
 *  	= long - Returns 0 on success.
 *  	: object - The object to be stimulated.
 *  	: object - The stimulus object.
 *  	: float - The intensity of the stimulus.
 */
	STDMETHOD(Stimulate)(object,object,float) PURE;
#else
/*** Stimulate - Stimulate an object.
 *  	= long - Returns 0 on success.
 *  	: object - The object to be stimulated.
 *  	: object - The stimulus object.
 *  	: float - The intensity of the stimulus.
 *  	: object - The source of the stimulus.
 */
	STDMETHOD(Stimulate)(object,object,float,object) PURE;
#endif
/*** GetReactionNamed - Return the reaction ID given its name.
 *  	= long - ID of the reaction.
 *  	: const char * - The reaction name.
 *  	@ IReactions::GetReactionNamed(name)
 */
	STDMETHOD_(long,GetReactionNamed)(const char *) PURE;
/*** GetReactionName - Return the name of a reaction given its ID.
 *  	= cScrStr - Name of the reaction.
 *  	: long - The reaction ID.
 *  	@ IReactions::DescribeReaction(id)
 */
	STDMETHOD_(cScrStr*,GetReactionName)(cScrStr &,long) PURE;
/*** SubscribeToStimulus - Register an object to receive stimulus messages of a particular type.
 *  	= long - Returns 0 on success.
 *  	: object - The object that will receive the messages.
 *  	: object - The type of stimulus.
 */
	STDMETHOD(SubscribeToStimulus)(object,object) PURE;
/*** UnsubscribeToStimulus - Stop listening for stimulus messages.
 *  	= long - Returns 0 on success.
 *  	: object - The object that was previously registered.
 *  	: object - The type of stimulus.
 */
	STDMETHOD(UnsubscribeToStimulus)(object,object) PURE;
/*** BeginContact - Initiate a stimulus contact on an object.
 *  	= long - Returns 0 on success.
 *  	: object - The stimulus object.
 *  	: object - The destination object.
 */
	STDMETHOD(BeginContact)(object,object) PURE;
/*** EndContact - Terminate stimulus contact on an object.
 *  	= long - Returns 0 on success.
 *  	: object - The stimulus object.
 *  	: object - The destination object.
 */
	STDMETHOD(EndContact)(object,object) PURE;
/*** SetSingleSensorContact - Briefly touch an object.
 *  	= long - Returns 0 on success.
 *  	: object - The stimulus object.
 *  	: object - The destination object.
 */
	STDMETHOD(SetSingleSensorContact)(object,object) PURE;
};
DEFINE_IIDSTRUCT(IActReactSrv,IID_IActReactScriptService);

DECLARE_GUID(IAIScriptService);
interface IAIScrSrv : IScriptServiceBase
{
/*** MakeGotoObjLoc - Instruct an AI to go to the current location of an object.
 *  	= true_bool - Success.
 *  	: int - Object ID of the AI.
 *  	: const object & - The target object.
 *  	: eAIScriptSpeed - How quickly the AI will move.
 *  	: eAIActionPriority - Priority level the action will be evaluated at.
 *  	: const cMultiParm & - Arbitrary data that will be passed with the ObjActResult message.
 */
	STDMETHOD_(true_bool*,MakeGotoObjLoc)(true_bool &,int,const object &,eAIScriptSpeed,eAIActionPriority,const cMultiParm &) PURE;
/*** MakeFrobObjWith - Instruct an AI to frob an object with another object.
 *  	= true_bool - Success.
 *  	: int - Object ID of the AI.
 *  	: const object & - The target object.
 *  	: const object & - Object that the target will be frobbed with.
 *  	: eAIActionPriority - Priority level the action will be evaluated at.
 *  	: const cMultiParm & - Arbitrary data that will be passed with the ObjActResult message.
 */
	STDMETHOD_(true_bool*,MakeFrobObjWith)(true_bool &,int,const object &,const object &,eAIActionPriority,const cMultiParm &) PURE;
/*** MakeFrobObj - Instruct an AI to frob an object.
 *  	= true_bool - Success.
 *  	: int - Object ID of the AI.
 *  	: const object & - The target object.
 *  	: eAIActionPriority - Priority level the action will be evaluated at.
 *  	: const cMultiParm & - Arbitrary data that will be passed with the ObjActResult message.
 */
	STDMETHOD_(true_bool*,MakeFrobObj)(true_bool &,int,const object &,eAIActionPriority,const cMultiParm &) PURE;
/*** GetAlertLevel - Return the current alert level of the AI.
 *  	= eAIScriptAlertLevel - The current level.
 *  	: int - Object ID of the AI.
 */
	STDMETHOD_(eAIScriptAlertLevel,GetAlertLevel)(int) PURE;
/*** SetMinimumAlert - Set the minimum alertness cap of the AI.
 *  	: int - Object ID of the AI.
 *  	: eAIScriptAlertLevel - The lowest alert level allowable for the AI.
 */
	STDMETHOD_(void,SetMinimumAlert)(int,eAIScriptAlertLevel) PURE;
/*** ClearGoals - Make the AI forget what it's doing. Obsolete, does nothing.
 *  	: int - Object ID of the AI.
 */
	STDMETHOD_(void,ClearGoals)(int) PURE;
/*** SetScriptFlags - Disable AI broadcasts.
 *  	: int - Object ID of the AI.
 *  	: int - Halt speech if 1. Clear flags if 0.
 */
	STDMETHOD_(void,SetScriptFlags)(int,int) PURE;
/*** ClearAlertness - Remove AIAwareness links and set the alert level to it's lowest allowable value.
 *  	: int - Object ID of the AI.
 */
	STDMETHOD_(void,ClearAlertness)(int) PURE;
/*** Signal - Send a SignalAI message with a given string to the AI.
 *  	: int - Object ID of the AI.
 *  	: const cScrStr & - A string that will be sent with the signal.
 */
	STDMETHOD_(void,Signal)(int,const cScrStr  &) PURE;
/*** StartConversation - Run a conversation pseudo-script.
 *  	= true_bool - Success.
 *  	: int - The object with the conversation script.
 *  	@ IAIManager::StartConversation(obj)
 */
	STDMETHOD_(true_bool*,StartConversation)(true_bool &,int) PURE;
};
DEFINE_IIDSTRUCT(IAIScrSrv,IID_IAIScriptService);

DECLARE_GUID(IAnimTextureScriptService);
interface IAnimTextureSrv : IScriptServiceBase
{
/*** ChangeTexture - Swap one texture on nearby polygons.
 *  	= long - Returns 0 on success.
 *  	: object - The host object.
 *  	: const char * - The path to the texture family of the old texture. May be NULL.
 *  	: const char * - The name of the old texture. If the path is NULL, this must be a full path.
 *  	: const char * - The path to the texture family of the new texture. May be NULL.
 *  	: const char * - The name of the new texture. If the path is NULL, this must be a full path.
 */
	STDMETHOD(ChangeTexture)(object,const char *,const char *,const char *,const char *) PURE;
};
DEFINE_IIDSTRUCT(IAnimTextureSrv,IID_IAnimTextureScriptService);

DECLARE_GUID(IBowScriptService);
interface IBowSrv : IScriptServiceBase
{
/*** Equip - Set the bow as the current weapon.
 *  	= Bool - Returns true on success.
 */
	STDMETHOD_(Bool,Equip)(void) PURE;
/*** UnEquip - Clear the current weapon if it was the bow.
 *  	= Bool - Returns true on success.
 */
	STDMETHOD_(Bool,UnEquip)(void) PURE;
/*** IsEquipped - Check if the bow is the current weapon.
 *  	= Bool - True if the bow is the current weapon.
 */
	STDMETHOD_(Bool,IsEquipped)(void) PURE;
/*** StartAttack - Begin drawing the bow.
 *  	= Bool - Returns true.
 */
	STDMETHOD_(Bool,StartAttack)(void) PURE;
/*** FinishAttack - Release the bow.
 *  	= Bool - Returns true on success.
 */
	STDMETHOD_(Bool,FinishAttack)(void) PURE;
/*** AbortAttack - Relax the bow without firing an arrow.
 *  	= Bool - Returns true on success.
 */
	STDMETHOD_(Bool,AbortAttack)(void) PURE;
/*** SetArrow - Make an object the current projectile for the bow.
 *  	= Bool - Returns true on success.
 *  	: object - The object that will be fired from the bow.
 */
	STDMETHOD_(Bool,SetArrow)(object) PURE;
};
DEFINE_IIDSTRUCT(IBowSrv,IID_IBowScriptService);

DECLARE_GUID(ICameraScriptService);
interface ICameraSrv : IScriptServiceBase
{
#if (_DARKGAME == 2) || ((_DARKGAME == 1) && defined(_NEWDARK))
/*** StaticAttach - Attach camera to object. Do not allow freelook.
 *  	= long - Returns 0.
 *  	: object - Object to attach to.
 */
	STDMETHOD(StaticAttach)(object) PURE;
/*** DynamicAttach - Attach camera to object. Allow freelook.
 *  	= long - Returns 0.
 *  	: object - Object to attach to.
 */
	STDMETHOD(DynamicAttach)(object) PURE;
/*** CameraReturn - Return the camera to Player if it's still attached to the object.
 *  	= long - Returns 0 if the camera was returned.
 *  	: object - Object to detach from. Does nothing if camera is attached to a different object.
 */
	STDMETHOD(CameraReturn)(object) PURE;
/*** ForceCameraReturn - Return the camera to Player unconditionally.
 *  	= long - Returns 0.
 */
	STDMETHOD(ForceCameraReturn)(void) PURE;
#ifdef _NEWDARK
/*** GetCameraParent - Return the object the camera is currently attached to.
 *  	! Implemented by NewDark version 1.22 or later only.
 *  	= object - The camera-attached object. Aggregate return.
 */
	STDMETHOD_(object*,GetCameraParent)(object&) PURE;
/*** IsRemote - Check if the camera is attached to another object than Player.
 *  	! Implemented by NewDark version 1.22 or later only.
 *  	= true_bool - True if GetCameraParent() != PlayerObject().
 */
	STDMETHOD_(true_bool*,IsRemote)(true_bool&) PURE;
/*** GetPosition - Get the location of the camera.
 *  	! Implemented by NewDark version 1.22 or later only.
 *  	= cScrVec - The camera-attached object's XYZ vector. Aggregate return.
 */
	STDMETHOD_(cScrVec*,GetPosition)(cScrVec&) PURE;
/*** GetFacing - Get the rotation of the camera.
 *  	! Implemented by NewDark version 1.22 or later only.
 *  	= cScrVec - The camera-attached object's HPB vector as degrees. Aggregate return.
 */
	STDMETHOD_(cScrVec*,GetFacing)(cScrVec&) PURE;
/*** CameraToWorld - Transform coordinates relative to the location and rotation of the camera.
 *  	! Implemented by NewDark version 1.23 or later only.
 *  	= cScrVec - World coordinates of the input vector. Aggregate return.
 *  	: const cScrVec & - Relative location. i.e. (1,0,0) is one unit in front of the camera.
 */
	STDMETHOD_(cScrVec*,CameraToWorld)(cScrVec&,const cScrVec &) PURE;
/*** WorldToCamera - Get the relative coordinates from the camera to a location.
 *  	! Implemented by NewDark version 1.23 or later only.
 *  	= cScrVec - Camera coordinates of the input vector. Aggregate return.
 *  	: const cScrVec & - Absolute location in the world.
 */
	STDMETHOD_(cScrVec*,WorldToCamera)(cScrVec&,const cScrVec &) PURE;
#endif
#endif
};
DEFINE_IIDSTRUCT(ICameraSrv,IID_ICameraScriptService);

DECLARE_GUID(IContainerScriptService);
interface IContainSrv : IScriptServiceBase
{
/*** Add - Move an object into a container.
 *  	= long - Returns 0 on success.
 *  	: object - The object to be contained.
 *  	: object - The container.
 *  	: int - The contain type.
 *  	: int - Combine the object if set to 1.
 *  	@ IContainSys::Add(container,obj,type,combine)
 */
	STDMETHOD(Add)(object,object,int,int) PURE;
/*** Remove - Take an object out of a container.
 *  	= long - Returns 0.
 *  	: object - The object that was contained.
 *  	: object - The container.
 *  	@ IContainSys::Remove(container,obj)
 */
	STDMETHOD(Remove)(object,object) PURE;
/*** MoveAllContents - Move all the objects in one container into another.
 *  	= long - Returns 0.
 *  	: object - The container to take the objects from.
 *  	: object - The container to place the objects in.
 *  	: int - Attempt to combine similar objects if set to 1.
 *  	@ IContainSys::MoveAllContents(to,from,combine)
 */
	STDMETHOD(MoveAllContents)(object,object,int) PURE;
#if (_DARKGAME != 1)
/*** StackAdd - Modify the stack count of an object.
 *  	= long - The actual amount added.
 *  	: object - The object to add to.
 *  	: int - Amount to add. May be negative.
 *  	@ IContainSys::StackAdd(obj,add,1)
 */
	STDMETHOD(StackAdd)(object,int) PURE;
/*** IsHeld - Check whether an object is contained by another.
 *  	= int - Returns the contain type or MAXLONG if the object is not contained.
 *  	: object - The container to check.
 *  	: object - The possibly contained object.
 *  	@ IContainSys::IsHeld(container,obj)
 */
	STDMETHOD_(int,IsHeld)(object,object) PURE;
#endif
};
DEFINE_IIDSTRUCT(IContainSrv,IID_IContainerScriptService);

DECLARE_GUID(IDamageScriptService);
interface IDamageSrv : IScriptServiceBase
{
/*** Damage - Cause damage to an object.
 *  	= long - Returns 0.
 *  	: object - Victim
 *  	: object - Culprit
 *  	: int - Intensity of damage
 *  	: int - Type of damage
 *  	@ IDamageModel::DamageObject(victim,culprit,damage,0,0)
 */
	STDMETHOD(Damage)(object,object,int,int) PURE;
/*** Slay - Slay an object.
 *  	= long - Returns 0.
 *  	: object - Victim
 *  	: object - Culprit
 *  	@ IDamageModel::SlayObject(victim,culprit,0)
 */
	STDMETHOD(Slay)(object,object) PURE;
/*** Resurrect - Reverse the effects of slaying an object.
 *  	= long - Returns 0.
 *  	: object - Un-Victim
 *  	: object - Culprit
 *  	@ IDamageModel::ResurrectObject(victim,culprit,0)
 */
	STDMETHOD(Resurrect)(object,object) PURE;
};
DEFINE_IIDSTRUCT(IDamageSrv,IID_IDamageScriptService);

DECLARE_GUID(IDarkGameScriptService);
interface IDarkGameSrv : IScriptServiceBase
{
/*** KillPlayer - Garrett dies. Ignored if no_endgame is set.
 *  	= long - Returns 0 on success.
 */
	STDMETHOD(KillPlayer)(void) PURE;
/*** EndMission - Immediately stop the current mission. Ignored if no_endgame is set.
 *  	= long - Returns 0 on success.
 */
	STDMETHOD(EndMission)(void) PURE;
/*** FadeToBlack - Gradually fade the screen. Ignored if no_endgame is set.
 *  	= long - Returns 0 on success.
 *  	: float - Speed of the fade, in seconds. If negative, the screen will immediately return to full visibility.
 */
	STDMETHOD(FadeToBlack)(float) PURE;
#if (_DARKGAME == 2)
/*** FoundObject - Rings the secret bell. Will only work once per object.
 *  	= long - Returns 0.
 *  	: int - object ID.
 */
	STDMETHOD(FoundObject)(int) PURE;
/*** ConfigIsDefined - Test if a config variable has been set.
 *  	= Bool - True if the variable has been set.
 *  	: const char * - The config variable to test for.
 */
	STDMETHOD_(Bool,ConfigIsDefined)(const char *) PURE;
/*** ConfigGetInt - Return the value of a config variable interpreted as an integer.
 *  	= Bool - Returns true on success.
 *  	: const char * - The config variable to retrieve.
 *  	: int & - Address of a variable that will recieve the value.
 */
	STDMETHOD_(Bool,ConfigGetInt)(const char *,int &) PURE;
/*** ConfigGetFloat - Return the value of a config variable interpreted as an floating-point number.
 *  	= Bool - Returns true on success.
 *  	: const char * - The config variable to retrieve.
 *  	: float & - Address of a variable that will recieve the value.
 */
	STDMETHOD_(Bool,ConfigGetFloat)(const char *,float &) PURE;
/*** BindingGetFloat - Return the floating-point value of a key-binding variable.
 *  	= float - The value of the variable.
 *  	: const char * - The name of the variable.
 */
	STDMETHOD_(float,BindingGetFloat)(const char *) PURE;
/*** GetAutomapLocationVisited - Return whether a region of the auto-map is marked as visited.
 *  	= Bool - True if the region was visited.
 *  	: int - The page number of the location.
 *  	: int - The room number of the location.
 */
	STDMETHOD_(Bool,GetAutomapLocationVisited)(int,int) PURE;
/*** SetAutomapLocationVisited - Mark a region of the auto-map as having been visited.
 *  	= long - Returns 0.
 *  	: int - The page number of the location.
 *  	: int - The room number of the location.
 */
	STDMETHOD(SetAutomapLocationVisited)(int,int) PURE;
#ifdef _NEWDARK
/*** SetNextMission - Change the number mission that will be loaded after this one ends.
 *  	: int - The number of the next mission to load.
 */
	STDMETHOD_(void,SetNextMission)(int) PURE;
/*** GetCurrentMission - Return the number of the current mission.
 *  	= int - The current mission number.
 */
	STDMETHOD_(int,GetCurrentMission)(void) PURE;
#endif
#endif
};
DEFINE_IIDSTRUCT(IDarkGameSrv,IID_IDarkGameScriptService);

DECLARE_GUID(IDarkUIScriptService);
interface IDarkUISrv : IScriptServiceBase
{
/*** TextMessage - Display a string on the screen.
 *  	= long - Returns 0.
 *  	: const char * - The message to display.
 *  	: ulong - The color of the text. Equivalent to Win32 COLORREF. If this is zero, uses the default color, which is white.
 *  	: int - The maximum time, in milliseconds, to display the message. Passing -1001 will use the default time of 5 secs. (Actual time may be shorter if another call to TextMessage is made.)
 */
	STDMETHOD(TextMessage)(const char *,ulong,int) PURE;
/*** ReadBook - Enter book mode.
 *  	= long - Returns 0.
 *  	: const char * - The resource name of the book.
 *  	: const char * - The background image that will be shown.
 */
	STDMETHOD(ReadBook)(const char *,const char *) PURE;
/*** InvItem - Get the currently selected inventory item.
 *  	= object - The inventory item.
 *  	@ IInventory::Selection(kInvItem)
 */
	STDMETHOD_(object*,InvItem)(object &) PURE;
/*** InvWeapon - Get the currently selected weapon.
 *  	= object - Object ID of the weapon.
 *  	@ IInventory::Selection(kInvWeapon)
 */
	STDMETHOD_(object*,InvWeapon)(object &) PURE;
/*** InvSelect - Set an object to be the active inventory selection.
 *  	= long - Returns 0 on success.
 *  	: object - Object ID of the item.
 *  	@ IInventory::Select(obj)
 */
	STDMETHOD(InvSelect)(object) PURE;
/*** IsCommandBound - Test if a command string is bound to a key sequence.
 *  	= true_bool - True if the command is bound. Aggregate return.
 *  	: const cScrStr & - The command string to check for.
 */
	STDMETHOD_(true_bool*,IsCommandBound)(true_bool &,const cScrStr &) PURE;
/*** DescribeKeyBinding - Return the key-binding for a particular command.
 *  	= cScrStr - The keys bound to this command. Aggregate return.
 *  	: const cScrStr & - The command string.
 */
	STDMETHOD_(cScrStr*,DescribeKeyBinding)(cScrStr &,const cScrStr &) PURE;
};
DEFINE_IIDSTRUCT(IDarkUISrv,IID_IDarkUIScriptService);

DECLARE_GUID(IDataScriptService);
interface IDataSrv : IScriptServiceBase
{
/*** GetString - Retrieve a string from a resource file.
 *  	= cScrStr - Aggregate return. Caller should free.
 *  	: const char * - The name of the resource file.
 *  	: const char * - The string name to get.
 *  	: const char * - Default value if the string can't be found.
 *  	: const char * - The resource directory to look in. ("Books" is not a normal resource, use "..\Books\file" for the filename and "strings" here.)
 *  	@ IGameStrings::FetchString(res,name,default,path)
 */
	STDMETHOD_(cScrStr*,GetString)(cScrStr &,const char *,const char *,const char *,const char *) PURE;
/*** GetObjString - Retrieve one of the standard object strings. Uses the GameName property.
 *  	= cScrStr - Aggregate return. Caller should free.
 *  	: int - The object ID to get the string of.
 *  	: const char * - The resource name to look in. "objnames" or "objdescs"
 *  	@ IGameStrings::FetchObjString(obj,res)
 */
	STDMETHOD_(cScrStr*,GetObjString)(cScrStr &,int,const char *) PURE;
/*** DirectRand - Return a (psuedo) random number in the range [0,32767]
 *  	= int - A randomly generated number.
 */
	STDMETHOD_(int,DirectRand)(void) PURE;
/*** RandInt - Return a (psuedo) random number in a given range. The range is inclusive on both ends.
 *  	= int - A randomly generated number.
 *  	: int - The low end of the range. The generated number will not be less than this.
 *  	: int - The high end of the range. The generated number will not be greater than this.
 */
	STDMETHOD_(int,RandInt)(int,int) PURE;
/*** RandFlt0to1 - Return a (psuedo) random floating-point number in the range [0,1].
 *  	= float - A randomly generated number.
 */
	STDMETHOD_(float,RandFlt0to1)(void) PURE;
/*** RandFltNeg1to1 - Return a (psuedo) random floating-point number in the range [-1,1).
 *  	= float - A randomly generated number.
 */
	STDMETHOD_(float,RandFltNeg1to1)(void) PURE;
};
DEFINE_IIDSTRUCT(IDataSrv,IID_IDataScriptService);

DECLARE_GUID(IDebugScriptService);
interface IDebugScrSrv : IScriptServiceBase
{
/*** MPrint - Send string(s) to the mono. DromEd only, but safe to use in game mode.
 *  	= long - Returns 0.
 *  	: cScrStr - A string to print.
 *  	: ...
 */
	STDMETHOD(MPrint)(const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &) PURE;
/*** Command - Execute commands.
 *  	= long - Returns 0.
 *  	: cScrStr - Command string. A space will be inserted between this and the rest of the arguments.
 *  	: cScrStr - Command argument.
 *  	: ...
 */
	STDMETHOD(Command)(const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &) PURE;
/*** Break - Raise a debugger interrupt.
 *  	= long - Returns 0.
 */
	STDMETHOD(Break)(void) PURE;
#ifdef _NEWDARK
/*** Log - Send string(s) to the log.
 *  	= long - Returns 0.
 *  	: cScrStr - A string to print.
 *  	: ...
 */
	STDMETHOD(Log)(const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &,const cScrStr &) PURE;
#endif
};
DEFINE_IIDSTRUCT(IDebugScrSrv,IID_IDebugScriptService);

DECLARE_GUID(IDoorScriptService);
interface IDoorSrv : IScriptServiceBase
{
/*** CloseDoor - Closes a door.
 *  	= Bool - True if the object is a door and is not already closed.
 *  	: object - The door to close.
 */
	STDMETHOD_(Bool,CloseDoor)(object) PURE;
/*** OpenDoor - Open a door.
 *  	= Bool - True if the object is a door and is not already open.
 *  	: object - The door to open.
 */
	STDMETHOD_(Bool,OpenDoor)(object) PURE;
/*** GetDoorState - Return whether a door is open or closed (or something else).
 *  	= int - The state of the door. See eDoorState in lg/defs.h. Returns 5 if the object is not a door.
 *  	: object - The door.
 */
	STDMETHOD_(int,GetDoorState)(object) PURE;
/*** ToggleDoor - Switch the state of a door.
 *  	= Bool - True on success.
 *  	: object - The door to open/close.
 */
	STDMETHOD_(Bool,ToggleDoor)(object) PURE;
#if (_DARKGAME == 2) || ((_DARKGAME == 1) && defined(_NEWDARK))
/*** SetBlocking - Set whether a door can block sound.
 *  	= Bool - True if the object is a door.
 *  	: object - The door to change.
 *  	: Bool - The blocking state.
 */
	STDMETHOD_(Bool,SetBlocking)(object,Bool) PURE;
/*** GetSoundBlocking - Return if a door blocks sound.
 *  	= Bool - True if the door blocks sound.
 *  	: object - The door to check..
 */
	STDMETHOD_(Bool,GetSoundBlocking)(object) PURE;
#endif
};
DEFINE_IIDSTRUCT(IDoorSrv,IID_IDoorScriptService);

DECLARE_GUID(IDrkInvScriptService);
enum eDrkInvCap
{
	kDrkInvCapCycle,
	kDrkInvCapWorldFrob,
	kDrkInvCapWorldFocus,
	kDrkInvCapInvFrob
};
enum eDrkInvControl
{
	kDrkInvControlOn,
	kDrkInvControlOff,
	kDrkInvControlToggle
};
interface IDarkInvSrv : IScriptServiceBase
{
/*** CapabilityControl - Set restrictions on the inventory UI.
 *  	: eDrkInvCap - Which capability to change.
 *  	: eDrkInvControl - Enable or disable the capability.
 */
	STDMETHOD_(void,CapabilityControl)(eDrkInvCap,eDrkInvControl) PURE;
/*** AddSpeedControl - Change the speed of Player.
 *  	: char * - ID of the control. Speed controls can be stacked and removed out-of-order.
 *  	: float - Amount to multiply the speed by.
 *  	: float - Multiplier for turning speed. Appears to be ineffective.
 */
	STDMETHOD_(void,AddSpeedControl)(const char *,float,float) PURE;
/*** RemoveSpeedControl - Remove a previously applied speed control.
 *  	: char * - ID of the control.
 */
	STDMETHOD_(void,RemoveSpeedControl)(const char *) PURE;
};
DEFINE_IIDSTRUCT(IDarkInvSrv,IID_IDrkInvScriptService);

DECLARE_GUID(IDrkPowerupsScriptService);
interface IDarkPowerupsSrv : IScriptServiceBase
{
/*** TriggerWorldFlash - Create a blinding flash.
 *  	: object - The flash will occur at the location of this object. Any AI with a line-of-sight to the object will be blinded. A RenderFlash link on the object's archetype determines how the flash will appear on screen.
 */
	STDMETHOD_(void,TriggerWorldFlash)(object) PURE;
/*** ObjTryDeploy - Create a new object at the location of another object.
 *  	= Bool - Returns true.
 *  	: object - Emitter object.
 *  	: object - Type of object to create.
 */
	STDMETHOD_(Bool,ObjTryDeploy)(object,object) PURE;
/*** CleanseBlood - Slay nearby objects with Prox\Blood
 *  	: object - Culprit object.
 *  	: float - The radius around the object that will be cleaned.
 */
	STDMETHOD_(void,CleanseBlood)(object,float) PURE;
};
DEFINE_IIDSTRUCT(IDarkPowerupsSrv,IID_IDrkPowerupsScriptService);

DECLARE_GUID(IKeyScriptService);
interface IKeySrv : IScriptServiceBase
{
/*** TryToUseKey - Use or test a key on an object.
 *  	= Bool - True if the operation was successful.
 *  	: const object & - The key object.
 *  	: const object & - The object to use the key on.
 *  	: eKeyUse - The operation to attempt.
 *  	@ IKeySys::TryToUseKey(key,obj,use)
 */
	STDMETHOD_(Bool,TryToUseKey)(const object &,const object &,eKeyUse) PURE;
};
DEFINE_IIDSTRUCT(IKeySrv,IID_IKeyScriptService);

DECLARE_GUID(ILightScriptService);
interface ILightScrSrv : IScriptServiceBase
{
/*** Set - Set the mode and min/max values of the light.
 *  	: const object & - The light object.
 *  	: int - The light mode.
 *  	: float - Minimum brightness of the light.
 *  	: float - Maximum brightness of the light.
 */
	STDMETHOD_(void,Set)(const object &,int,float,float) PURE;
/*** SetMode - Set the current mode of the light.
 *  	: const object & - The light object.
 *  	: int - The light mode.
 */
	STDMETHOD_(void,SetMode)(const object &,int) PURE;
/*** Activate - Clear the inactive flag on the light.
 *  	: const object & - The light object.
 */
	STDMETHOD_(void,Activate)(const object &) PURE;
/*** Deactivate - Set the inactive flag on the light.
 *  	: const object & - The light object.
 */
	STDMETHOD_(void,Deactivate)(const object &) PURE;
/*** Subscribe - Listen for LightChange messages.
 *  	: const object & - The light object.
 */
	STDMETHOD_(void,Subscribe)(const object &) PURE;
/*** Unsubscribe - Stop listening for LightChange messages.
 *  	: const object & - The light object.
 */
	STDMETHOD_(void,Unsubscribe)(const object &) PURE;
/*** GetMode - Return the current light mode.
 *  	= int - The current mode.
 *  	: const object & - The light object.
 */
	STDMETHOD_(int,GetMode)(const object &) PURE;
};
DEFINE_IIDSTRUCT(ILightScrSrv,IID_ILightScriptService);

DECLARE_GUID(ILinkScriptService);
interface ILinkSrv : IScriptServiceBase
{
/*** Create - Add a link between two objects.
 *  	= link - The created link. Aggregate return.
 *  	: linkkind - The flavor of the link to create.
 *  	: object - The source of the link.
 *  	: object - The destination of the link.
 *  	@ ILinkManager::Add(src,dst,flavor)
 */
	STDMETHOD_(link*,Create)(link &,linkkind,object,object) PURE;
/*** Destroy - Removes a link.
 *  	= long - Zero on success.
 *  	: link - The link to remove.
 *  	@ ILinkManager::Remove(link)
 */
	STDMETHOD(Destroy)(link) PURE;
/*** AnyExist - Check if there is a link of a certain flavor between two objects.
 *  	= true_bool - True if at least one link exists. Aggregate return.
 *  	: linkkind - The flavor of the link to look for.
 *  	: object - The source of the link.
 *  	: object - The destination of the link.
 *  	@ ILinkManager::Query(src,dst,flavor)
 */
	STDMETHOD_(true_bool*,AnyExist)(true_bool &,linkkind,object,object) PURE;
/*** GetAll - Get all the links of certain flavor between two objects.
 *  	= linkset - The query of the requested links. Aggregate return.
 *  	: linkkind - The link flavor requested.
 *  	: object - The source of the links.
 *  	: object - The destination of the links.
 *  	@ ILinkManager::Query(src,dst,flavor)
 */
	STDMETHOD_(linkset*,GetAll)(linkset &,linkkind,object,object) PURE;
/*** GetOne - Get just one link of certain flavor between two objects.
 *  	= link - The link. Aggregate return.
 *  	: linkkind - The flavor of the link requested.
 *  	: object - The source of the link.
 *  	: object - The destination of the link.
 *  	@ ILinkManager::Query(src,dst,flavor)
 */
	STDMETHOD_(link*,GetOne)(link &,linkkind,object,object) PURE;
/*** BroadcastOnAllLinks - Send a message to the destination of links from an object.
 *  	= long - Returns 0.
 *  	: const object & - The source of the link(s). Also the source of the message(s).
 *  	: const char * - The name of the message to send.
 *  	: linkkind - The flavor of the link(s) to send the message accross.
 *  	@ ILinkManager::Query(src,0,flavor)
 */
	STDMETHOD(BroadcastOnAllLinks)(const object &,const char *,linkkind) PURE;
/*** BroadcastOnAllLinksData - Send a message to the destination of links from an object, comparing data.
 *  	= long - Returns 0.
 *  	: const object & - The source of the link(s). Also the source of the message(s).
 *  	: const char * - The name of the message to send.
 *  	: linkkind - The flavor of the link(s) to send the message accross.
 *  	: const cMultiParm & - The message is sent if the link data matches this exactly. It is copied to the first data parameter of the message.
 *  	@ ILinkManager::Query(src,0,flavor)
 */
	STDMETHOD_(long,BroadcastOnAllLinksData)(const object &,const char *,linkkind,const cMultiParm &) PURE;
/*** CreateMany - Add links between many different objects.
 *  	= long - Returns 0 on success.
 *  	: linkkind - The flavor of the links to create.
 *  	: const cScrStr & - The sources of the links.
 *  	: const cScrStr & - The destinations of the links.
 */
	STDMETHOD(CreateMany)(linkkind,const cScrStr &,const cScrStr &) PURE;
/*** DestroyMany - Remove multiple links from objects.
 *  	= long - Returns 0 on success.
 *  	: linkkind - The flavor of the links to destroy.
 *  	: const cScrStr & - The sources of the links.
 *  	: const cScrStr & - The destinations of the links.
 */
	STDMETHOD(DestroyMany)(linkkind,const cScrStr &,const cScrStr &) PURE;
/*** GetAllInherited - Retrieve links between objects and both their archetypes.
 *  	= linkset - The links between the objects. Aggregate return.
 *  	: linkkind - The flavor of the links to retrieve.
 *  	: object - The starting object to look for the source of the links.
 *  	: object - The startint object to look for the destination of the links.
 */
	STDMETHOD_(linkset*,GetAllInherited)(linkset &,linkkind,object,object) PURE;
/*** GetAllInheritedSingle - Retrieve links from an object and its archetypes and a particular or unknown object.
 *  	= linkset - The links between the objects. Aggregate return.
 *  	: linkkind - The flavor of the links to retrieve.
 *  	: object - The starting object to look for the source of the links.
 *  	: object - The destination of the links.
 */
	STDMETHOD_(linkset*,GetAllInheritedSingle)(linkset &,linkkind,object,object) PURE;
};
DEFINE_IIDSTRUCT(ILinkSrv,IID_ILinkScriptService);

DECLARE_GUID(ILinkToolsScriptService);
interface ILinkToolsSrv : IScriptServiceBase
{
/*** LinkKindNamed - Get the ID of a link flavor
 *  	= long - The flavor ID.
 *  	: const char * - The name of the flavor.
 *  	@ ILinkManager::GetRelationNamed(name)
 */
	STDMETHOD_(long,LinkKindNamed)(const char *) PURE;
/*** LinkKindName - Get the name of a link flavor.
 *  	= cScrStr - The flavor name. Aggregate return.
 *  	: long - The ID of the flavor.
 *  	@ ILinkManager::GetRelation(flavor)
 */
	STDMETHOD_(cScrStr*,LinkKindName)(cScrStr &,long) PURE;
/*** LinkGet - Fill a structure with information about a link.
 *  	= long - Returns 0.
 *  	: long - The link ID.
 *  	: sLink & - Address of the structure that will recieve the information.
 *  	@ ILinkManager::Get(link,struct)
 */
	STDMETHOD_(long,LinkGet)(long,sLink &) PURE;
/*** LinkGetData - Retrieve the data associated with a link.
 *  	= cMultiParm - Aggregate return. Caller should free.
 *  	: long - The link ID.
 *  	: const char * - Name of the structure field to retrieve.
 */
	STDMETHOD_(cMultiParm*,LinkGetData)(cMultiParm &,long,const char *) PURE;
/*** LinkSetData - Set the data associated with a link.
 *  	= long - Returns 0.
 *  	: long - The link ID.
 *  	: const char * - The structure field to modify.
 *  	: const cMultiParm & - The data to assign.
 */
	STDMETHOD(LinkSetData)(long,const char *,const cMultiParm &) PURE;
};
DEFINE_IIDSTRUCT(ILinkToolsSrv,IID_ILinkToolsScriptService);

DECLARE_GUID(ILockedScriptService);
interface ILockSrv : IScriptServiceBase
{
/*** IsLocked - Test whether an object has the Locked property set.
 *  	= Bool - True if the object is locked.
 *  	: const object & - The object to check.
 */
	STDMETHOD_(Bool,IsLocked)(const object &) PURE;
};
DEFINE_IIDSTRUCT(ILockSrv,IID_ILockedScriptService);

DECLARE_GUID(INetworkingScriptService);
interface INetworkingSrv : IScriptServiceBase
{
#if (_DARKGAME == 3) || ((_DARKGAME == 2) && (_NETWORKING == 1))
/*** Broadcast - Send a message to over the network.
 *  	= Bool - The message was sent successfully.
 *  	: const object & - The object to send to.
 *  	: const char * - The message name.
 *  	: Bool - Send the message even if the object is a proxy.
 *  	: const cMultiParm & - Message data.
 */
	STDMETHOD_(Bool,Broadcast)(const object &,const char *,int,const cMultiParm &) PURE;
/*** SendToProxy - Send a message to an object on another computer.
 *  	= Bool - Returns true.
 *  	: const object & - The proxy host that will send the message.
 *  	: const object & - The destination of the message.
 *  	: const char * - The message name.
 *  	: const cMultiParm & - Message data.
 */
	STDMETHOD_(Bool,SendToProxy)(const object &,const object &,const char *,const cMultiParm &) PURE;
/*** TakeOver - Become the host of an object.
 *  	= Bool - Returns true.
 *  	: const object & - Object to grab.
 *  	@ IObjectNetworking::ObjTakeOver(obj)
 */
	STDMETHOD_(Bool,TakeOver)(const object &) PURE;
/*** GiveTo - Let an object be hosted by a different object.
 *  	= Bool - Returns true.
 *  	: const object & - Object to give.
 *  	: const object & - The new host.
 *  	@ IObjectNetworking::ObjGiveWithoutObjID(obj,host)
 */
	STDMETHOD_(Bool,GiveTo)(const object &,const object &) PURE;
/*** IsPlayer - Check if an object is one of the players.
 *  	= Bool - Is the object is a player.
 *  	: const object & - Object to test.
 */
	STDMETHOD_(Bool,IsPlayer)(const object &) PURE;
/*** IsMultiplayer - Check if the game is running in multi-player mode.
 *  	= Bool - Is multi-player mode.
 *  	@ INetManager::IsNetworkGame()
 */
	STDMETHOD_(Bool,IsMultiplayer)(void) PURE;
/*** SetProxyOneShotTimer - Send a timed message to the proxy for an object.
 *  	= tScrTimer - Timer handle.
 *  	: const object & - The destination object.
 *  	: const char * - The timer name.
 *  	: float - Time to delay the message, in seconds.
 *  	: const cMultiParm & - Message data.
 */
	STDMETHOD_(tScrTimer,SetProxyOneShotTimer)(const object &,const char *,float,const cMultiParm &) PURE;
/*** FirstPlayer - Begin an iteration of all players. The first player is the local owner.
 *  	= object - The object ID of the first player. Aggregate return.
 *  	@ INetManager::NetPlayerIterStart(iter)
 */
	STDMETHOD_(object*,FirstPlayer)(object &) PURE;
/*** NextPlayer - Continue an iteration of all players.
 *  	= object - The object ID of another player or 0 if there are no more players. Aggregate return.
 *  	@ INetManager::NetPlayerIterNext(iter,obj)
 */
	STDMETHOD_(object*,NextPlayer)(object &) PURE;
/*** Suspend - Prevent network messages from propagating.
 *  	= long - Returns 0.
 *  	@ INetManager::SuspendMessaging()
 */
	STDMETHOD(Suspend)(void) PURE;
/*** Resume - Allow network communication again. (Possibly flushes queued messages?)
 *  	= long - Returns 0.
 *  	@ INetManager::ResumeMessaging()
 */
	STDMETHOD(Resume)(void) PURE;
/*** HostedHere - Check if an object is hosted by this computer.
 *  	= Bool - True if the object is hosted here.
 *  	: const object & - Object to test.
 *  	@ IObjectNetworking::ObjHostedHere(obj)
 */
	STDMETHOD_(Bool,HostedHere)(const object &) PURE;
/*** IsProxy - Check if an object is hosted somewhere else.
 *  	= Bool - True if the object is a remote proxy.
 *  	: const object & - Object to test.
 *  	@ IObjectNetworking::ObjIsProxy(obj)
 */
	STDMETHOD_(Bool,IsProxy)(const object &) PURE;
/*** LocalOnly - Check if an object is locally specific.
 *  	= Bool - True if the object is not on the network.
 *  	: const object & - Object to test.
 *  	@ IObjectNetworking::ObjLocalOnly(obj)
 */
	STDMETHOD_(Bool,LocalOnly)(const object &) PURE;
/*** IsNetworking - Check if the computer is connected to a network.
 *  	= Bool - True if networking is active.
 *  	@ INetManager::Networking()
 */
	STDMETHOD_(Bool,IsNetworking)(void) PURE;
#if (_DARKGAME == 2)
/*** Owner - Get the object that hosts an object.
 *  	= object - The host object. Aggregate return.
 *  	: const object & - The hosted object.
 *  	@ IObjectNetworking::ObjHostPlayer(obj)
 */
	STDMETHOD_(object*,Owner)(object &,const object &) PURE;
#endif
#endif
};
DEFINE_IIDSTRUCT(INetworkingSrv,IID_INetworkingScriptService);

DECLARE_GUID(INullScriptService);

enum RelTransformType {
	RelObject,
	RelJoint,
	RelVHot,
	RelSubObject,
	RelSubPhysModel
};
DECLARE_GUID(IObjectScriptService);
interface IObjectSrv : IScriptServiceBase
{
/*** BeginCreate - Do the first half of a two-stage object creation.
 *  	= object - The new object. Aggregate return.
 *  	: object - The parent archetype for the new object.
 *  	@ IObjectSystem::BeginCreate(obj,1)
 */
	STDMETHOD_(object*,BeginCreate)(object &,object) PURE;
/*** EndCreate - Finish creating an object returned from BeginCreate.
 *  	= long - Returns 0 on success.
 *  	: object - The created object.
 *  	@ IObjectSystem::EndCreate(obj)
 */
	STDMETHOD(EndCreate)(object) PURE;
/*** Create - Add an object to the database.
 *  	= object - The new object. Aggregate return.
 *  	: object - The parent archetype for the new object.
 *  	@ IObjectSystem::Create(obj,1)
 */
	STDMETHOD_(object*,Create)(object &,object) PURE;
/*** Destroy - Remove an object from the database.
 *  	= long - Returns 0 on success.
 *  	: object - The object to destroy.
 *  	@ IObjectSystem::Destroy(obj)
 */
	STDMETHOD(Destroy)(object) PURE;
/*** Exists - Check if an object is in the database.
 *  	= true_bool - True if the object is valid. Aggregate return.
 *  	: object - The object to look for.
 *  	@ IObjectSystem::Exists(obj)
 */
	STDMETHOD_(true_bool*,Exists)(true_bool &,object) PURE;
/*** SetName - Change an object's name.
 *  	= long - Returns 0.
 *  	: object - The object to change.
 *  	: const char * - The new name of the object.
 *  	@ IObjectSystem::NameObject(obj,name)
 */
	STDMETHOD(SetName)(object,const char *) PURE;
/*** GetName - Return an object's name.
 *  	= cScrStr - The name of the object. Aggregate return. Should be freed by the caller.
 *  	: object - The object.
 *  	@ IObjectSystem::GetName(obj)
 */
	STDMETHOD_(cScrStr*,GetName)(cScrStr &,object) PURE;
/*** Named - Find an object given a name.
 *  	= object - The found object. Aggregate return.
 *  	: const char * - The name of the object.
 *  	@ IObjectSystem::GetObjectNamed(name)
 */
	STDMETHOD_(object*,Named)(object &,const char *) PURE;
/*** AddMetaProperty - Add a metaproperty to an object.
 *  	= long - Returns 0.
 *  	: object - The object to add the metaproperty to.
 *  	: object - The metaproperty to add.
 */
	STDMETHOD(AddMetaProperty)(object,object) PURE;
/*** RemoveMetaProperty - Add a metaproperty to an object.
 *  	= long - Returns 0.
 *  	: object - The object to remove the metaproperty from.
 *  	: object - The metaproperty to remove.
 */
	STDMETHOD(RemoveMetaProperty)(object,object) PURE;
/*** HasMetaProperty - Check if a metaproperty is applied to an object.
 *  	= true_bool - True if the object is linked with the metaproperty. Aggregate return.
 *  	: object - The object that might have the metaproperty.
 *  	: object - The metaproperty to look for.
 *  	@ ITraitManager::ObjHasDonorIntrinsically(obj,mp)
 */
	STDMETHOD_(true_bool*,HasMetaProperty)(true_bool &,object,object) PURE;
/*** InheritsFrom - Check if an object inherits properties from another object. May be a direct ancestor or a metaproperty.
 *  	= true_bool - True if the object inherits from the archetype. Aggregate return.
 *  	: object - The object that might be a descendant.
 *  	: object - The ancestor object.
 *  	@ ITraitManager::ObjHasDonor(obj,mp)
 */
	STDMETHOD_(true_bool*,InheritsFrom)(true_bool &,object,object) PURE;
/*** IsTransient - Check if an object is transient.
 *  	= true_bool - True if the object is transient. Aggregate return.
 *  	: object - The object to check.
 *  	@ IObjectSystem::ObjIsTransient(obj)
 */
	STDMETHOD_(true_bool*,IsTransient)(true_bool &,object) PURE;
/*** SetTransience - Set whether the object will be saved to disk.
 *  	= long - Returns 0.
 *  	: object - The object to change.
 *  	: true_bool - Whether or not the object should be transient.
 *  	@ IObjectSystem::SetObjTransience(obj,bool)
 */
	STDMETHOD(SetTransience)(object,true_bool) PURE;
/*** Position - Get the location of an object.
 *  	= cScrVec - The object's XYZ vector. Aggregate return.
 *  	: object - The object to query.
 */
	STDMETHOD_(cScrVec*,Position)(cScrVec &,object) PURE;
/*** Facing - Get the direction an object is facing.
 *  	= cScrVec - The object's HPB vector as degrees. Aggregate return.
 *  	: object - The object to query.
 */
	STDMETHOD_(cScrVec*,Facing)(cScrVec &,object) PURE;
/*** Teleport - Move an object to a different location.
 *  	= long - Returns 0.
 *  	: object - The object to move.
 *  	: const cScrVec & - The new location for the object.
 *  	: const cScrVec & - The new facing for the object, as degrees.
 *  	: object - An object to measure the new location and facing relative from. 0 for absolute positioning.
 *  	@ IGameTools::TeleportObject(obj,loc,fac,rel)
 */
	STDMETHOD(Teleport)(object,const cScrVec  &,const cScrVec  &,object) PURE;
#if (_DARKGAME == 2) || (_DARKGAME == 3)
/*** IsPositionValid - Check if the object is inside the worldrep.
 *  	= true_bool - True if the object is not in solid space. Aggregate return.
 *  	: object - The object to query.
 */
	STDMETHOD_(true_bool*,IsPositionValid)(true_bool &,object) PURE;
#endif
#if (_DARKGAME == 2)
/*** FindClosestObjectNamed - Locate the object that is physically closest to a reference object.
 *  	= object - The nearest object, if any. Aggregate return.
 *  	: int - The object to center the search about.
 *  	: const char * - The name of an archetype that the located object should inherit from.
 */
	STDMETHOD_(object*,FindClosestObjectNamed)(object &,int,const char *) PURE;
#endif
/*** AddMetaPropertyToMany - Add a metaproperty to multiple objects.
 *  	= int - Number of objects affected.
 *  	: object - The metaproperty to add.
 *  	: const cScrStr & - The objects to modify.
 */
	STDMETHOD_(int,AddMetaPropertyToMany)(object,const cScrStr  &) PURE;
/*** RemoveMetaPropertyFromMany - Remove a metaproperty from multiple objects.
 *  	= int - Number of objects affected.
 *  	: object - The metaproperty to remove.
 *  	: const cScrStr & - The objects to modify.
 */
	STDMETHOD_(int,RemoveMetaPropertyFromMany)(object,const cScrStr  &) PURE;
/*** RenderedThisFrame - Check if the object was included in the last rendering pass.
 *  	= true_bool - True if the object is visible. Aggregate return.
 *  	: object - The object to query.
 */
	STDMETHOD_(true_bool*,RenderedThisFrame)(true_bool &,object) PURE;
#ifdef _NEWDARK
#if (_DARKGAME == 3)
	STDMETHOD_(object*,FindClosestObjectNamed)(object &,int,const char *) PURE;
#endif
/*** ObjectToWorld - Translate a relative vector to absolute.
 *  	= cScrVec - The absolute position in world coordinates. Aggregate return.
 *  	: object - The object to measure from.
 *  	: const cScrVec & - Position relative to the location and rotation of the object.
 */
	STDMETHOD_(cScrVec*,ObjectToWorld)(cScrVec &,object,const cScrVec &) PURE;
/*** WorldToObject - Transform an absolute vector to relative.
 *  	! Implemented by NewDark version 1.23 or later only.
 *  	= cScrVec - Position relative to the location and rotation of the object. Aggregate return.
 *  	: object - The object to measure from.
 *  	: const cScrVec & - The absolute position in world coordinates.
 */
	STDMETHOD_(cScrVec*,WorldToObject)(cScrVec&,object,const cScrVec &) PURE;
/*** CalcRelTransform - Get the location and rotation of an object relative to a base object.
 *  	! Implemented by NewDark version 1.23 or later only.
 *  	= true_bool - Aggregate return. (FIXME would this be false for anything other than invalid object?)
 *  	: object - Base object to measure from.
 *  	: object - Destination object.
 *  	: cScrVec & - Relative location.
 *  	: cScrVec & - Relative rotation.
 *  	: int - Where to measure from on the base object. See enum RelTransformType.
 *  	: int - Number of the submodel, vhot, or joint if applicable.
 */
	STDMETHOD_(true_bool*,CalcRelTransform)(true_bool&,object,object,cScrVec &,cScrVec &,int,int) PURE;
#endif
};
DEFINE_IIDSTRUCT(IObjectSrv,IID_IObjectScriptService);

DECLARE_GUID(IPGroupScriptService);
interface IPGroupSrv : IScriptServiceBase
{
/*** SetActive - Turn a particle SFX on or off.
 *  	= Bool - Returns true.
 *  	: int - Object ID of the particle group.
 *  	: Bool - Activate or deactivate.
 */
	STDMETHOD_(Bool,SetActive)(int,Bool) PURE;
};
DEFINE_IIDSTRUCT(IPGroupSrv,IID_IPGroupScriptService);

enum ePhysMsgType {
	kPhysCollision = 1,
	kPhysContact = 2,
	kPhysEnterExit = 4,
	kPhysFellAsleep = 8,
	kPhysWokeUp = 16
};
DECLARE_GUID(IPhysicsScriptService);
interface IPhysSrv : IScriptServiceBase
{
/*** SubscribeMsg - Register an object to receive certain messages.
 *  	= Bool - Returns true.
 *  	: object - Object that will recieve the messages.
 *  	: int - A bit mask specifying which messages to begin listening for.
 */
	STDMETHOD_(Bool,SubscribeMsg)(object,int) PURE;
/*** UnsubscribeMsg - Stop listening for certain messages.
 *  	= Bool - Returns true.
 *  	: object - Object that recieved the messages.
 *  	: int - A bit mask specifying which messages to stop listening for.
 */
	STDMETHOD_(Bool,UnsubscribeMsg)(object,int) PURE;
/*** LaunchProjectile - Emit an object.
 *  	= object - The emitted object. Aggregate return.
 *  	: object - Object to launch from.
 *  	: object - Archetype to emit.
 *  	: float - Velocity scale of projectile.
 *  	: int - 1=ZeroVel, 2=PushOut, 4=RelativeVelocity, 8=Gravity, 512=TellAI, 1024=NoPhysics.
 *  	: const cScrVec & - Initial velocity. Will be added to the velocity inherited from the archetype or emitter.
 */
	STDMETHOD_(object*,LaunchProjectile)(object &,object,object,float,int,const cScrVec &) PURE;
/*** SetVelocity - Set the current speed of an object.
 *  	= long - Returns 0.
 *  	: object - The object to modify.
 *  	: const cScrVec & - The new velocity of the object.
 */
	STDMETHOD(SetVelocity)(object,const cScrVec &) PURE;
/*** GetVelocity - Retrieve the current speed of an object.
 *  	= long - Returns 0.
 *  	: object - The object to query.
 *  	: cScrVec & - Address of a variable that will receive the velocity.
 */
	STDMETHOD(GetVelocity)(object,cScrVec  &) PURE;
#if (_DARKGAME == 2)
/*** ControlVelocity - Lock the velocity of an object.
 *  	= long - Returns 0.
 *  	: object - The object to modify.
 *  	: const cScrVec & - The new velocity of the object.
 */
	STDMETHOD(ControlVelocity)(object,const cScrVec &) PURE;
/*** StopControlVelocity - Unlock the velocity of an object.
 *  	= long - Returns 0.
 *  	: object - The object to modify.
 */
	STDMETHOD(StopControlVelocity)(object) PURE;
#endif
/*** SetGravity - Set the gravity of an object.
 *  	= long - Returns 0.
 *  	: object - The object to modify.
 *  	: float - The new gravity of the object.
 */
	STDMETHOD(SetGravity)(object,float) PURE;
/*** GetGravity - Retrieve the gravity of an object.
 *  	= float - The current gravity.
 *  	: object - The object to query.
 */
	STDMETHOD_(float,GetGravity)(object) PURE;
#if (_DARKGAME != 1)
/*** HasPhysics - Check if an object has a physics model.
 *  	= Bool - True if the object has a physics model.
 *  	: object - The object to query.
 */
	STDMETHOD_(Bool,HasPhysics)(object) PURE;
/*** IsSphere - Check if an object is a sphere.
 *  	= Bool - True if the object has a sphere-type physics model.
 *  	: object - The object to query.
 */
	STDMETHOD_(Bool,IsSphere)(object) PURE;
/*** IsOBB - Check if an object is an oriented bounding-box.
 *  	= Bool - True if the object has an OBB-type physics model.
 *  	: object - The object to query.
 */
	STDMETHOD_(Bool,IsOBB)(object) PURE;
/*** ControlCurrentLocation - Lock the location of an object to its current values.
 *  	= long - Returns 0 on success.
 *  	: object - The object to lock.
 */
	STDMETHOD(ControlCurrentLocation)(object) PURE;
/*** ControlCurrentRotation - Lock the facing of an object to its current values.
 *  	= long - Returns 0 on success.
 *  	: object - The object to lock.
 */
	STDMETHOD(ControlCurrentRotation)(object) PURE;
/*** ControlCurrentPosition - Lock the location and facing of an object to its current values.
 *  	= long - Returns 0 on success.
 *  	: object - The object to lock.
 */
	STDMETHOD(ControlCurrentPosition)(object) PURE;
/*** DeregisterModel - Remove the physics model of an object.
 *  	= long - Returns 0 on success.
 *  	: object - The object to modify.
 */
	STDMETHOD(DeregisterModel)(object) PURE;
/*** PlayerMotionSetOffset - Nudge the player model.
 *  	: int - Submodel to move.
 *  	: cScrVec & - New position.
 */
	STDMETHOD_(void,PlayerMotionSetOffset)(int,cScrVec &) PURE;
/*** Activate - Wake up an object at rest.
 *  	= long - Returns 0 on success.
 *  	: const object - The object to activate.
 */
	STDMETHOD(Activate)(const object) PURE;
/*** ValidPos - Test if an object is not in solid space.
 *  	= Bool - True if position is valid.
 *  	: const object - The object to test.
 */
	STDMETHOD_(Bool,ValidPos)(const object) PURE;
#endif
#ifdef _NEWDARK
/*** IsRope - Test if an object is climbable.
 *  	= Bool - True if the object is a rope.
 *  	: const object & - The object to test.
 */
	STDMETHOD_(Bool,IsRope)(const object &) PURE;
/*** GetClimbingObject - Get the ID of the climbable object something is attached to.
 *  	: const object & - The object that is attached. Typically the Player.
 *  	: object & - Returns the climbable object or OBJ_NULL.
 */
	STDMETHOD_(void,GetClimbingObject)(const object &,object &) PURE;
#endif
};
DEFINE_IIDSTRUCT(IPhysSrv,IID_IPhysicsScriptService);

DECLARE_GUID(IPickLockScriptService);
interface IPickLockSrv : IScriptServiceBase
{
/*** Ready - Prepare a pick.
 *  	= Bool - True on success.
 *  	: object - The host object.
 *  	: object - The pick.
 */
	STDMETHOD_(Bool,Ready)(object,object) PURE;
/*** UnReady - Release a pick.
 *  	= Bool - True on success.
 *  	: object - The host object.
 *  	: object - The pick.
 */
	STDMETHOD_(Bool,UnReady)(object,object) PURE;
/*** StartPicking - Begin using a pick on an object.
 *  	= Bool - True on success.
 *  	: object - The host object.
 *  	: object - The pick.
 *  	: object - The object being picked.
 */
	STDMETHOD_(Bool,StartPicking)(object,object,object) PURE;
/*** FinishPicking - Stop picking an object.
 *  	= Bool - True on success.
 *  	: object - The pick.
 */
	STDMETHOD_(Bool,FinishPicking)(object) PURE;
/*** CheckPick - Test if a pick can be used.
 *  	= int - Returns the pick state.
 *  	: object - The pick.
 *  	: object - The object being picked.
 *  	: int - Flags of some sort. Not used.
 */
	STDMETHOD_(int,CheckPick)(object,object,int) PURE;
/*** DirectMotion - Move the pick arm. Not used.
 *  	= Bool - True on success.
 *  	: Bool - Activate or deactivate the picking motion.
 */
	STDMETHOD_(Bool,DirectMotion)(Bool) PURE;
};
DEFINE_IIDSTRUCT(IPickLockSrv,IID_IPickLockScriptService);

DECLARE_GUID(IPlayerLimbsScriptService);
interface IPlayerLimbsSrv : IScriptServiceBase
{
/*** Equip - Display the player arm.
 *  	= Bool - True on success.
 *  	: object - Host object of the arm.
 */
	STDMETHOD_(Bool,Equip)(object) PURE;
/*** UnEquip - Hide the player arm.
 *  	= Bool - True on success.
 *  	: object - Host object of the arm.
 */
	STDMETHOD_(Bool,UnEquip)(object) PURE;
/*** StartUse - Begin moving the player arm.
 *  	= Bool - True on success.
 *  	: object - Host object of the arm.
 */
	STDMETHOD_(Bool,StartUse)(object) PURE;
/*** FinishUse - End an arm motion.
 *  	= Bool - True on success.
 *  	: object - Host object of the arm.
 */
	STDMETHOD_(Bool,FinishUse)(object) PURE;
};
DEFINE_IIDSTRUCT(IPlayerLimbsSrv,IID_IPlayerLimbsScriptService);

DECLARE_GUID(IPropertyScriptService);
interface IPropertySrv : IScriptServiceBase
{
/*** Get - Retrieve some data from a property.
 *  	= cMultiParm - Aggregate return. Caller should free if string or vector.
 *  	: object - The object to query.
 *  	: const char * - The property name.
 *  	: const char * - The field name. NULL if the property is only a single field, otherwise it's the exact name that's displayed in the editor dialog in DromEd.
 */
	STDMETHOD_(cMultiParm*,Get)(cMultiParm &,object,const char *,const char *) PURE;
/*** Set - Write a value into a field of a property.
 *  	= long - Returns 0 on success.
 *  	: const char * - The property name.
 *  	: const char * - The field name.
 *  	: const cMultiParm & - The data to write.
 */
	STDMETHOD(Set)(object,const char *,const char *,const cMultiParm &) PURE;
/*** SetSimple - Write a value into a simple property. Identical to calling Set with a NULL field name.
 *  	= long - Returns 0 on success.
 *  	: const char * - The property name.
 *  	: const cMultiParm & - The data to write.
 */
	STDMETHOD(SetSimple)(object,const char *,const cMultiParm &) PURE;
#if (_DARKGAME == 2) || (_DARKGAME == 3)
/*** SetLocal - Write a value into a field of a property without propogating across the network.
 *  	= long - Returns 0 on success.
 *  	: const char * - The property name.
 *  	: const char * - The field name.
 *  	: const cMultiParm & - The data to write.
 */
	STDMETHOD(SetLocal)(object,const char *,const char *,const cMultiParm &) PURE;
#endif
/*** Add - Create an instance of a property on an object.
 *  	= long - Returns 0 on success.
 *  	: object - The object to receive the property.
 *  	: const char * - The property name.
 *  	@ IProperty::Create(obj)
 */
	STDMETHOD(Add)(object,const char *) PURE;
/*** Remove - Delete an instance of a property from an object.
 *  	= long - Returns 0 on success.
 *  	: object - The object to modify.
 *  	: const char * - The property name.
 *  	@ IProperty::Delete(obj)
 */
	STDMETHOD(Remove)(object,const char *) PURE;
/*** CopyFrom - Copy the contents of a property from one object to another.
 *  	= long - Returns 0 on success.
 *  	: object - The destination object.
 *  	: const char * - The property name.
 *  	: object - The source object.
 *  	@ IProperty::Copy(dst,src)
 */
	STDMETHOD_(long,CopyFrom)(object,const char *,object) PURE;
/*** Possessed - Test if an object has an instance of a property.
 *  	= Bool - True if the property is on the object or its archetype.
 *  	: object - The object to query.
 *  	: const char * - The property name.
 *  	@ IProperty::IsRelevant(obj)
 */
	STDMETHOD_(Bool,Possessed)(object,const char *) PURE;
};
DEFINE_IIDSTRUCT(IPropertySrv,IID_IPropertyScriptService);

DECLARE_GUID(IPuppetScriptService);
interface IPuppetSrv : IScriptServiceBase
{
/*** PlayMotion - Play a motion schema on an object.
 *  	= true_bool - True if the motion played. Aggregate return.
 *  	: object - The host object.
 *  	: const char * - The schema name.
 */
	STDMETHOD_(true_bool*,PlayMotion)(true_bool &,const object,const char *) PURE;
};
DEFINE_IIDSTRUCT(IPuppetSrv,IID_IPuppetScriptService);

DECLARE_GUID(IQuestScriptService);
interface IQuestSrv : IScriptServiceBase
{
/*** SubscribeMsg - Register an object to receive notifications when a quest variable changes.
 *  	= Bool - Returns true.
 *  	: object - The object that will receive the messages.
 *  	: const char * - The quest variable name.
 *  	: eQuestDataType - Which database to monitor for changes.
 *  	@ IQuestData::SubscribeMsg(obj,name,flags)
 */
	STDMETHOD_(Bool,SubscribeMsg)(object,const char *,eQuestDataType) PURE;
/*** UnsubscribeMsg - Stop listening for quest variable messages.
 *  	= Bool - Returns true.
 *  	: object - The object that was previously registered.
 *  	: const char * - The quest variable name.
 *  	@ IQuestData::UnsubscribeMsg(obj,name)
 */
	STDMETHOD_(Bool,UnsubscribeMsg)(object,const char *) PURE;
/*** Set - Change the value of a quest variable.
 *  	= long -  Returns 0.
 *  	: const char * - The quest variable name.
 *  	: int - The new value of the variable.
 *  	: eQuestDataType - The database to modify. 0 is mission, 1 is campaign.
 *  	@ IQuestData::Set(name,value) or IQuestData::Create(name,value,type)
 */
	STDMETHOD(Set)(const char *,int,eQuestDataType) PURE;
/*** Get - Retrieve the value of a quest variable.
 *  	= int - The value of the variable. Returns 0 if the variable doesn't exist.
 *  	: const char * - The quest variable name.
 *  	@ IQuestData::Get(name)
 */
	STDMETHOD_(int,Get)(const char *) PURE;
/*** Exists - Test if a quest variable is defined.
 *  	= Bool - True if the variable exists.
 *  	: const char * - The quest variable name.
 *  	@ IQuestData::Exists(name)
 */
	STDMETHOD_(Bool,Exists)(const char *) PURE;
/*** Delete - Remove a quest variable from either database.
 *  	= Bool - Returns true if the variable doesn't exist.
 *  	: const char * - The quest variable name.
 *  	@ IQuestData::Delete(name)
 */
	STDMETHOD_(Bool,Delete)(const char *) PURE;
};
DEFINE_IIDSTRUCT(IQuestSrv,IID_IQuestScriptService);

DECLARE_GUID(IShockGameScriptService);
interface IShockGameSrv : IScriptServiceBase
{
#if (_DARKGAME == 3) || (_SHOCKINTERFACES == 1)
/*** DestroyCursorObj - Destroy the current cursor object.
 *  	= long - Returns 0.
 */
	STDMETHOD(DestroyCursorObj)(void) PURE;
/*** DestroyInvObj - Destroy an object which may be in cursor mode.
 *  	= Bool - Returns true.
 *  	: const object & - Object to destroy.
 */
	STDMETHOD_(Bool,DestroyInvObj)(const object &) PURE;
/*** HideInvObj - Takes an object out of the player's inventory.
 *  	= Bool - Returns true.
 *  	: const object & - Inventory object.
 *  	@ IContainSys::Remove(player,obj)
 */
	STDMETHOD_(Bool,HideInvObj)(const object &) PURE;
	/* [20] */
/*** SetPlayerPsiPoints - Modify the player's psi points.
 *  	= Bool - Returns true.
 *  	: int - New value for psi points.
 *  	@ IPlayerPsi::SetPoints(value)
 */
	STDMETHOD_(Bool,SetPlayerPsiPoints)(int) PURE;
/*** GetPlayerPsiPoints - Get the player's psi points.
 *  	= int - Current psi points.
 *  	@ IPlayerPsi::GetPoints()
 */
	STDMETHOD_(int,GetPlayerPsiPoints)(void) PURE;
/*** AttachCamera - Set the camera to a named object.
 *  	= long - Returns 0.
 *  	: const cScrStr & - Name of the object to attach to.
 *  	@ IShockCamera::Attach(name)
 */
	STDMETHOD(AttachCamera)(const cScrStr &) PURE;
/*** CutSceneModeOn - Enter scripted camera mode.
 *  	= long - Returns 0.
 *  	: const cScrStr & - Scene name.
 *  	@ IShockCamera::SetScene(name)
 */
	STDMETHOD(CutSceneModeOn)(const cScrStr &) PURE;
	/* [30] */
/*** CutSceneModeOff - Exit scripted camera mode.
 *  	= long - Returns 0.
 *  	@ IShockCamera::SetEditMode(Normal)
 */
	STDMETHOD(CutSceneModeOff)(void) PURE;
/*** CreatePlayerPuppet - Create an object that acts like the player. Uses a custom model.
 *  	= int - Object ID of the new player.
 *  	: const cScrStr & - Model name for the puppet.
 */
	STDMETHOD_(int,CreatePlayerPuppet)(const cScrStr &) PURE;
/*** CreatePlayerPuppetDefault - Create an object that acts like the player. Uses the default object model.
 *  	= int - Object ID of the new player.
 */
	STDMETHOD_(int,CreatePlayerPuppetDefault)(void) PURE;
/*** DestroyPlayerPuppet - Destroy the current player puppet object.
 *  	= Bool - Returns true.
 */
	STDMETHOD_(Bool,DestroyPlayerPuppet)(void) PURE;
	/* [40] */
/*** Replicator - Display the replicator interface.
 *  	= long - Returns 0.
 *  	: const object & - The replicator object.
 */
	STDMETHOD(Replicator)(const object &) PURE;
/*** Container - Display the container interface.
 *  	= long - Returns 0.
 *  	: const object & - The container object.
 */
	STDMETHOD(Container)(const object &) PURE;
#if (_DARKGAME == 1)
	virtual int __stdcall f13() = 0;
#endif
/*** YorN - Display a yes-or-no propmpt.
 *  	= long - Returns 0.
 *  	: const object & - Object that will recieve the result of the prompt.
 *  	: const cScrStr & - Message to display.
 */
	STDMETHOD(YorN)(const object &,const cScrStr &) PURE;
/*** Keypad - Display the keypad interface.
 *  	= long - Returns 0.
 *  	: const object & - The keypad object.
 */
	STDMETHOD(Keypad)(const object &) PURE;
#if (_DARKGAME != 1)
	/* [50] */
/*** HRM - Display the hack/repair/modify/maintain/research interface.
 *  	= long - Returns 0 on success.
 *  	: int - Type of action. 0=Hack, 1=Repair, 2=Modify, 3=Maintain, 4=Research.
 *  	: const object & - Object being modified.
 *  	: Bool - Is psi being used.
 */
	STDMETHOD(HRM)(int,const object &,Bool) PURE;
/*** TechTool - Display an object's HRM interface.
 *  	= long - Returns 0 on success.
 *  	: const object & - Object being modified.
 */
	STDMETHOD(TechTool)(const object &) PURE;
#endif
/*** UseLog - Read an object log.
 *  	= long - Return 0 on success.
 *  	: const object & - Log object. Is destroyed after use.
 *  	: Bool - Broadcast the log to other players.
 */
	STDMETHOD(UseLog)(const object &,Bool) PURE;
/*** TriggerLog - Displays a log message.
 *  	= Bool - True on success.
 *  	: int - Type of log. 0=email, 1=log, 2=video, 3=help, 4=research
 *  	: int - Deck level.
 *  	: int - Log number.
 *  	: Bool - Always show.
 */
	STDMETHOD_(Bool,TriggerLog)(int,int,int,int) PURE;
	/* [60] */
/*** FindLogData - Retrieve log data from an object.
 *  	= long - Returns 0 on success.
 *  	: const object & - Log object.
 *  	: int - Type of log.
 *  	: int * - Deck level.
 *  	: int * - Log number.
 */
	STDMETHOD(FindLogData)(const object &,int,int *,int *) PURE;
/*** PayNanites - Attempt to subtract nanites from the player.
 *  	= long - Non-zero if the player doesn't have enough nanites.
 *  	: int - Amount to subtract. May be negative to add nanites.
 */
	STDMETHOD(PayNanites)(int) PURE;
/*** OverlayChange - Change the status of an overlay panel.
 *  	= long - Returns 0.
 *  	: int - Overlay ID.
 *  	: int - Display state. 0=Off, 1=On, 2=Toggle
 */
	STDMETHOD(OverlayChange)(int,int) PURE;
/*** Equipped - Get the object contained in a particular slot.
 *  	= object - Contained object. Aggregate return.
 *  	: int - Slot to look in. The Contains link type minus 1000.
 *  	@ IShockPlayer::GetEquip(player,id)
 */
	STDMETHOD_(object*,Equipped)(object &,int) PURE;
	/* [70] */
/*** LevelTransport - Change the mission map.
 *  	= long - Returns 0 on success.
 *  	: const char * - Mission name.
 *  	: int - Location ID.
 *  	: uint - Flags. 1=Transport elevatorable objects, 2=Resync the network
 */
	STDMETHOD(LevelTransport)(const char *,int,uint) PURE;
/*** CheckLocked - Determine if a creature can open an object.
 *  	= Bool - True if the object is locked.
 *  	: const object & - Object to check.
 *  	: Bool - If true, display a message if locked.
 *  	: const object & - Player or AI attempting to use the object. Required when using keys.
 */
	STDMETHOD_(Bool,CheckLocked)(const object &,Bool,const object &) PURE;
/*** AddText - Display text on a player's screen.
 *  	= long - Returns 0.
 *  	: const char * - Text to display.
 *  	: const object & - Player that will see the text, or 0 to display everywhere.
 *  	: int - Time the text will be visible, in milliseconds.
 */
	STDMETHOD(AddText)(const char *,const object &,int) PURE;
/*** AddTranslatableText - Display a string from a resource.
 *  	= long - Returns 0.
 *  	: const char * - String name.
 *  	: const char * - Resource name.
 *  	: const object & - Player.
 *  	: int - Time in milliseconds.
 */
	STDMETHOD(AddTranslatableText)(const char *,const char *,const object &,int) PURE;
	/* [80] */
/*** AmmoLoad - Add or change the ammunition in a gun.
 *  	= long - Returns 0 on success.
 *  	: const object & - Gun.
 *  	: const object & - Ammo.
 */
	STDMETHOD(AmmoLoad)(const object &,const object &) PURE;
#if (_DARKGAME != 1)
/*** GetClip - Get the size of a clip.
 *  	= int - Number of rounds.
 *  	: const object & - Ammo.
 */
	STDMETHOD_(int,GetClip)(const object &) PURE;
#endif
/*** AddExp - Give experience cookies.
 *  	= long - Returns 0.
 *  	: const object & - Recipient. Can be 0 to give to the player.
 *  	: int - Amount.
 *  	: Bool - Show message if true.
 */
	STDMETHOD(AddExp)(const object &,int,Bool) PURE;
/*** HasTrait - Check if a player has a trait.
 *  	= Bool - True if the trait is active.
 *  	: const object & - Object to check.
 *  	: int - Trait ID to look for.
 */
	STDMETHOD_(Bool,HasTrait)(const object &,int) PURE;
	/* [90] */
/*** HasImplant - Check if a player is using an implant.
 *  	= Bool - True if the implant is active.
 *  	: const object & - Object to check.
 *  	: int - Implant ID to look for.
 */
	STDMETHOD_(Bool,HasImplant)(const object &,int) PURE;
/*** HealObj - Add hit points to an object.
 *  	= long - Returns 0 on success.
 *  	: const object & - Object to heal.
 *  	: int - Number of hit points to add. May be negative.
 */
	STDMETHOD(HealObj)(const object &,int) PURE;
/*** OverlaySetObj - Associate an object with an interface panel.
 *  	= long - Returns 0.
 *  	: int - The overlay ID.
 *  	: const object & - Object to that will receive the messages.
 */
	STDMETHOD(OverlaySetObj)(int,const object &) PURE;
/*** Research - Display the research interface.
 *  	= long - Returns 0.
 */
	STDMETHOD(Research)(void) PURE;
	/* [A0] */
/*** GetArchetypeName - Get the name of an object's archetype.
 *  	= cScrStr - Archetype name. Aggregate return.
 *  	: const object & - The child object.
 *  	@ ITraitManager::GetArchetype(obj)
 */
	STDMETHOD_(cScrStr*,GetArchetypeName)(cScrStr &,const object &) PURE;
/*** OverlayOn - Check if an overlay panel is currently displayed.
 *  	= Bool - Returns true if the overlay is on.
 *  	: int - The overlay ID.
 */
	STDMETHOD_(Bool,OverlayOn)(int) PURE;
/*** FindSpawnPoint - Get a spawn point linked from an object.
 *  	= object - The spawn point. Aggregate return.
 *  	: const object & - The source object.
 *  	: uint - Spawn flags. See the property.
 */
	STDMETHOD_(object*,FindSpawnPoint)(object &,const object &,uint) PURE;
/*** CountEcoMatching - Find physical objects of an ecology type.
 *  	= int - Number of matching objects.
 *  	: int - Eco type.
 */
	STDMETHOD_(int,CountEcoMatching)(int) PURE;
	/* [B0] */
/*** GetStat - Get a player stat.
 *  	= int - Stat value.
 *  	: const object & - Object to check.
 *  	: int - Stat ID. 0=STR, 1=END, 2=PSI, 3=AGI, 4=CYB
 *  	@ IShockPlayer::GetStat(stat)
 */
	STDMETHOD_(int,GetStat)(const object &,int) PURE;
/*** GetSelectedObj - Return the currently selected object.
 *  	= object - The hilighted object. Aggregate return.
 */
	STDMETHOD_(object*,GetSelectedObj)(object &) PURE;
/*** AddInvObj - Try to put an object in the player's inventory.
 *  	= Bool - True on success.
 *  	: const object & - Object to add.
 */
	STDMETHOD_(Bool,AddInvObj)(const object &) PURE;
/*** RecalcStats - Adjust a player's stats after having modified properties or links.
 *  	= long - Returns 0.
 *  	: const object & - Player to update.
 *  	@ IShockPlayer::RecalcData(player)
 */
	STDMETHOD(RecalcStats)(const object &) PURE;
	/* [C0] */
/*** PlayVideo - Display a movie.
 *  	= long - Returns 0.
 *  	: const char * - Filename of the movie.
 */
	STDMETHOD(PlayVideo)(const char *) PURE;
#if (_DARKGAME != 1)
/*** ClearRadiation - Cancel the radiation hazard.
 *  	= long - Returns 0.
 */
	STDMETHOD(ClearRadiation)(void) PURE;
/*** SetPlayerVolume - Change the rate of the player's movement.
 *  	: float - Movement scale.
 */
	STDMETHOD_(void,SetPlayerVolume)(float) PURE;
/*** RandRange - [low, high]
 *  	= int - A (psuedo) random number.
 *  	: int - The lowest number to return.
 *  	: int - The highest number to return.
 */
	STDMETHOD_(int,RandRange)(int,int) PURE;
	/* [D0] */
/*** LoadCursor - Set the cursor object.
 *  	= Bool - True on success.
 *  	: const object & - Object that will be the cursor.
 */
	STDMETHOD_(Bool,LoadCursor)(const object &) PURE;
/*** AddSpeedControl - Change the speed of Player.
 *  	: const char * - ID of the control. Speed controls can be stacked and removed out-of-order.
 *  	: float - Amount to multiply the speed by.
 *  	: float - Multiplier for turning speed. Appears to be ineffective.
 */
	STDMETHOD_(void,AddSpeedControl)(const char *,float,float) PURE;
/*** RemoveSpeedControl - Remove a previously applied speed control.
 *  	: char * - ID of the control.
 */
	STDMETHOD_(void,RemoveSpeedControl)(const char *) PURE;
/*** PreventSwap - Avoid changing the cursor object when an inventory object is selected.
 *  	= long - Returns 0.
 */
	STDMETHOD(PreventSwap)(void) PURE;
	/* [E0] */
/*** GetDistantSelectedObj - Find the object that the player is looking at.
 *  	= object - An object in the player's crosshairs. Aggregate return.
 */
	STDMETHOD_(object*,GetDistantSelectedObj)(object &) PURE;
/*** Equip - Put an object in an inventory slot.
 *  	= long - Returns 0.
 *  	: int - The slot ID. The Contains type is the ID plus 1000.
 *  	: const object & - The object to equip.
 *  	@ IShockPlayer::Equip(player,id,obj,1)
 */
	STDMETHOD(Equip)(int,const object &) PURE;
/*** OverlayChangeObj - Set the state and associated object of an interface panel.
 *  	= long - Returns 0.
 *  	: int - Overlay ID.
 *  	: int - Display state.
 *  	: const object & - Object that will recieve the messages.
 */
	STDMETHOD(OverlayChangeObj)(int,int,const object &) PURE;
/*** SetObjState - Change the state of an object.
 *  	= long - Returns 0.
 *  	: const object & - Object to modify.
 *  	: eShockObjState - New state.
 */
	STDMETHOD(SetObjState)(const object &,eShockObjState) PURE;
	/* [F0] */
/*** RadiationHack - Set radiation to 0 on all objects except the player.
 *  	= long - Returns 0.
 */
	STDMETHOD(RadiationHack)(void) PURE;
/*** DestroyAllByName - Destroy all objects that descend from an archetype.
 *  	= long - Returns 0 on success.
 *  	: const char * - Archetype name.
 */
	STDMETHOD(DestroyAllByName)(char const *) PURE;
/*** AddTextObjProp - Display the resource string from an object's property.
 *  	= long - Returns 0.
 *  	: const object & - Object to read the property from.
 *  	: const char * - The property name. Should be a label.
 *  	: const object & - The player that will see the text.
 *  	: int - Time in milliseconds.
 */
	STDMETHOD(AddTextObjProp)(const object &,const char *,const object &,int) PURE;
/*** DisableAlarmGlobal - Turn off all alarms.
 *  	= long - Returns 0.
 */
	STDMETHOD(DisableAlarmGlobal)(void) PURE;
	/* [100] */
/*** Frob - Make the player frob the currently selected item.
 *  	: Bool - Ignore blocking objects. Use this for inventory objects.
 */
	STDMETHOD_(void,Frob)(Bool) PURE;
/*** TweqAllByName - Activate the tweqs on all objects that descend from an archetype.
 *  	= long - Returns 0 on success.
 *  	: const char * - Archetype name.
 *  	: Bool - Activate if true, otherwise halt.
 */
	STDMETHOD(TweqAllByName)(const char *,Bool) PURE;
/*** SetExplored - Set whether a location has been explored.
 *  	= long - Returns 0.
 *  	: int - Location ID.
 *  	: char - Non-zero if the location is explored.
 */
	STDMETHOD(SetExplored)(int,char) PURE;
/*** RemoveFromContainer - Remove an object from a container.
 *  	= long - Returns 0.
 *  	: const object & - Contained object.
 *  	: const object & - Container object.
 */
	STDMETHOD(RemoveFromContainer)(const object &,const object &) PURE;
	/* [110] */
/*** ActivateMap - Set a campaign quest variable with the name "Map" plus the name of the current map.
 *  	= long - Returns 0.
 */
	STDMETHOD(ActivateMap)(void) PURE;
/*** SimTime - Get time the game has been active.
 *  	= int - Current sim time.
 */
	STDMETHOD_(int,SimTime)(void) PURE;
/*** StartFadeIn - Set the screen to a solid color, then gradually fade to full visibility.
 *  	: int - Time in milliseconds.
 *  	: unsigned char - Red.
 *  	: unsigned char - Green.
 *  	: unsigned char - Blue.
 */
	STDMETHOD_(void,StartFadeIn)(int,unsigned char,unsigned char,unsigned char) PURE;
/*** StartFadeOut - Gradually transition to a solid color.
 *  	: int - Time in milliseconds.
 *  	: unsigned char - Red.
 *  	: unsigned char - Green.
 *  	: unsigned char - Blue.
 */
	STDMETHOD_(void,StartFadeOut)(int,unsigned char,unsigned char,unsigned char) PURE;
	/* [120] */
/*** GrantPsiPower - Give a psi ability to a player.
 *  	= long - Returns 0.
 *  	: const object & - Recipient.
 *  	: int - Psi power.
 *  	@ IShockPlayer::AddPsiPower(obj,psi)
 */
	STDMETHOD(GrantPsiPower)(const object &,int) PURE;
/*** ResearchConsume - Attempt to use an object in the current research process.
 *  	= Bool - True if the object was used.
 *  	: const object & - Object to use.
 */
	STDMETHOD_(Bool,ResearchConsume)(const object &) PURE;
/*** PlayerMode - Set the player mode with side-effects.
 *  	= long - Returns 0.
 *  	: int - Mode.
 */
	STDMETHOD(PlayerMode)(int) PURE;
/*** EndGame - Stop playing the game.
 *  	= long - Returns 0.
 */
	STDMETHOD(EndGame)(void) PURE;
	/* [130] */
/*** AllowDeath - Return whether the player dying should end the game. Checks for the config variable "undead".
 *  	= Bool - True if the game should not end.
 */
	STDMETHOD_(Bool,AllowDeath)(void) PURE;
/*** AddAlarm - Set the alarm timeout.
 *  	= long - Returns 0.
 *  	: int - The alarm will expire in this many milliseconds. Overrides any previously set alarm.
 */
	STDMETHOD(AddAlarm)(int) PURE;
/*** RemoveAlarm - Immediately cancel the security alarm.
 *  	= long - Returns 0.
 */
	STDMETHOD(RemoveAlarm)(void) PURE;
/*** GetHazardResistance - Get the damage multiplier for the endurance level.
 *  	= float - Amount to scale the damage.
 *  	: int - Endurance stat.
 */
	STDMETHOD_(float,GetHazardResistance)(int) PURE;
	/* [140] */
/*** GetBurnDmg - Get the amount of damage done by a psi overload.
 *  	= int - Hit points to damage the player by.
 */
	STDMETHOD_(int,GetBurnDmg)(void) PURE;
/*** PlayerGun - Get the gun being wielded by the player.
 *  	= object - Current weapon. Aggregate return.
 *  	@ IPlayerGun::Get()
 */
	STDMETHOD_(object*,PlayerGun)(object &) PURE;
/*** IsPsiActive - Check if a psi power is being used.
 *  	= Bool - True if active.
 *  	: int - Psi power.
 *  	@ IPlayerPsi::IsActive(psi)
 */
	STDMETHOD_(Bool,IsPsiActive)(int) PURE;
/*** PsiRadarScan - Do a pass of the psi radar.
 *  	= long - Returns 0.
 */
	STDMETHOD(PsiRadarScan)(void) PURE;
	/* [150] */
/*** PseudoProjectile - Create an object at a distance from another object.
 *  	= object - Emitted object. Aggregate return.
 *  	: const object & - Firer.
 *  	: const object & - Projectile archetype.
 */
	STDMETHOD_(object*,PseudoProjectile)(object &,const object &,const object &) PURE;
/*** WearArmor - Set or clear the armor.
 *  	= long - Returns 0.
 *  	: const object & - The armor to use, or 0 for none.
 */
	STDMETHOD(WearArmor)(const object &) PURE;
/*** SetModify - Change the modification state of a gun.
 *  	= long - Returns 0.
 *  	: const object & - The object to modify.
 *  	: int - Modification state.
 */
	STDMETHOD(SetModify)(const object &,int) PURE;
/*** Censored - Return whether blood should not be shown. Checks the config variable "menschveracht".
 *  	= Bool - True if the game is censored.
 */
	STDMETHOD_(Bool,Censored)(void) PURE;
	/* [160] */
/*** DebriefMode - Switch to the debriefing screen.
 *  	= long - Returns 0.
 *  	: int - Mission number.
 */
	STDMETHOD(DebriefMode)(int) PURE;
/*** TlucTextAdd - Display a string in an overlay at the center of the screen.
 *  	= long - Returns 0.
 *  	: const char * - String name.
 *  	: const char * - Resource name.
 *  	: int - A number that is appended to the end of the string name.
 */
	STDMETHOD(TlucTextAdd)(const char *,const char *,int) PURE;
/*** Mouse - Change the mouse mode.
 *  	= long - Returns 0.
 *  	: Bool - Activate mouse mode.
 *  	: Bool - Drop the cursor object.
 */
	STDMETHOD(Mouse)(Bool,Bool) PURE;
/*** RefreshInv - Update the state of the player's inventory.
 *  	= long - Returns 0.
 */
	STDMETHOD(RefreshInv)(void) PURE;
	/* [170] */
/*** TreasureTable - Adds random objects to a container. Make sure that guaranteed loot is available.
 *  	= long - Returns 0.
 *  	: const object & - The loot object
 */
	STDMETHOD(TreasureTable)(const object &) PURE;
/*** OverlayGetObj - Get the object associated with an overlay.
 *  	= object - The overlay object. Aggregate return.
 */
	STDMETHOD_(object*,OverlayGetObj)(object &) PURE;
/*** VaporizeInv - Destroy (almost) all objects in the player's inventory. Saves objects in slot 10 and the "Magic Ball".
 *  	= long - Returns 0.
 */
	STDMETHOD(VaporizeInv)(void) PURE;
/*** ShutoffPsi - Deactivate all psi powers.
 *  	= long - Returns 0 on success.
 *  	@ IPlayerPsi::Deactivate()
 */
	STDMETHOD(ShutoffPsi)(void) PURE;
	/* [180] */
/*** SetQBHacked - Set the value of a quest variable. Handles variable names that begin with "note" specially.
 *  	= long - Returns 0 on success.
 *  	: const cScrStr & - Quest variable name.
 *  	: int - The value of the variable.
 *  	@ IQuestData::Set(name,val) or IQuestData::Create(name,val,campaign)
 */
	STDMETHOD(SetQBHacked)(const cScrStr &,int) PURE;
/*** GetPlayerMaxPsiPoints - Return the maximum psi points the player can have.
 *  	= int - The maximum psi points.
 *  	@ IPlayerPsi::GetMaxPoints()
 */
	STDMETHOD_(int,GetPlayerMaxPsiPoints)(void) PURE;
/*** SetLogTime - Mark the time that a log is read.
 *  	= long - Returns 0.
 *  	: int - Deck level.
 *  	: int - Type of log.
 *  	: int - Log number.
 */
	STDMETHOD(SetLogTime)(int,int,int) PURE;
/*** AddTranslatableTextInt - Display a string with a replaceable parameter. Identical to AddTranslatableTextIndexInt with the index -1.
 *  	= long - Returns 0.
 *  	: const char * - String name.
 *  	: const char * - Resource name.
 *  	: const object & - Player.
 *  	: int - Parameter value.
 *  	: int - Time in milliseconds.
 *  	@ AddTranslatableTextIndexInt(name,res,player,-1,parm,time)
 */
	STDMETHOD(AddTranslatableTextInt)(const char *,const char *,const object &,int,int) PURE;
	/* [190] */
/*** ZeroControls - Stops the player's movement.
 *  	= long - Returns 0.
 *  	: const object & - Player object.
 *  	: Bool - Poll keys if true.
 */
	STDMETHOD(ZeroControls)(const object &,int) PURE;
/*** SetSelectedPsiPower - Set the current psi power.
 *  	= long - Returns 0.
 *  	: int - Psi power.
 *  	@ IPlayerPsi::Select(psi)
 */
	STDMETHOD(SetSelectedPsiPower)(int) PURE;
/*** ValidGun - Check if an object is a gun.
 *  	= Bool - True if the object has a gun state, is not a melee weapon, and is not the psi amp.
 *  	: const object & - Object to check.
 */
	STDMETHOD_(Bool,ValidGun)(const object &) PURE;
/*** AddTranslatableTextIndexInt - Display an indexed string with a replaceable parameter.
 *  	= long - Returns 0.
 *  	: const char * - String name.
 *  	: const char * - Resource name.
 *  	: const object & - Player.
 *  	: int - Number that will be appended to the end of the string name. Use just the name if -1.
 *  	: int - Parameter value.
 *  	: int - Time in milliseconds.
 */
	STDMETHOD(AddTranslatableTextIndexInt)(const char *,const char *,const object &,int,int,int) PURE;
	/* [1A0] */
/*** IsAlarmActive - Check if the security alarm is active.
 *  	= Bool - Returns true if there is an alarm.
 */
	STDMETHOD_(Bool,IsAlarmActive)(void) PURE;
/*** SlayAllByName - Slay all objects that descend from an archetype.
 *  	= long - Returns 0 on success.
 *  	: const char * - Archetype name.
 */
	STDMETHOD(SlayAllByName)(const char *) PURE;
/*** NoMove - Prevents or allow the player to move. Turning and free-look are still allowed.
 *  	= long - Returns 0.
 *  	: Bool - Freeze or unfreeze the player.
 */
	STDMETHOD(NoMove)(Bool) PURE;
/*** PlayerModeSimple - Just change the player mode.
 *  	= long - Returns 0.
 *  	: int - Mode. 7=Dead, 2=Swimming?, 3=Climbing?, 1=Running?
 */
	STDMETHOD(PlayerModeSimple)(int) PURE;
	/* [1B0] */
/*** UpdateMovingTerrainVelocity - Manually adjust the speed of moving terrain.
 *  	= long - Returns 0.
 *  	: object - Moving terrain object.
 *  	: object - The TerrPt to move to.
 *  	: float - New velocity.
 */
	STDMETHOD(UpdateMovingTerrainVelocity)(object,object,float) PURE;
/*** MouseCursor - Check if the cursor is on-screen.
 *  	= Bool - Returns true if visible.
 */
	STDMETHOD_(Bool,MouseCursor)(void) PURE;
/*** ConfigIsDefined - Test if a config variable has been set.
 *  	= Bool - True if the variable has been set.
 *  	: const char * - The config variable to test for.
 */
	STDMETHOD_(Bool,ConfigIsDefined)(const char *) PURE;
/*** ConfigGetInt - Return the value of a config variable interpreted as an integer.
 *  	= Bool - Returns true on success.
 *  	: const char * - The config variable to retrieve.
 *  	: int & - Address of a variable that will recieve the value.
 */
	STDMETHOD_(Bool,ConfigGetInt)(const char *,int &) PURE;
/*** TechHacking - Show hack UI. Obsolete. Use HRM instead.
 *  	= long - Returns 0.
 *  	: const object & - Hackable object.
 */
	STDMETHOD(TechHacking)(const object &) PURE;
/*** LevelTransportTrap - Change the map from an object property. Not used.
 *  	= long - Returns 0.
 *  	: const char * - Mission name.
 *  	: const object & - Reference object.
 *  	: uint - Flags.
 */
	STDMETHOD(LevelTransport)(const char *,object &,uint) PURE;
/*** SpewLockData - Show access message for a lock.
 *  	= long - Returns 0.
 *  	: const object & - Locked object.
 *  	: Bool - True if the lock was used.
 */
	STDMETHOD(SpewLockData)(const object &,Bool) PURE;
#endif

#endif
};
DEFINE_IIDSTRUCT(IShockGameSrv,IID_IShockGameScriptService);

DECLARE_GUID(IShockObjScriptService);
interface IShockObjSrv : IScriptServiceBase
{
#if (_DARKGAME == 3) || (_SHOCKINTERFACES == 1)
/*** FindScriptDonor - Get the object from which a particular script is inherited from.
 *  	= int - The inherited object ID that has the script.
 *  	: int - Descendant object ID.
 *  	: cScrStr - Name of the script to look for. Passed by value. Method will call IMalloc::Free.
 */
	STDMETHOD_(int,FindScriptDonor)(int,cScrStr) PURE;
#endif
};
DEFINE_IIDSTRUCT(IShockObjSrv,IID_IShockObjScriptService);

DECLARE_GUID(IShockPsiScriptService);
interface IShockPsiSrv : IScriptServiceBase
{
#if (_DARKGAME == 3) || (_SHOCKINTERFACES == 1)
/*** OnDeactivate - Stop using a psi power.
 *  	= long - Returns 0.
 *  	: ePsiPowers - Psi power.
 *  	@ IPlayerPsi::OnDeactivate(psi)
 */
	STDMETHOD(OnDeactivate)(ePsiPowers) PURE;
/*** GetActiveTime - Get how long a psi power has been active.
 *  	= ulong - Time in milliseconds.
 *  	: ePsiPowers - Psi power.
 */
	STDMETHOD_(ulong,GetActiveTime)(ePsiPowers) PURE;
#if (_DARKGAME != 1)
/*** IsOverloaded - Check if a psi power went past its maximum activation level.
 *  	= Bool - True if overloaded.
 *  	: ePsiPowers - Psi power.
 */
	STDMETHOD_(Bool,IsOverloaded)(ePsiPowers) PURE;
#endif
#endif
};
DEFINE_IIDSTRUCT(IShockPsiSrv,IID_IShockPsiScriptService);

DECLARE_GUID(IShockAIScriptService);
interface IShockAISrv : IScriptServiceBase
{
#if (_DARKGAME == 3) || (_SHOCKINTERFACES == 1)
/*** Stun - Interrupt an AI temporarily.
 *  	= Bool - True if successful.
 *  	: object - The AI.
 *  	: cScrStr - Tags. Passed by value. Method will call IMalloc::Free.
 *  	: cScrStr - Motion tags. Passed by value. Method will call IMalloc::Free.
 *  	: float - Time in seconds.
 */
	STDMETHOD_(Bool,Stun)(object,cScrStr,cScrStr,float) PURE;
/*** IsStunned - Is an AI unable to move?
 *  	= Bool - True if the AI is immobile.
 *  	: object - The AI.
 */
	STDMETHOD_(Bool,IsStunned)(object) PURE;
/*** UnStun - Restore the AI state.
 *  	= Bool - True if successful.
 *  	: object - The AI.
 */
	STDMETHOD_(Bool,UnStun)(object) PURE;
/*** Freeze - Make an AI immobile.
 *  	= Bool - True if successful.
 *  	: object - The AI.
 *  	: float - Time in seconds.
 *  	@ IAI::Freeze(time)
 */
	STDMETHOD_(Bool,Freeze)(object,float) PURE;
/*** IsFrozen - Not used.
 *  	= Bool - True if the AI is frozen.
 *  	: object - The AI.
 */
	STDMETHOD_(Bool,IsFrozen)(object) PURE;
/*** UnFreeze - Let an AI move again.
 *  	= Bool - True if successful.
 *  	: object - The AI.
 *  	@ IAI::Unfreeze()
 */
	STDMETHOD_(Bool,UnFreeze)(object) PURE;
/*** NotifyEnterTripwire - Tell an AI that it is approaching a door.
 *  	: object - The AI.
 *  	: object - The door.
 *  	@ IAI::NotifyTripwire(obj,1)
 */
	STDMETHOD_(void,NotifyEnterTripwire)(object,object) PURE;
/*** NotifyExitTripwire - Tell an AI that it is leaving the vicinity of a door.
 *  	: object - The AI.
 *  	: object - The door.
 *  	@ IAI::NotifyTripwire(obj,0)
 */
	STDMETHOD_(void,NotifyExitTripwire)(object,object) PURE;
/*** ObjectLocked - Test if an object is locked. Ignores links.
 *  	= Bool - The value of the Locked property.
 *  	: object - The object to test.
 */
	STDMETHOD_(int,ObjectLocked)(object) PURE;
/*** ValidateSpawn - Check if a creature was spawned in a valid position. For debugging only.
 *  	: object - Spawned object. Must already exist.
 *  	: object - The creator.
 */
	STDMETHOD_(void,ValidateSpawn)(object,object) PURE;
#endif
};
DEFINE_IIDSTRUCT(IShockAISrv,IID_IShockAIScriptService);

DECLARE_GUID(IShockWeaponScriptService);
interface IShockWeaponSrv : IScriptServiceBase
{
#if (_DARKGAME == 3) || (_SHOCKINTERFACES == 1)
/*** SetWeaponModel - Change the current weapon.
 *  	: const object & - The weapon.
 *  	@ IShockPlayer::SetWeaponModel(obj)
 */
	STDMETHOD_(void,SetWeaponModel)(const object &) PURE;
/*** GetWeaponModel - Get the currently active weapon.
 *  	= object - The weapon. Aggregate return.
 *  	@ IWeaponRelation::Query(player,0) or IPlayerGun::Get()
 */
	STDMETHOD_(object*,GetWeaponModel)(object &) PURE;
/*** TargetScan - Find an object in the path of another object.
 *  	= object - The target object. Aggregate return.
 *  	: object - Object to scan from.
 */
	STDMETHOD_(object*,TargetScan)(object &,object) PURE;
/*** Home - Turn an object to face another object.
 *  	: object - The object to turn.
 *  	: object - The target object.
 */
	STDMETHOD_(void,Home)(object,object) PURE;
/*** DestroyMelee - Stop using a melee weapon.
 *  	: const object & - The weapon.
 */
	STDMETHOD_(void,DestroyMelee)(const object &) PURE;
#endif
};
DEFINE_IIDSTRUCT(IShockWeaponSrv,IID_IShockWeaponScriptService);

DECLARE_GUID(ISoundScriptService);
#if (_DARKGAME != 1)
#define SOUND_NET  ,eSoundNetwork
#else
#define SOUND_NET
#endif
interface ISoundScrSrv : IScriptServiceBase
{
/*** PlayAtLocation - Play a schema at a specific location.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: const cScrStr & - The schema tags.
 *  	: const cScrVec & - The location the schema will originate from.
 *  	: eSoundSpecial - Loop option.
 *  	: eSoundNetwork - Network option.
 */
	STDMETHOD_(true_bool*,PlayAtLocation)(true_bool &,object,const cScrStr &,const cScrVec &,eSoundSpecial SOUND_NET) PURE;
/*** PlayAtObject - Play a schema at the location of an object.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: const cScrStr & - The schema tags.
 *  	: object - The object at which location the schema will be played.
 *  	: eSoundSpecial - Loop option.
 *  	: eSoundNetwork - Network option.
 */
	STDMETHOD_(true_bool*,PlayAtObject)(true_bool &,object,const cScrStr &,object,eSoundSpecial SOUND_NET) PURE;
/*** Play - Play a schema at the location of this object.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: const cScrStr & - The schema tags.
 *  	: eSoundSpecial - Loop option.
 *  	: eSoundNetwork - Network option.
 */
	STDMETHOD_(true_bool*,Play)(true_bool &,object,const cScrStr &,eSoundSpecial SOUND_NET) PURE;
/*** PlayAmbient - Play an ambient schema.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: const cScrStr & - The schema tags.
 *  	: eSoundSpecial - Loop option.
 *  	: eSoundNetwork - Network option.
 */
	STDMETHOD_(true_bool*,PlayAmbient)(true_bool &,object,const cScrStr &,eSoundSpecial SOUND_NET) PURE;
/*** PlaySchemaAtLocation - Play a schema object at a specific location.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: object - The schema.
 *  	: const cScrVec & - The location the schema will originate from.
 *  	: eSoundNetwork - Network option.
 */
	STDMETHOD_(true_bool*,PlaySchemaAtLocation)(true_bool &,object,object,const cScrVec & SOUND_NET) PURE;
/*** PlaySchemaAtObject - Play a schema object at the location of an object.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: object - The schema.
 *  	: object - The object at which location the schema will be played.
 *  	: eSoundNetwork - Network option.
 */
	STDMETHOD_(true_bool*,PlaySchemaAtObject)(true_bool &,object,object,object SOUND_NET) PURE;
/*** PlaySchema - Play a schema object at the location of this object.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: object - The schema.
 *  	: eSoundNetwork - Network option.
 */
	STDMETHOD_(true_bool*,PlaySchema)(true_bool &,object,object SOUND_NET) PURE;
/*** PlaySchemaAmbient - Play an ambient schema object.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: object - The schema.
 *  	: eSoundNetwork - Network option.
 */
	STDMETHOD_(true_bool*,PlaySchemaAmbient)(true_bool &,object,object SOUND_NET) PURE;
/*** PlayEnvSchema - Play an environmental schema.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: const cScrStr & - The schema tags.
 *  	: object - The source object.
 *  	: object - Second source object.
 *  	: eEnvSoundLoc - Where the schema will be played.
 *  	: eSoundNetwork - Network option.
 */
	STDMETHOD_(true_bool*,PlayEnvSchema)(true_bool &,object,const cScrStr &,object,object,eEnvSoundLoc SOUND_NET) PURE;
/*** PlayVoiceOver - Play a voice-over schema.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: object - The schema.
 *  	@ IVoiceOverSys::Play(schema)
 */
	STDMETHOD_(true_bool*,PlayVoiceOver)(true_bool &,object,object) PURE;
/*** Halt - Stop playing a schema.
 *  	= int - The number of schemas halted.
 *  	: object - The source object.
 *  	: const cScrStr & - The schema name. Stops all schemas if blank.
 *  	: object - The host object.
 */
	STDMETHOD_(int,Halt)(object,const cScrStr &,object) PURE;
/*** HaltSchema - Stop playing a schema.
 *  	= true_bool - Success.
 *  	: object - The source object.
 *  	: const cScrStr & - The schema tags.
 *  	: object - The host object.
 */
	STDMETHOD_(true_bool*,HaltSchema)(true_bool &,object,const cScrStr &,object) PURE;
/*** HaltSpeech - Prevent an AI from speaking.
 *  	= long - Returns 0.
 *  	: object - The AI.
 */
	STDMETHOD(HaltSpeech)(object) PURE;
/*** PreLoad - Read the waveform data for a schema before having to play it.
 *  	= true_bool - Success.
 *  	: object - The host object.
 *  	: const cScrStr & - The schema tags.
 */
	STDMETHOD_(true_bool*,PreLoad)(true_bool &,const cScrStr &) PURE;
};
#undef SOUND_NET
DEFINE_IIDSTRUCT(ISoundScrSrv,IID_ISoundScriptService);

enum eWeaponType
{
	kWeaponSword,
	kWeaponBlackjack
};
DECLARE_GUID(IWeaponScriptService);
interface IWeaponSrv : IScriptServiceBase
{
/*** Equip - Select an object as the current weapon.
 *  	= Bool - True on success.
 *  	: object - The weapon.
 *  	: eWeaponType - The type of weapon.
 */
	STDMETHOD_(Bool,Equip)(object,eWeaponType) PURE;
/*** UnEquip - Clear the current weapon, if selected.
 *  	= Bool - True on success.
 *  	: object - The weapon.
 */
	STDMETHOD_(Bool,UnEquip)(object) PURE;
/*** IsEquipped - Check if a particular object is the current weapon.
 *  	= Bool - True if the object is equipped.
 *  	: object - The host object.
 *  	: object - The weapon.
 */
	STDMETHOD_(Bool,IsEquipped)(object,object) PURE;
/*** StartAttack - Begin swinging the weapon.
 *  	= Bool - Returns true.
 *  	: object - The host object.
 *  	: object - The weapon.
 */
	STDMETHOD_(Bool,StartAttack)(object,object) PURE;
/*** FinishAttack - Stop swinging the weapon.
 *  	= Bool - Returns true.
 *  	: object - The host object.
 *  	: object - The weapon.
 */
	STDMETHOD_(Bool,FinishAttack)(object,object) PURE;
};
DEFINE_IIDSTRUCT(IWeaponSrv,IID_IWeaponScriptService);

#ifdef _NEWDARK
interface IDarkOverlayHandler
{
/*** DrawHUD - Called when the handler can draw HUD elements.
 */
	STDMETHOD_(void,DrawHUD)(void) PURE;
/*** DrawTOverlay - Called when the handler can draw transparent overlay elements.
 */
	STDMETHOD_(void,DrawTOverlay)(void) PURE;
/*** OnUIEnterMode - Called when initializing UI components and changing screen modes.
 */
	STDMETHOD_(void,OnUIEnterMode)(void) PURE;
};
enum eStyleColorKind
{
	kStyleColorFG,
	kStyleColorBG,
	kStyleColorText,
	kStyleColorHilite,
	kStyleColorDim,
	kStyleColorFG2,
	kStyleColorBG2,
	kStyleColorBorder,
	kStyleColorWhite,
	kStyleColorBlack,
	kStyleColorXOR,
	kStyleColorBevelLight,
	kStyleColorBevelDark
};
DECLARE_GUID(IDarkOverlayScriptService);
interface IDarkOverlaySrv : IScriptServiceBase
{
/*** SetHandler - Register a handler object to draw custom overlays. Only one custom handler can be set at a time.
 *  	: IDarkOverlayHandler - Pointer to an overlay handler instance. Pass NULL to clear the handler.
 */
	STDMETHOD_(void,SetHandler)(IDarkOverlayHandler *) PURE;
/*** GetBitmap - Load a bitmap file.
 *  	= int - Returns a handle to the loaded bitmap, or -1.
 *  	: const char * - The name of the bitmap file.
 *  	: const char * - Resource path to look for the file in. Such as "iface".
 */
	STDMETHOD_(int,GetBitmap)(const char *,const char *) PURE;
/*** FlushBitmap - Release a bitmap.
 *  	: int - The bitmap handle.
 */
	STDMETHOD_(void,FlushBitmap)(int) PURE;
/*** GetBitmapSize - Gets the size of a bitmap.
 *  	: int - The bitmap handle.
 *  	: int & - The width of the bitmap.
 *  	: int & - The height of the bitmap.
 */
	STDMETHOD_(void,GetBitmapSize)(int,int &,int &) PURE;
/*** WorldToScreen - Translate a 3D point in the world to screen coordinates. Only valid while drawing an overlay.
 *  	= Bool - Returns false if the point is offscreen.
 *  	: const cScrVec & - A location in the world.
 *  	: int & - X coordinate of the point on the screen.
 *  	: int & - Y coordinate of the point on the screen.
 */
	STDMETHOD_(Bool,WorldToScreen)(const cScrVec &,int &,int &) PURE;
/*** GetObjectScreenBounds - Get the rectange that surrounds an object as it appears onscreen.
 *  	= Bool - Returns false if the object is not visible.
 *  	: const object & - The object.
 *  	: int & - X coordinate of the left edge.
 *  	: int & - Y coordinate of the top edge.
 *  	: int & - X coordinate of the right edge.
 *  	: int & - Y coordinate of the bottom edge.
 */
	STDMETHOD_(Bool,GetObjectScreenBounds)(const object &,int &,int &,int &,int &) PURE;
/*** CreateTOverlayItem - Create a new user-drawn UI overlay.
 *  	= int - A handle to the overlay, or -1.
 *  	: int - X coordinate of the left edge of the overlay.
 *  	: int - Y coordinate of the top edge of the overlay.
 *  	: int - Width of the overlay.
 *  	: int - Height of the overlay.
 *  	: int - Opacity level, 0..255
 *  	: Bool - True if the background should be transparent.
 */
	STDMETHOD_(int,CreateTOverlayItem)(int,int,int,int,int,Bool) PURE;
/*** CreateTOverlayItemFromBitmap - Use a bitmap as a UI overlay.
 *  	= int - A handle to the overlay, or -1.
 *  	: int - X coordinate of the left edge of the overlay.
 *  	: int - Y coordinate of the top edge of the overlay.
 *  	: int - Opacity level, 0..255
 *  	: int - The bitmap handle.
 *  	: Bool - True if the background should be transparent.
 */
	STDMETHOD_(int,CreateTOverlayItemFromBitmap)(int,int,int,int,Bool) PURE;
/*** DestroyTOverlayItem - Releases the memory used by an overlay.
 *  	: int - The overlay handle.
 */
	STDMETHOD_(void,DestroyTOverlayItem)(int) PURE;
/*** UpdateTOverlayAlpha - Change the opacity of an overlay.
 *  	: int - The overlay handle.
 *  	: int - Opacity of the overlay.
 */
	STDMETHOD_(void,UpdateTOverlayAlpha)(int,int) PURE;
/*** UpdateTOverlayPosition - Set the position of an overlay.
 *  	: int - The overlay handle.
 *  	: int - X coordinate of the left edge.
 *  	: int - Y coordinate of the top edge.
 */
	STDMETHOD_(void,UpdateTOverlayPosition)(int,int,int) PURE;
/*** UpdateTOverlaySize - Change the size of an overlay.
 *  	: int - The overlay handle.
 *  	: int - Width of the overlay.
 *  	: int - Height of the overlay.
 */
	STDMETHOD_(void,UpdateTOverlaySize)(int,int,int) PURE;
/*** DrawBitmap - Display a bitmap in a HUD or overlay.
 *  	: int - The bitmap handle.
 *  	: int - X coordinate of the left edge.
 *  	: int - Y coordinate of the top edge.
 */
	STDMETHOD_(void,DrawBitmap)(int,int,int) PURE;
/*** DrawSubBitmap - Display a cropped region from a bitmap.
 *  	: int - The bitmap handle.
 *  	: int - X coordinate of the left edge where the image is shown.
 *  	: int - Y coordinate of the top edge where the image is shown.
 *  	: int - X offset in the bitmap.
 *  	: int - Y offset in the bitmap.
 *  	: int - Width of the region.
 *  	: int - Height of the region.
 */
	STDMETHOD_(void,DrawSubBitmap)(int,int,int,int,int,int,int) PURE;
/*** SetTextColorFromStyle - Change to a preset color.
 *  	: eStyleColorKind - One of the predefined colors.
 */
	STDMETHOD_(void,SetTextColorFromStyle)(eStyleColorKind) PURE;
/*** SetTextColor - Change the current font color.
 *  	: int - Red. If this is negative, the default color is used.
 *  	: int - Green.
 *  	: int - Blue.
 */
	STDMETHOD_(void,SetTextColor)(int,int,int) PURE;
/*** GetStringSize - Measure the bounding box of a string in the current font.
 *  	: const char * - The text to measure.
 *  	: int - Width of the string.
 *  	: int - Height of the string.
 */
	STDMETHOD_(void,GetStringSize)(const char *,int &,int &) PURE;
/*** DrawString - Display a string in the current font.
 *  	: const char * - The text to show.
 *  	: int - X coordinate.
 *  	: int - Y coordinate.
 */
	STDMETHOD_(void,DrawString)(const char *,int,int) PURE;
/*** DrawLine - Draw a line in the current text color.
 *  	: int - X coordinate of the start of the line.
 *  	: int - Y coordinate of the start of the line.
 *  	: int - X coordinate of the end of the line.
 *  	: int - Y coordinate of the end of the line.
 */
	STDMETHOD_(void,DrawLine)(int,int,int,int) PURE;
/*** FillTOverlay - Fill an overlay with a palette color.
 *  	: int - Color from the standard palette.
 *  	: int - Alpha channel. 0..255
 */
	STDMETHOD_(void,FillTOverlay)(int,int) PURE;
/*** BeginTOverlayUpdate - Call before drawing on an overlay.
 *  	= Bool - Returns true if the user can draw to the overlay.
 *  	: int - The overlay handle.
 */
	STDMETHOD_(Bool,BeginTOverlayUpdate)(int) PURE;
/*** EndTOverlayUpdate - Finish drawing an overlay.
 */
	STDMETHOD_(void,EndTOverlayUpdate)(void) PURE;
/*** DrawTOverlayItem - Display an overlay.
 *  	: int - The overlay handle.
 */
	STDMETHOD_(void,DrawTOverlayItem)(int) PURE;
};
DEFINE_IIDSTRUCT(IDarkOverlaySrv,IID_IDarkOverlayScriptService);

enum eObjRaycast
{
	kObjRaycastNearest,
	kObjRaycastAny,
	kObjRaycastFast
};
DECLARE_GUID(IEngineScriptService);
interface IEngineSrv : IScriptServiceBase
{
/*** ConfigIsDefined - Test if a config variable has been set.
 *  	= Bool - True if the variable has been set.
 *  	: const char * - The config variable to test for.
 */
	STDMETHOD_(Bool,ConfigIsDefined)(const char *) PURE;
/*** ConfigGetInt - Return the value of a config variable interpreted as an integer.
 *  	= Bool - Returns true on success.
 *  	: const char * - The config variable to retrieve.
 *  	: int & - Address of a variable that will recieve the value.
 */
	STDMETHOD_(Bool,ConfigGetInt)(const char *,int &) PURE;
/*** ConfigGetFloat - Return the value of a config variable interpreted as an floating-point number.
 *  	= Bool - Returns true on success.
 *  	: const char * - The config variable to retrieve.
 *  	: float & - Address of a variable that will recieve the value.
 */
	STDMETHOD_(Bool,ConfigGetFloat)(const char *,float &) PURE;
/*** ConfigGetRaw - Return the value of a config variable.
 *  	= Bool - Returns true on success.
 *  	: const char * - The config variable to retrieve.
 *  	: cScrStr & - Address of a variable that will recieve the value.
 */
	STDMETHOD_(Bool,ConfigGetRaw)(const char *,cScrStr &) PURE;
/*** BindingGetFloat - Return the floating-point value of a key-binding variable.
 *  	= float - The value of the variable.
 *  	: const char * - The name of the variable.
 */
	STDMETHOD_(float,BindingGetFloat)(const char *) PURE;
/*** FindFileInPath - Search for a file in the paths defined by a config variable.
 *  	= Bool - Returns true if the file is found.
 *  	: const char * - The config variable set to the path list to search in.
 *  	: const char * - The name of the file.
 *  	: cScrStr & - Address of a variable that is set to the filename.
 */
	STDMETHOD_(Bool,FindFileInPath)(const char *,const char *,cScrStr &) PURE;
/*** IsRunningDX6 - Check the version of DirectX.
 *  	= Bool - True if the older DX6 mode is in use.
 */
	STDMETHOD_(Bool,IsRunningDX6)(void) PURE;
/*** GetCanvasSize - Get the screen size.
 *  	: int & - Width.
 *  	: int & - Height.
 */
	STDMETHOD_(void,GetCanvasSize)(int &,int &) PURE;
/*** GetAspectRatio - Get the screen aspect ratio.
 *  	= float - Width / Height.
 */
	STDMETHOD_(float,GetAspectRatio)(void) PURE;
/*** GetFog - Get the global fog parameters.
 *  	: int & - Red.
 *  	: int & - Green.
 *  	: int & - Blue.
 *  	: float & - Minimum distance.
 */
	STDMETHOD_(void,GetFog)(int &,int &,int &,float &) PURE;
/*** SetFog - Change the global fog parameter.
 *  	: int - Red.
 *  	: int - Green.
 *  	: int - Blue.
 *  	: float - Minimum distance.
 */
	STDMETHOD_(void,SetFog)(int,int,int,float) PURE;
/*** GetFogZone - Get fog parameters for a zone.
 *  	: int - The fog zone. 1..8
 *  	: int & - Red.
 *  	: int & - Green.
 *  	: int & - Blue.
 *  	: float & - Minimum distance.
 */
	STDMETHOD_(void,GetFogZone)(int,int &,int &,int &,float &) PURE;
/*** SetFogZone - Change the fog parameters for a zone.
 *  	: int - The fog zone. 1..8
 *  	: int - Red.
 *  	: int - Green.
 *  	: int - Blue.
 *  	: float - Minimum distance.
 */
	STDMETHOD_(void,SetFogZone)(int,int,int,int,float) PURE;
/*** GetWeather - Get the global weather parameters.
 *  	: int & - Precipitation type.
 *  	: float & - Precipitation frequency.
 *  	: float & - Precipitation speed.
 *  	: float & - Minimum distance.
 *  	: float & - Maximum distance.
 *  	: float & - Alpha.
 *  	: float & - Brightness.
 *  	: float & - Snow jitter.
 *  	: float & - Rain length.
 *  	: float & - Splash frequency.
 *  	: float & - Splash radius.
 *  	: float & - Splash height.
 *  	: float & - Splash time.
 *  	: cScrStr & - Precipitation bitmap.
 *  	: cScrVec & - Wind velocity.
 */
	STDMETHOD_(void,GetWeather)(int &,float &,float &,float &,float &,float &,float &,float &,float &,float &,float &,float &,float &,cScrStr &,cScrVec &) PURE;
/*** SetWeather - Change the global weather parameters.
 *  	: int - Precipitation type.
 *  	: float - Precipitation frequency.
 *  	: float - Precipitation speed.
 *  	: float - Minimum distance.
 *  	: float - Maximum distance.
 *  	: float - Alpha.
 *  	: float - Brightness.
 *  	: float - Snow jitter.
 *  	: float - Rain length.
 *  	: float - Splash frequency.
 *  	: float - Splash radius.
 *  	: float - Splash height.
 *  	: float - Splash time.
 *  	: const char * - Precipitation bitmap.
 *  	: const cScrVec & - Wind velocity.
 */
	STDMETHOD_(void,SetWeather)(int,float,float,float,float,float,float,float,float,float,float,float,float,const char *,const cScrVec &) PURE;
/*** PortalRaycast - Check for terrain blocking two points.
 *  	= Bool - True if terrain was hit.
 *  	: const cScrVec & - Starting location.
 *  	: const cScrVec & - Ending location.
 *  	: cScrVec & - Location of terrain, if hit.
 */
	STDMETHOD_(Bool,PortalRaycast)(const cScrVec &,const cScrVec &,cScrVec &) PURE;
/*** ObjRaycast - Check for an object or terrain between two points.
 *  	= int - Returns 0 if nothing is hit. 1 = terrain, 2 = object, 3 = AI
 *  	: const cScrVec & - Starting location.
 *  	: const cScrVec & - Ending location.
 *  	: cScrVec & - Location where the object or terrain is hit, if any.
 *  	: object & - The object or AI that was hit, if any.
 *  	: eObjRaycast - What to do when there is a hit.
 *  	: Bool - Ignore all AI if true.
 *  	: object - An object to ignore, such as a source object.
 *  	: object - Another object to ignore, such as a destination object.
 */
	STDMETHOD_(int,ObjRaycast)(const cScrVec &,const cScrVec &,cScrVec &,object &,eObjRaycast,Bool,object,object) PURE;
/*** SetEnvMapZone - Change the environment texture map for a zone.
 *  	: int - Environment zone ID. (0 - 63)
 *  	: const char * - Name of the new texture, or NULL.
 */
	STDMETHOD_(void,SetEnvMapZone)(int,const char *) PURE;
};
DEFINE_IIDSTRUCT(IEngineSrv,IID_IEngineScriptService);

enum eShockCursorMode
{
	kSCM_Normal,
	kSCM_DragObj,
	kSCM_UseObj,
	kSCM_Look,
	kSCM_Psi,
	kSCM_Split
};
interface IShockOverlayHandler : IDarkOverlayHandler
{
/*** CanEnableElement - Query the handler if an overlay panel should be displayed.
 *  	= Bool - False if the overlay should be hidden.
 *  	: int - ID of the overlay panel.
 */
	STDMETHOD_(Bool,CanEnableElement)(int) PURE;
/*** IsMouseOver - Notify the handler of mouse movement.
 *  	= Bool - True if the cursor is over a clickable UI element.
 *  	: int - X coordinate of the mouse cursor.
 *  	: int - Y coordinate of the mouse cursor.
 */
	STDMETHOD_(Bool,IsMouseOver)(int,int) PURE;
/*** MouseClick - Notify the handler of a mouse click.
 *  	= Bool - Returns true if the click was handled.
 *  	: int - X coordinate of the mouse cursor.
 *  	: int - Y coordinate of the mouse cursor.
 */
	STDMETHOD_(Bool,MouseClick)(int,int) PURE;
/*** MouseDblClick - Notify the handler of a double-click.
 *  	= Bool - Returns true if the click was handled.
 *  	: int - X coordinate of the mouse cursor.
 *  	: int - Y coordinate of the mouse cursor.
 */
	STDMETHOD_(Bool,MouseDblClick)(int,int) PURE;
/*** MouseDragDrop - Notify the handler of a mouse drag event.
 *  	= Bool - Returns true if the click was handled.
 *  	: int - X coordinate of the mouse cursor.
 *  	: int - Y coordinate of the mouse cursor.
 *  	: Bool - Set to true on the first drag event, then false on subsequent events until the mouse button is released.
 *  	: eShockCursorMode - The cursor interaction mode.
 */
	STDMETHOD_(Bool,MouseDragDrop)(int,int,Bool,eShockCursorMode) PURE;
};
DECLARE_GUID(IShockOverlayScriptService);
interface IShockOverlaySrv : IScriptServiceBase
{
/*** SetHandler - Register a handler object to draw custom overlays. Only one custom handler can be set at a time.
 *  	: IShockOverlayHandler - Pointer to an overlay handler instance. Pass NULL to clear the handler.
 */
	STDMETHOD_(void,SetHandler)(IShockOverlayHandler *) PURE;
/*** SetKeyboardInputCapture - Send keyboard input to the overlay handler.
 *  	: Bool - Set to true to enable capture.
 */
	STDMETHOD_(void,SetKeyboardInputCapture)(Bool) PURE;
/*** GetBitmap - Load a bitmap file.
 *  	= int - Returns a handle to the loaded bitmap, or -1.
 *  	: const char * - The name of the bitmap file.
 *  	: const char * - Resource path to look for the file in. Such as "iface".
 */
	STDMETHOD_(int,GetBitmap)(const char *,const char *) PURE;
/*** FlushBitmap - Release a bitmap.
 *  	: int - The bitmap handle.
 */
	STDMETHOD_(void,FlushBitmap)(int) PURE;
/*** GetBitmapSize - Gets the size of a bitmap.
 *  	: int - The bitmap handle.
 *  	: int & - The width of the bitmap.
 *  	: int & - The height of the bitmap.
 */
	STDMETHOD_(void,GetBitmapSize)(int,int &,int &) PURE;
/*** SetCustomFont - Load a font file.
 *  	= Bool - Returns true on success.
 *  	: int - The custom font style. See IShockOverlaySrv::SetFont.
 *  	: const char * - The name of the font file.
 *  	: const char * - Resource path to look for the file in. Such as "fonts".
 */
	STDMETHOD_(Bool,SetCustomFont)(int,const char *,const char *) PURE;
/*** GetOverlayRect - Get the bounding rectangle of an overlay panel.
 *  	: int - ID of the overlay.
 *  	: int & - X coordinate of the left edge.
 *  	: int & - Y coordinate of the top edge.
 *  	: int & - X coordinate of the right edge.
 *  	: int & - Y coordinate of the bottom edge.
 */
	STDMETHOD_(void,GetOverlayRect)(int,int &,int &,int &,int &) PURE;
/*** GetCursorMode - Get the interaction mode of the mouse cursor.
 *  	= eShockCursorMode - The current cursor mode.
 */
	STDMETHOD_(eShockCursorMode,GetCursorMode)(void) PURE;
/*** ClearCursorMode - Set the cursor mode to normal, cancelling the current mode.
 */
	STDMETHOD_(void,ClearCursorMode)(void) PURE;
/*** SetCursorBitmap - Change the cursor icon.
 *  	= Bool - Returns true on success.
 *  	: const char * - The name of the bitmap file, or NULL to use the default cursor.
 *  	: const char * - Resource path to look for the file in. Such as "iface".
 */
	STDMETHOD_(Bool,SetCursorBitmap)(const char *,const char *) PURE;
/*** SetInterfaceMouseOverObject - Set an object as the focus of the mouse cursor.
 *  	: const object & - The object the cursor is pointing at.
 */
	STDMETHOD_(void,SetInterfaceMouseOverObject)(const object &) PURE;
/*** GetInterfaceFocusObject - Get the object that is the focus of the mouse cursor.
 *  	: object & - A variable reference that will be set to the current cursor object.
 */
	STDMETHOD_(void,GetInterfaceFocusObject)(object &) PURE;
/*** OpenLookPopup - Show the "help" panel.
 *  	: const object & - The object to show information about.
 */
	STDMETHOD_(void,OpenLookPopup)(const object &) PURE;
/*** ToggleLookCursor - Turn on or off the "help" cursor mode. Also called look mode.
 */
	STDMETHOD_(void,ToggleLookCursor)(void) PURE;
/*** StartObjectDragDrop - Begin dragging an object.
 *  	= Bool - Returns true on success.
 *  	: const object & - The object being dragged.
 */
	STDMETHOD_(Bool,StartObjectDragDrop)(const object &) PURE;
/*** PlaySound - Play a UI schema.
 *  	: const char * - A schema name.
 */
	STDMETHOD_(void,PlaySound)(const char *) PURE;
/*** WorldToScreen - Translate a 3D point in the world to screen coordinates. Only valid while drawing an overlay.
 *  	= Bool - Returns false if the point is offscreen.
 *  	: const cScrVec & - A location in the world.
 *  	: int & - X coordinate of the point on the screen.
 *  	: int & - Y coordinate of the point on the screen.
 */
	STDMETHOD_(Bool,WorldToScreen)(const cScrVec &,int &,int &) PURE;
/*** GetObjectScreenBounds - Get the rectange that surrounds an object as it appears onscreen.
 *  	= Bool - Returns false if the object is not visible.
 *  	: const object & - The object.
 *  	: int & - X coordinate of the left edge.
 *  	: int & - Y coordinate of the top edge.
 *  	: int & - X coordinate of the right edge.
 *  	: int & - Y coordinate of the bottom edge.
 */
	STDMETHOD_(Bool,GetObjectScreenBounds)(const object &,int &,int &,int &,int &) PURE;
/*** CreateTOverlayItem - Create a new user-drawn UI overlay.
 *  	= int - A handle to the overlay, or -1.
 *  	: int - X coordinate of the left edge of the overlay.
 *  	: int - Y coordinate of the top edge of the overlay.
 *  	: int - Width of the overlay.
 *  	: int - Height of the overlay.
 *  	: int - Opacity level, 0..255
 *  	: Bool - True if the background should be transparent.
 */
	STDMETHOD_(int,CreateTOverlayItem)(int,int,int,int,int,Bool) PURE;
/*** CreateTOverlayItemFromBitmap - Use a bitmap as a UI overlay.
 *  	= int - A handle to the overlay, or -1.
 *  	: int - X coordinate of the left edge of the overlay.
 *  	: int - Y coordinate of the top edge of the overlay.
 *  	: int - Opacity level, 0..255
 *  	: int - The bitmap handle.
 *  	: Bool - True if the background should be transparent.
 */
	STDMETHOD_(int,CreateTOverlayItemFromBitmap)(int,int,int,int,Bool) PURE;
/*** DestroyTOverlayItem - Releases the memory used by an overlay.
 *  	: int - The overlay handle.
 */
	STDMETHOD_(void,DestroyTOverlayItem)(int) PURE;
/*** UpdateTOverlayAlpha - Change the opacity of an overlay.
 *  	: int - The overlay handle.
 *  	: int - Opacity of the overlay.
 */
	STDMETHOD_(void,UpdateTOverlayAlpha)(int,int) PURE;
/*** UpdateTOverlayPosition - Set the position of an overlay.
 *  	: int - The overlay handle.
 *  	: int - X coordinate of the left edge.
 *  	: int - Y coordinate of the top edge.
 */
	STDMETHOD_(void,UpdateTOverlayPosition)(int,int,int) PURE;
/*** UpdateTOverlaySize - Change the size of an overlay.
 *  	: int - The overlay handle.
 *  	: int - Width of the overlay.
 *  	: int - Height of the overlay.
 */
	STDMETHOD_(void,UpdateTOverlaySize)(int,int,int) PURE;
/*** DrawBitmap - Display a bitmap in a HUD or overlay.
 *  	: int - The bitmap handle.
 *  	: int - X coordinate of the left edge.
 *  	: int - Y coordinate of the top edge.
 */
	STDMETHOD_(void,DrawBitmap)(int,int,int) PURE;
/*** DrawSubBitmap - Display a cropped region from a bitmap.
 *  	: int - The bitmap handle.
 *  	: int - X coordinate of the left edge where the image is shown.
 *  	: int - Y coordinate of the top edge where the image is shown.
 *  	: int - X offset in the bitmap.
 *  	: int - Y offset in the bitmap.
 *  	: int - Width of the region.
 *  	: int - Height of the region.
 */
	STDMETHOD_(void,DrawSubBitmap)(int,int,int,int,int,int,int) PURE;
/*** DrawObjectIcon - Display an object as an icon.
 *  	: const object & - The object to show.
 *  	: int - X coordinate.
 *  	: int - Y coordinate.
 */
	STDMETHOD_(void,DrawObjectIcon)(const object &,int,int) PURE;
/*** SetFont - Change the current font style.
 *  	: int - The font style. 0 = default, 1 = monospace, 2..5 are custom styles which are 0..3 when loaded with SetCustomFont.
 */
	STDMETHOD_(void,SetFont)(int) PURE;
/*** SetTextColor - Change the current font color.
 *  	: int - Red. If this is negative, the default color is used.
 *  	: int - Green.
 *  	: int - Blue.
 */
	STDMETHOD_(void,SetTextColor)(int,int,int) PURE;
/*** GetStringSize - Measure the bounding box of a string in the current font.
 *  	: const char * - The text to measure.
 *  	: int - Width of the string.
 *  	: int - Height of the string.
 */
	STDMETHOD_(void,GetStringSize)(const char *,int &,int &) PURE;
/*** DrawString - Display a string in the current font.
 *  	: const char * - The text to show.
 *  	: int - X coordinate.
 *  	: int - Y coordinate.
 */
	STDMETHOD_(void,DrawString)(const char *,int,int) PURE;
/*** DrawLine - Draw a line in the current text color.
 *  	: int - X coordinate of the start of the line.
 *  	: int - Y coordinate of the start of the line.
 *  	: int - X coordinate of the end of the line.
 *  	: int - Y coordinate of the end of the line.
 */
	STDMETHOD_(void,DrawLine)(int,int,int,int) PURE;
/*** FillTOverlay - Fill an overlay with a palette color.
 *  	: int - Color from the standard palette.
 *  	: int - Alpha channel. 0..255
 */
	STDMETHOD_(void,FillTOverlay)(int,int) PURE;
/*** BeginTOverlayUpdate - Call before drawing on an overlay.
 *  	= Bool - Returns true if the user can draw to the overlay.
 *  	: int - The overlay handle.
 */
	STDMETHOD_(Bool,BeginTOverlayUpdate)(int) PURE;
/*** EndTOverlayUpdate - Finish drawing an overlay.
 */
	STDMETHOD_(void,EndTOverlayUpdate)(void) PURE;
/*** DrawTOverlayItem - Display an overlay.
 *  	: int - The overlay handle.
 */
	STDMETHOD_(void,DrawTOverlayItem)(int) PURE;
};
DEFINE_IIDSTRUCT(IShockOverlaySrv,IID_IShockOverlayScriptService);

DECLARE_GUID(IVersionScriptService);
interface IVersionSrv : IScriptServiceBase
{
/*** GetAppName - Get the name of the host application.
 *  	: Bool - Return a shorter name if true.
 *  	: cScrStr & - The address of a string that is filled with the application name.
 */
	STDMETHOD_(void,GetAppName)(Bool,cScrStr &) PURE;
/*** GetVersion - Get the version number of the host application.
 *  	: int & - Major version number.
 *  	: int & - Minor version number.
 */
	STDMETHOD_(void,GetVersion)(int &,int &) PURE;
/*** IsEditor - Check if the host application is DromEd.
 *  	= int - Returns 0 when called from the game. 1 = DromEd in edit mode, 2 = DromEd in game mode.
 */
	STDMETHOD_(int,IsEditor)(void) PURE;
/*** GetGame - Get the type of the game. Either "dark" or "shock".
 *  	: cScrStr & - A string that will be set to the game type.
 */
	STDMETHOD_(void,GetGame)(cScrStr &) PURE;
/*** GetGamsys - Get the filename of the current gamesys.
 *  	: cScrStr & - A string that will be set to the GAM name.
 */
	STDMETHOD_(void,GetGamsys)(cScrStr &) PURE;
/*** GetMap - Get the filename of the current mission.
 *  	: cScrStr & - A string that will be set to the MIS name.
 */
	STDMETHOD_(void,GetMap)(cScrStr &) PURE;
/*** GetCurrentFM - Get the name of the current fan mission.
 *  	= long - Returns 0 if no FM is active.
 *  	: cScrStr & - A string that will be set to the name of the FM.
 */
	STDMETHOD(GetCurrentFM)(cScrStr &) PURE;
/*** GetCurrentFMPath - Get the directory name of the current fan mission.
 *  	= long - Returns 0 if no FM is active.
 *  	: cScrStr & - A string that will be set to the FM path.
 */
	STDMETHOD(GetCurrentFMPath)(cScrStr &) PURE;
/*** FMizeRelativePath - Add the FM directory to a relative path name.
 *  	: const char * - A file or directory name, relative to the FM path.
 *  	: cScrStr & - A string that will be set to the name joined to the FM path.
 */
	STDMETHOD_(void,FMizeRelativePath)(const char *,cScrStr &) PURE;
/*** FMizePath - Add the FM directory to a relative or absolute path name.
 *  	: const char * - A file or directory name.
 *  	: cScrStr & - A string that will be set to the name joined to the FM path. If the name is an absolute path, it is returned unmodified.
 */
	STDMETHOD_(void,FMizePath)(const char *,cScrStr &) PURE;
};
DEFINE_IIDSTRUCT(IVersionSrv,IID_IVersionScriptService);
#endif

#endif // _LG_SCRSERVICES_H

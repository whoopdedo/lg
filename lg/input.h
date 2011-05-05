/**********************
 * LGS Input
 */

#ifndef _LG_INPUT_H
#define _LG_INPUT_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

struct sInputDeviceInfo
{
	GUID iid;
};

interface IPrimaryInputDevicesSink;

#define INTERFACE IInputDevices
DECLARE_GUID(IInputDevices);
DECLARE_INTERFACE_(IInputDevices,IUnknown)
{
	STDMETHOD(Advise)(THIS_ IPrimaryInputDevicesSink *,ulong *) PURE;
	STDMETHOD(Unadvise)(THIS_ ulong) PURE;
	STDMETHOD_(Bool,GetMouseState)(THIS_ int *,int *,int *) PURE;
	STDMETHOD_(Bool,SetMousePos)(THIS_ int,int) PURE;
};
DEFINE_IIDSTRUCT(IInputDevices,IID_IInputDevices);
#undef INTERFACE

#define INTERFACE IInputDevice
DECLARE_GUID(IInputDevice);
DECLARE_INTERFACE_(IInputDevice,IUnknown)
{
	STDMETHOD(GetInfo)(THIS_ sInputDeviceInfo *) PURE;
};
DEFINE_IIDSTRUCT(IInputDevice,IID_IInputDevice);
#undef INTERFACE

struct uiEvent
{
	Point pos;
	uint type;
	short subtype;
	char data[6];
};

struct intrnl_var_channel
{
	char szValue[32];
	int iType;
	Bool bActive;
	short unknown;
	ulong iContext;
};

struct Region
{
	int x,y;
	Rect *r;
	int z;
	int moving;
	// more stuff
};

typedef int (__cdecl *InputVarHandlerFunc)(const char*,const char*);
typedef int (__cdecl *InputVarAddActiveAgg)(void*,int,char*);

struct IB_var
{
	char szName[32];
	char szValue[64];
	uint iFlags;	// 2 - alias
	InputVarHandlerFunc pfnHandler;
	InputVarAddActiveAgg pfnActiveAgg;
	char szTempVal[32];
};

struct sBindContext
{
	char szPrefix[32];
	ulong iContext;
};

struct sJoyState
{
	long x,y,z;
	long rx,ry,rz;
	long u,v;
	ulong pov[4];
	unsigned char buttons[32];
};

typedef unsigned char (__cdecl *InputHandlerFunc)(uiEvent*,Region*,void*);
typedef int (__cdecl *InputBindFilter)(char*,char*,void*);
typedef void (__cdecl *InputPostBind)(int);
typedef int (__cdecl *MasterAggregationFunc)(intrnl_var_channel**,long,char*);
typedef char* (__cdecl *MasterProcessCallbackFunc)(char*,char*,int);

#define INTERFACE IInputBinder
DECLARE_GUID(IInputBinder);
DECLARE_INTERFACE_(IInputBinder,IUnknown)
{
	STDMETHOD_(char*,Init)(THIS_ IB_var *,char *) PURE;
	STDMETHOD_(char*,Term)(THIS) PURE;
	STDMETHOD_(void,GetHandler)(THIS_ InputHandlerFunc *) PURE;
	STDMETHOD_(void,SetValidEvents)(THIS_ ulong) PURE;
#if (_DARKGAME == 2) || (_DARKGAME == 3)
	STDMETHOD_(ulong,GetValidEvents)(THIS) PURE;
	STDMETHOD_(Bool,Bind)(THIS_ char *,char *) PURE;
	STDMETHOD_(Bool,Unbind)(THIS_ char *) PURE;
	STDMETHOD_(void,QueryBind)(THIS_ char *,char *,long) PURE;
	STDMETHOD_(void,GetVarValue)(THIS_ char *,char *,long) PURE;
#endif
	STDMETHOD_(char*,ProcessCmd)(THIS_ char *) PURE;
	STDMETHOD_(void,TrapBind)(THIS_ char *,InputBindFilter,InputPostBind,void *) PURE;
	STDMETHOD_(char *,Update)(THIS) PURE;
	STDMETHOD_(void,PollAllKeys)(THIS) PURE;
	STDMETHOD_(void,RegisterJoyProcObj)(THIS_ void *) PURE;
#if (_DARKGAME == 2)
	STDMETHOD_(void,LoadBndContexted)(THIS_ char *) PURE;
	STDMETHOD_(void,ContextAssociate)(THIS_ sBindContext *) PURE;
#endif
	STDMETHOD_(char*,LoadBndFile)(THIS_ char *,ulong,char *) PURE;
	STDMETHOD_(char*,SaveBndFile)(THIS_ char *,char *) PURE;
	STDMETHOD_(Bool,VarSet)(THIS_ IB_var *) PURE;
	STDMETHOD_(Bool,VarSetn)(THIS_ IB_var *,long) PURE;
	STDMETHOD_(char*,VarUnset)(THIS_ char * *,Bool) PURE;
	STDMETHOD_(char*,VarUnsetn)(THIS_ char * *,long,Bool) PURE;
	STDMETHOD_(char*,VarUnsetAll)(THIS) PURE;
	STDMETHOD_(Bool,SetContext)(THIS_ ulong,Bool) PURE;
	STDMETHOD_(void,GetContext)(THIS_ ulong *) PURE;
	STDMETHOD_(void,SetMasterAggregation)(THIS_ MasterAggregationFunc) PURE;
	STDMETHOD_(void,SetMasterProcessCallback)(THIS_ MasterProcessCallbackFunc) PURE;
	STDMETHOD_(char*,GetControlFromCmdStart)(THIS_ char *,char *) PURE;
	STDMETHOD_(char*,GetControlFromCmdNext)(THIS_ char *) PURE;
	STDMETHOD_(void,SetResPath)(THIS_ char *) PURE;
	STDMETHOD_(char*,DecomposeControl)(THIS_ char *,char[4][32],long *) PURE;
#if (_DARKGAME == 2) || (_DARKGAME == 3)
	STDMETHOD_(void,Reset)(THIS) PURE;
#endif
};
DEFINE_IIDSTRUCT(IInputBinder,IID_IInputBinder);
#undef INTERFACE

#define INTERFACE IJoystick
DECLARE_GUID(IJoystick);
DECLARE_INTERFACE_(IJoystick,IUnknown)
{
	STDMETHOD(GetInfo)(THIS_ sInputDeviceInfo *) PURE;
	STDMETHOD(GetState)(THIS_ sJoyState *) PURE;
	STDMETHOD(SetAxisRange)(THIS_ int,long,long) PURE;
	STDMETHOD(GetAxisRange)(THIS_ int,long*,long*) PURE;
	STDMETHOD(SetAxisDeadZone)(THIS_ int,ulong) PURE;
	/*
	STDMETHOD_(long,SetCooperativeLevel)(THIS_ int,int) PURE;
	*/
};
DEFINE_IIDSTRUCT(IJoystick,IID_IJoystick);
#undef INTERFACE

#endif // _LG_INPUT_H

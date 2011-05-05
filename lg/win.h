/**********************
 * LGS Windows Host
 */

#ifndef _LG_WIN_H
#define _LG_WIN_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>
#include <lg/graphics.h>

typedef Bool(__stdcall *DialogBoxProc)(HANDLE,uint,uint,ulong);

#define INTERFACE IAppAdviseSink
DECLARE_GUID(IAppAdviseSink);
DECLARE_INTERFACE_(IAppAdviseSink,IUnknown)
{
	STDMETHOD_(short,GetVersion)(THIS) PURE;
	STDMETHOD(OnQueryQuit)(THIS) PURE;
	STDMETHOD_(void,OnQuit)(THIS) PURE;
	STDMETHOD_(void,OnCriticalError)(THIS_ int) PURE;
	STDMETHOD_(void,OnCommand)(THIS_ uint) PURE;
};
DEFINE_IIDSTRUCT(IAppAdviseSink,IID_IAppAdviseSink);
#undef INTERFACE

#define INTERFACE IApplication
DECLARE_GUID(IApplication);
DECLARE_INTERFACE_(IApplication,IUnknown)
{
	STDMETHOD(QueryQuit)(THIS) PURE;
	STDMETHOD_(void,Quit)(THIS) PURE;
	STDMETHOD_(void,Abort)(THIS_ const char*) PURE;
	STDMETHOD_(void,SetCaption)(THIS_ const char*) PURE;
	STDMETHOD_(const char*,GetCaption)(THIS) PURE;
	STDMETHOD_(void,SetDefaultFilePath)(THIS_ const char*) PURE;
	STDMETHOD_(const char*,GetDefaultFilePath)(THIS) PURE;
	STDMETHOD_(const char*,GetFullName)(THIS) PURE;
	STDMETHOD_(const char*,GetPath)(THIS) PURE;
	STDMETHOD_(int,MessageBox)(THIS_ const char*,const char*,int) PURE;
	STDMETHOD(Advise)(THIS_ IAppAdviseSink*,ulong*) PURE;
	STDMETHOD(Unadvise)(THIS_ ulong) PURE;
	STDMETHOD_(void,AppCommand)(THIS_ uint) PURE;
	STDMETHOD_(int,CriticalMessageBox)(THIS_ const char*,const char*,int) PURE;
};
DEFINE_IIDSTRUCT(IApplication,IID_IApplication);
#undef INTERFACE

enum eWinPumpResult
{
	kPumpOk,
	kPumpEmpty,
	kPumpQuit,
	kPumpFail
};
enum eWinPumpDuration
{
	kPumpOne,
	kPumpUntilEmpty,
	kPumpUntilQuit
};

#define INTERFACE IWinAppAdviseSink
DECLARE_GUID(IWinAppAdviseSink);
DECLARE_INTERFACE_(IWinAppAdviseSink,IUnknown)
{
	STDMETHOD_(short,GetVersion)(THIS) PURE;
	STDMETHOD_(Bool,PreTranslateMessage)(THIS_ void*) PURE;
	STDMETHOD_(Bool,OnIdle)(THIS_ long) PURE;
};
DEFINE_IIDSTRUCT(IWinAppAdviseSink,IID_IWinAppAdviseSink);
#undef INTERFACE

#define INTERFACE IWinApp
DECLARE_GUID(IWinApp);
DECLARE_INTERFACE_(IWinApp,IUnknown)
{
	STDMETHOD_(HANDLE,GetMainWnd)(THIS) PURE;
	STDMETHOD_(HANDLE,SetMainWnd)(THIS_ HANDLE) PURE;
	STDMETHOD_(HANDLE,GetInstance)(THIS) PURE;
	STDMETHOD_(HANDLE,GetResourceInstance)(THIS) PURE;
	STDMETHOD_(const char*,GetCommandLine)(THIS) PURE;
	STDMETHOD_(int,GetCommandShow)(THIS) PURE;
	STDMETHOD_(void,SetRegistryKey)(THIS_ const char*) PURE;
	STDMETHOD_(const char*,GetRegistryKey)(THIS) PURE;
	STDMETHOD_(void,SetProfileName)(THIS_ const char*) PURE;
	STDMETHOD_(const char*,GetProfileName)(THIS) PURE;
	STDMETHOD_(void,SetDialogBkColor)(THIS_ ulong,ulong) PURE;
	STDMETHOD_(eWinPumpResult,PumpEvents)(THIS_ int,eWinPumpDuration) PURE;
	STDMETHOD(ModalDialogBox)(THIS_ const char*,DialogBoxProc) PURE;
	STDMETHOD(Advise)(THIS_ IWinAppAdviseSink*,ulong*) PURE;
	STDMETHOD(Unadvise)(THIS_ ulong) PURE;
};
DEFINE_IIDSTRUCT(IWinApp,IID_IWinApp);
#undef INTERFACE

interface IDirectDraw4;
interface IDirectDrawSurface4;

struct sWinDispDevCallbackInfo
{
};
typedef void (__cdecl *WinDispDevCallbackFunc)(sWinDispDevCallbackInfo*);

#define INTERFACE IWinDispDevice
DECLARE_GUID(IWinDisplayDevice);
DECLARE_INTERFACE_(IWinDispDevice,IUnknown)
{
	STDMETHOD_(Bool,ProcessMessage)(THIS_ uint,uint,long,long*) PURE;
	STDMETHOD_(void,GetWidthHeight)(THIS_ uint*,uint*) PURE;
	STDMETHOD_(void,OnTaskSwitch)(THIS_ Bool) PURE;
	STDMETHOD_(int,GetDirectDraw)(THIS_ IDirectDraw4**) PURE;
	STDMETHOD_(void,WaitForMutex)(THIS) PURE;
	STDMETHOD_(void,ReleaseMutex)(THIS) PURE;
	STDMETHOD_(void,CursorBltFromGDIScreen)(THIS_ sGrBitmap*,int,int) PURE;
	STDMETHOD_(void,CursorBltToGDIScreen)(THIS_ sGrBitmap*,int,int) PURE;
	STDMETHOD_(Bool,GetBitmapSurface)(THIS_ sGrBitmap*,IDirectDrawSurface4**) PURE;
	STDMETHOD_(void,AddTaskSwitchCallback)(THIS_ WinDispDevCallbackFunc) PURE;
	STDMETHOD_(void,RemoveTaskSwitchCallback)(THIS_ int) PURE;
};
DEFINE_IIDSTRUCT(IWinDispDevice,IID_IWinDisplayDevice);
#undef INTERFACE

enum eGSCursorEvent {
	kGSCursorShow,
	kGSCursorHide
};

#define INTERFACE IGameShell
DECLARE_GUID(IGameShell);
DECLARE_INTERFACE_(IGameShell,IUnknown)
{
	STDMETHOD_(void,BeginFrame)(THIS) PURE;
	STDMETHOD_(void,EndFrame)(THIS) PURE;
	STDMETHOD(BringToFront)(THIS) PURE;
	virtual int f1() = 0;
	STDMETHOD_(void,PumpEvents)(THIS_ int) PURE;
	STDMETHOD_(int,DisplayLock)(THIS) PURE;
	STDMETHOD_(int,DisplayUnlock)(THIS) PURE;
	STDMETHOD_(void,DisplayFlush)(THIS) PURE;
	STDMETHOD_(unsigned long,GetTimerTick)(THIS) PURE;
	STDMETHOD_(void,SetTimer)(THIS_ unsigned long) PURE;
	STDMETHOD_(Bool,ShowHelp)(THIS_ const char*,uint,ulong) PURE;
	STDMETHOD_(Bool,SetOSCursor)(THIS_ sGrBitmap*,const Point*) PURE;
	STDMETHOD_(Bool,ShowOSCursor)(THIS_ Bool) PURE;
	STDMETHOD_(void,SetCursorCallback)(THIS_ void (__stdcall *)(eGSCursorEvent)) PURE;
	STDMETHOD_(Bool,Exec)(THIS_ const char*) PURE;
	STDMETHOD_(Bool,SetFlags)(THIS_ int) PURE;
	STDMETHOD_(Bool,GetFlags)(THIS_ int*) PURE;
};
DEFINE_IIDSTRUCT(IGameShell,IID_IGameShell);
#undef INTERFACE

#define INTERFACE IWinShellSink
DECLARE_GUID(IGameShellAdviseSink);
DECLARE_INTERFACE_(IWinShellSink,IUnknown)
{
	STDMETHOD_(Bool,PreProcessMessage)(THIS_ uint,uint,long,long*) PURE;
	STDMETHOD_(Bool,PostProcessMessage)(THIS_ uint,uint,long,long*) PURE;
	STDMETHOD_(void,OnTaskSwitch)(THIS_ Bool) PURE;
};
DEFINE_IIDSTRUCT(IWinShellSink,IID_IGameShellAdviseSink);
#undef INTERFACE

#define INTERFACE IWinShell
DECLARE_GUID(IWinShell);
DECLARE_INTERFACE_(IWinShell,IUnknown)
{
	STDMETHOD_(HANDLE,SetCursor)(THIS_ HANDLE) PURE;
	STDMETHOD_(HANDLE,GetCursor)(THIS) PURE;
	STDMETHOD(Advise)(THIS_ IWinShellSink*,int,ulong*) PURE;
	STDMETHOD(Unadvise)(THIS_ ulong) PURE;
};
DEFINE_IIDSTRUCT(IWinShell,IID_IWinShell);
#undef INTERFACE

#endif // _LG_WIN_H

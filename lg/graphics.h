/**********************
 * LGS Graphics interface
 */

#ifndef _LG_GRAPHICS_H
#define _LG_GRAPHICS_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

interface IDeviceBitmap;

enum eDisplayDeviceKind
{
	kDisplayDeviceNone,
	kDisplayDeviceWindow,
	kDisplayDeviceFullScreen,
	kUnknownDisplayDeviceKind = 0xFFFF
};

enum eDisplayDeviceMonitorFlag
{
};

struct sGrSysInfo
{
	Byte vers_high, vers_low;
	Word unknown1;
	Word modes[86];
};

struct sGrModeInfo
{
	Short	mode_num;
	Short	unknown1;
	Word	width;
	Word	height;
	Byte	depth;
	Byte	unknown2;
	Word	unknown3;
};

struct sGrDriverCapabilities
{
	long	unknown1;
	Word	width, height;
	long	unknown2;
	long	unknown3;
	uint	row_size;
};

struct sGrModeInfoEx
{
	int 	mode_num;
	uint	width, height, row_size;
	long	unknown1;
	uint	depth;
	uint	red_mask, green_mask, blue_mask;
	long	unknown2;
	long	unknown3;
};

struct sGrBitmap
{
	Byte *	data;
	Byte	depth;
	Byte	unknown1;
	Short	unknown2;
	Word	width, height, row_size;
	Word unknown3;
};

struct sGrDevBitmapDesc
{
	uint width, height;
	long unknown[8];
};

struct sGrRenderTargets
{
	IDeviceBitmap * buffers[2];
};

#define INTERFACE IDisplayDevice
DECLARE_GUID(IDisplayDevice);
DECLARE_INTERFACE_(IDisplayDevice,IUnknown)
{
	STDMETHOD_(eDisplayDeviceKind,GetKind)(THIS) PURE;
	STDMETHOD_(void,SetKind)(THIS_ eDisplayDeviceKind,int) PURE;
	STDMETHOD_(void,GetInfo)(THIS_ sGrSysInfo *,sGrModeInfo *) PURE;
	STDMETHOD(Open)(THIS_ sGrDriverCapabilities *,int) PURE;
	STDMETHOD(Close)(THIS) PURE;
	STDMETHOD(SetMode)(THIS_ int,int) PURE;
	STDMETHOD_(int,GetMode)(THIS_ sGrModeInfoEx *) PURE;
	STDMETHOD_(Bool,StatHTrace)(THIS) PURE;
	STDMETHOD_(Bool,StatVTrace)(THIS) PURE;
	STDMETHOD_(Bool,SetPalette)(THIS_ uint,uint,const Byte *) PURE;
	STDMETHOD_(Bool,GetPalette)(THIS_ uint,uint,Byte *) PURE;
	STDMETHOD(PageFlip)(THIS) PURE;
	STDMETHOD_(int,Lock)(THIS) PURE;
	STDMETHOD_(int,Unlock)(THIS) PURE;
	STDMETHOD_(void,Flush)(THIS) PURE;
	STDMETHOD_(void,PauseFlush)(THIS_ Bool) PURE;
	STDMETHOD_(Bool,IsFlushingPaused)(THIS) PURE;
	STDMETHOD_(Bool,SetMonitor)(THIS_ void * *,eDisplayDeviceMonitorFlag) PURE;
	STDMETHOD_(int,BreakLock)(THIS) PURE;
	STDMETHOD_(void,RestoreLock)(THIS_ int) PURE;
	STDMETHOD_(Bool,IsLocked)(THIS) PURE;
	STDMETHOD_(void,FlushRect)(THIS_ int,int,int,int) PURE;
	STDMETHOD(CreateBitmap)(THIS_ sGrDevBitmapDesc *,int,IDeviceBitmap * *) PURE;
	STDMETHOD(FindBitmap)(THIS_ const sGrBitmap *,IDeviceBitmap * *) PURE;
	STDMETHOD(GetRenderTargets)(THIS_ sGrRenderTargets *) PURE;
	STDMETHOD_(void,SetKind2)(THIS_ eDisplayDeviceKind,GUID *) PURE;
	STDMETHOD_(void,GetKind2)(THIS_ eDisplayDeviceKind *,int *,GUID * *) PURE;
	STDMETHOD_(Bool,SetGamma)(THIS_ double) PURE;
	STDMETHOD_(Bool,SetFlip)(THIS_ Bool) PURE;
};
DEFINE_IIDSTRUCT(IDisplayDevice,IID_IDisplayDevice);
#undef INTERFACE

#define INTERFACE IDeviceBitmap
DECLARE_GUID(IDeviceBitmap);
DECLARE_INTERFACE_(IDeviceBitmap,IUnknown)
{
	STDMETHOD(SimpleBlt)(THIS_ int,int,IDeviceBitmap *) PURE;
	STDMETHOD_(Bool,IsAvailable)(THIS) PURE;
	STDMETHOD(BeginAccess)(THIS_ sGrBitmap *) PURE;
	STDMETHOD(NotifyCopy)(THIS_ sGrBitmap *) PURE;
	STDMETHOD(EndAccess)(THIS_ sGrBitmap *) PURE;
	STDMETHOD(GetImplementor)(THIS_ IUnknown * *) PURE;
	STDMETHOD_(int,Lock)(THIS) PURE;
	STDMETHOD_(int,Unlock)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IDeviceBitmap,IID_IDeviceBitmap);
#undef INTERFACE

enum eMP1State {
	kMP1Closed,
	kMP1Opened,
	kMP1Playing,
	kMP1Paused
};

#define INTERFACE IMoviePlayer1
DECLARE_GUID(IMoviePlayer1);
DECLARE_INTERFACE_(IMoviePlayer1,IUnknown)
{
	STDMETHOD_(Bool,Open)(THIS_ const char *,int,int,int,int) PURE;
	STDMETHOD_(void,Close)(THIS) PURE;
	STDMETHOD_(Bool,CanPlay)(THIS) PURE;
	STDMETHOD_(Bool,Play)(THIS_ int) PURE;
	STDMETHOD_(Bool,Pause)(THIS) PURE;
	STDMETHOD_(Bool,Stop)(THIS) PURE;
	STDMETHOD_(Bool,GetVolume)(THIS_ int *) PURE;
	STDMETHOD_(Bool,SetVolume)(THIS_ int) PURE;
	STDMETHOD_(eMP1State,GetState)(THIS) PURE;
	STDMETHOD_(void,SetTermKeys)(THIS_ char *) PURE;
};
DEFINE_IIDSTRUCT(IMoviePlayer1,IID_IMoviePlayer1);
#undef INTERFACE

#endif

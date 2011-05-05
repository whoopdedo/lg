/**********************
 * LGS Sound
 */

#ifndef _LG_SOUND_H
#define _LG_SOUND_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#define INTERFACE ICDPlayer
DECLARE_GUID(ICDPlayer);
DECLARE_INTERFACE_(ICDPlayer,IUnknown)
{
	STDMETHOD(Init)(THIS) PURE;
	STDMETHOD(CDPlayTrack)(THIS_ int) PURE;
	STDMETHOD(CDStopPlay)(THIS) PURE;
	STDMETHOD(CDSetBGMTrack)(THIS_ int) PURE;
	STDMETHOD(CDPlayTransition)(THIS_ int,uint) PURE;
	STDMETHOD(Update)(THIS) PURE;
};
DEFINE_IIDSTRUCT(ICDPlayer,IID_ICDPlayer);
#undef INTERFACE

interface ISong;

#define INTERFACE ISongPlayer
DECLARE_GUID(ISongPlayer);
DECLARE_INTERFACE_(ISongPlayer,IUnknown)
{
	STDMETHOD_(Bool,SetSong)(THIS_ ISong*) PURE;
	STDMETHOD_(void,GetSong)(THIS_ ISong**) PURE;
	STDMETHOD_(void,UnloadSong)(THIS) PURE;
	STDMETHOD_(Bool,StartPlaying)(THIS) PURE;
	STDMETHOD_(Bool,StopPlaying)(THIS) PURE;
	STDMETHOD_(Bool,PausePlaying)(THIS) PURE;
	STDMETHOD_(Bool,ResumePlaying)(THIS) PURE;
	STDMETHOD_(void,SetVolume)(THIS_ int) PURE;
	STDMETHOD_(int,GetVolume)(THIS) PURE;
	STDMETHOD_(Bool,SendEvent)(THIS_ char const*, int) PURE;
	STDMETHOD_(void,SetThemed)(THIS_ Bool) PURE;
	STDMETHOD_(Bool,IsThemed)(THIS) PURE;
	STDMETHOD_(Bool,SetTheme)(THIS_ char const*) PURE;
	STDMETHOD_(void,GetMemento)(THIS_ void**, int*) PURE;
	STDMETHOD_(Bool,RestoreMemento)(THIS_ void*, int) PURE;
};
DEFINE_IIDSTRUCT(ISongPlayer,IID_ISongPlayer);
#undef INTERFACE

#define INTERFACE IVoiceOverSys
DECLARE_GUID(IVoiceOverSys);
DECLARE_INTERFACE_(IVoiceOverSys,IUnknown)
{
	STDMETHOD_(int,Play)(THIS_ int) PURE;
	STDMETHOD_(Bool,AlreadyPlayed)(THIS_ int) PURE;
	STDMETHOD(SetAlreadyPlayed)(THIS_ int,Bool) PURE;
	STDMETHOD(SetCombatTest)(THIS_ Bool (__stdcall *)(void)) PURE;
};
DEFINE_IIDSTRUCT(IVoiceOverSys,IID_IVoiceOverSys);
#undef INTERFACE

#endif // _LG_SOUND_H

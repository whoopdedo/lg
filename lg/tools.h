/**********************
 * LGS Script Tools
 */

#ifndef _LG_TOOLS_H
#define _LG_TOOLS_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#include <lg/types.h>

interface IStringProperty;

#define INTERFACE IGameStrings
DECLARE_GUID(IGameStrings);
DECLARE_INTERFACE_(IGameStrings,IUnknown)
{
	// filename, stringname, default, resname
	STDMETHOD_(cAnsiStr*,FetchString)(THIS_ cAnsiStr&,const char*,const char*,const char*,const char*) PURE;
	// Bind a resname to a property
	STDMETHOD(RegisterProp)(THIS_ const char*,IStringProperty*) PURE;
	// object id, resname (as used in RegisterProp)
	STDMETHOD_(cAnsiStr*,FetchObjString)(THIS_ cAnsiStr&,int,const char*) PURE;
	STDMETHOD(DumpProp)(THIS_ const char*) PURE;
	STDMETHOD(LoadProp)(THIS_ const char*) PURE;
	STDMETHOD(StripProp)(THIS_ const char*) PURE;
	STDMETHOD(ModernizeProp)(THIS_ const char*) PURE;
};
DEFINE_IIDSTRUCT(IGameStrings,IID_IGameStrings);
#undef INTERFACE

typedef Bool (__cdecl *IsToGameModeGUIDCallbackFunc)(const GUID *);

#define INTERFACE IGameTools
DECLARE_GUID(IGameTools);
DECLARE_INTERFACE_(IGameTools,IUnknown)
{
	STDMETHOD_(Bool,IsToGameModeGUID)(THIS_ const GUID *) PURE;
	STDMETHOD(SetIsToGameModeGUIDCallback)(THIS_ IsToGameModeGUIDCallbackFunc) PURE;
	STDMETHOD(TeleportObject)(THIS_ int,const mxs_vector*,const mxs_angvec*,int) PURE;
};
DEFINE_IIDSTRUCT(IGameTools,IID_IGameTools);
#undef INTERFACE

#define INTERFACE IStructDescTools
DECLARE_GUID(IStructDescTools);
DECLARE_INTERFACE_(IStructDescTools,IUnknown)
{
	 STDMETHOD_(const sFieldDesc*,GetFieldNamed)(THIS_ const sStructDesc*,const char*) PURE;
	 STDMETHOD(ParseField)(THIS_ const sFieldDesc*,const char*,void*) PURE;
	 STDMETHOD(UnparseField)(THIS_ const sFieldDesc*,const void*,char*,int) PURE;
	 STDMETHOD_(Bool,IsSimple)(THIS_ const sStructDesc*) PURE;
	 STDMETHOD_(Bool,ParseSimple)(THIS_ const sStructDesc*,const char*,void*) PURE;
	 STDMETHOD_(Bool,UnparseSimple)(THIS_ const sStructDesc*,const void*,char*,int) PURE;
	 STDMETHOD_(Bool,ParseFull)(THIS_ const sStructDesc*,const char*,void*) PURE;
	 STDMETHOD_(Bool,UnparseFull)(THIS_ const sStructDesc*,const void*,char*,int) PURE;
	 STDMETHOD(Dump)(THIS_ const sStructDesc*,const void*) PURE;
	 STDMETHOD(SetIntegral)(THIS_ const sFieldDesc*,long,void*) PURE;
	 STDMETHOD(GetIntegral)(THIS_ const sFieldDesc*,const void*,long*) PURE;
	 STDMETHOD_(const sStructDesc*,Lookup)(THIS_ const char*) PURE;
	 STDMETHOD(Register)(THIS_ const sStructDesc*) PURE;
	 STDMETHOD(ClearRegistry)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IStructDescTools,IID_IStructDescTools);
#undef INTERFACE

enum eRecMode
{
	kRecRecord,
	kRecPlay,
	kRecStop,
	kRecPauseRecord,
	kRecPausePlay
};

#define INTERFACE IRecorder
DECLARE_GUID(IRecorder);
DECLARE_INTERFACE_(IRecorder,IUnknown)
{
	STDMETHOD_(eRecMode,GetMode)(THIS) PURE;
	STDMETHOD(StreamAddOrExtract)(THIS_ void*,uint,const char*) PURE;
	STDMETHOD(AddToStream)(THIS_ void*,uint,const char*) PURE;
	STDMETHOD(ExtractFromStream)(THIS_ void*,uint,const char*) PURE;
	STDMETHOD(Pause)(THIS) PURE;
	STDMETHOD(Resume)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IRecorder,IID_IRecorder);
#undef INTERFACE

#endif // _LG_TOOLS_H

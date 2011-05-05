/***********************
 * LGS Editor Interface
 */

#ifndef _LG_EDITOR_H
#define _LG_EDITOR_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>
#include <lg/types.h>

interface IProperty;
interface IObjEditor;
struct sObjEditorDesc;

#define EDITTRAIT_PROPERTY 1
#define EDITTRAIT_LINK 2

enum eEditTraitFlags
{
	kEditTraitHidden = 1
};

struct sEditTraitDesc
{
	int iTraitKind;  // 1 = property, 2 = link
	char szName[16];
	char szLabel[32];
	char szCategory[32];
	ulong Flags;
};

enum eEditTraitCapabilities
{
	kEditTraitCanAdd = 1,
	kEditTraitCanRemove = 2,
	kEditTraitCanEdit = 4,
	kEditTraitCanParse = 8,
	kEditTraitCanUnparse = 16,
	kEditTraitCapAll = 0xFFFFFFFF
};

struct sEditTraitCaps
{
	ulong Flags;
};

#define INTERFACE IEditTrait
DECLARE_GUID(IEditTrait);
DECLARE_INTERFACE_(IEditTrait,IUnknown)
{
	STDMETHOD_(const sEditTraitDesc*,Describe)(THIS) PURE;
	STDMETHOD_(const sEditTraitCaps*,Capabilities)(THIS) PURE;
	STDMETHOD_(Bool,IntrinsicTo)(THIS_ int) PURE;
	STDMETHOD_(long,Add)(THIS_ int) PURE;
	STDMETHOD(Remove)(THIS_ int) PURE;
	STDMETHOD(Edit)(THIS_ int) PURE;
	STDMETHOD(Parse)(THIS_ int,const char*) PURE;
	STDMETHOD(Unparse)(THIS_ int,char*,int) PURE;
};
DEFINE_IIDSTRUCT(IEditTrait,IID_IEditTrait);
#undef INTERFACE

struct sEditTraitIter
{
	int id;
};

#define INTERFACE IObjEditors
DECLARE_GUID(IObjEditors);
DECLARE_INTERFACE_(IObjEditors,IUnknown)
{
	STDMETHOD(AddTrait)(THIS_ IEditTrait*) PURE;
	STDMETHOD(RemoveTrait)(THIS_ IEditTrait*) PURE;
	STDMETHOD_(IEditTrait*,AddProperty)(THIS_ IProperty*) PURE;
	STDMETHOD_(IEditTrait*,FirstTrait)(THIS_ sEditTraitIter*) PURE;
	STDMETHOD_(IEditTrait*,NextTrait)(THIS_ sEditTraitIter*) PURE;
	STDMETHOD_(IObjEditor*,Create)(THIS_ sObjEditorDesc*,int) PURE;
};
DEFINE_IIDSTRUCT(IObjEditors,IID_IObjEditors);
#undef INTERFACE

#define INTERFACE IEditTools
DECLARE_GUID(IEditTools);
DECLARE_INTERFACE_(IEditTools,IUnknown)
{
	STDMETHOD_(const char*,ObjName)(THIS_ int) PURE;
	STDMETHOD_(int,GetObjNamed)(THIS_ const char*) PURE;
	STDMETHOD(EditTypedData)(THIS_ const char*, const char*, void*) PURE;
};
DEFINE_IIDSTRUCT(IEditTools,IID_IEditTools);
#undef INTERFACE

#endif // _LG_EDITOR_H

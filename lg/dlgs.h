/**********************
 * LGS Dialog Interfaces
 */

#ifndef _LG_DLGS_H
#define _LG_DLGS_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#include <lg/types.h>

struct sObjStimPair;
struct sStimSourceDesc;
struct sReceptron;

interface IStructEditor;

struct sStructEditorEvent
{
	uint button;
	IStructEditor* editor;
};

typedef void (__stdcall *StructEditorCallback)(sStructEditorEvent,void*);

enum eStructEditorFlags
{
	kStructEditorNoLabels = 1,
	kStructEditorNoOK = 8,
	kStructEditorNoCancel = 16,
	kStructEditorNoApply = 32
};

struct sStructEditorDesc
{
	char title[32];
	ulong flags;
};

struct sObjEditorEvent
{
	uint button;
	IObjEditor* editor;
};

typedef void (__stdcall *ObjEditorCallback)(sObjEditorEvent,void*);

enum eObjEditorFlags
{
	kObjEditorShowAll = 1
};

struct sObjEditorDesc
{
	char title[32];
	ulong flags;
};

enum eLinkEditorFlags
{
	kLinkEditorDoneButton = 1,
	kLinkEditorAddButton = 2,
	kLinkEditorRemoveButton = 4,
	kLinkEditorEditButton = 8,
	kLinkEditorShowAll = 0x10000,
	kLinkEditorModeless = 0x20000
};

struct sLinkEditorDesc
{
	char title[64];
	ulong flags;
};

enum eHierarchyRootFlag
{
	kHierarchyRootShowConcrete = 1,
	kHierarchyRootNoAdd = 2,
	kHierarchyRootNoDel = 4,
	kHierarchyRootNoCreate = 8
};

enum eHierarchyCallbackResult
{
	kHierarchyResultDefault = 1,
	kHierarchyResultRefresh = 2,
	kHierarchyResultClose = 4,
	kHierarchyResultCancel = 8
};

struct sHierarchyRootDesc
{
	char label[32];
	char name[16];
	ulong flags;
	// Any of these callbacks can be NULL. In which case,
	// the dialog should handle the event itself (if it can)
	int (__stdcall *AddCallback)(int,const char*);	// retuns 10 or 1
	int (__stdcall *DeleteCallback)(int);	// returns 1 or 8
	int (__stdcall *CreateCallback)(int);	// returns 5
};

struct sHierarchyEditorDesc
{
	char title[32];
	ulong flags;
	sHierarchyRootDesc* root;
	// The list of roots is terminated with an empty struct.
};

#define INTERFACE IStructEditor
DECLARE_GUID(IStructEditor);
DECLARE_INTERFACE_(IStructEditor,IUnknown)
{
	STDMETHOD_(Bool,Show)(THIS_ Bool) PURE;
	STDMETHOD(SetCallback)(THIS_ StructEditorCallback,void*) PURE;
	STDMETHOD_(const sStructEditorDesc*,Describe)(THIS) PURE;
	STDMETHOD_(const sStructDesc*,DescribeStruct)(THIS) PURE;
	STDMETHOD_(void*,Data)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IStructEditor,IID_IStructEditor);
#undef INTERFACE

#define INTERFACE IObjEditor
DECLARE_GUID(IObjEditor);
DECLARE_INTERFACE_(IObjEditor,IUnknown)
{
	STDMETHOD_(Bool,Show)(THIS_ Bool) PURE;
	STDMETHOD(SetCallback)(THIS_ ObjEditorCallback,void*) PURE;
	STDMETHOD_(const sObjEditorDesc*,Describe)(THIS) PURE;
	STDMETHOD_(int,ID)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IObjEditor,IID_IObjEditor);
#undef INTERFACE

#define INTERFACE IActReactEditors
DECLARE_GUID(IActReactEditors);
DECLARE_INTERFACE_(IActReactEditors,IUnknown)
{
	STDMETHOD(EditSource)(THIS_ int,sObjStimPair*,sStimSourceDesc*) PURE;
	STDMETHOD(EditReceptron)(THIS_ int,sObjStimPair*,sReceptron*) PURE;
	STDMETHOD(ListReceptrons)(THIS_ int,const sObjStimPair*) PURE;
	STDMETHOD(ListSources)(THIS_ int,const sObjStimPair*) PURE;
};
DEFINE_IIDSTRUCT(IActReactEditors,IID_IActReactEditors);
#undef INTERFACE

#endif // _LG_DLGS_H

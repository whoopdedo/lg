/**************************
 * LGS Property Interfaces
 */

#ifndef _LG_PROPERTIES_H
#define _LG_PROPERTIES_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>
#include <lg/types.h>
#include <lg/data.h>

struct sPropertyConstraint
{
	int iType;
	const char* pszProp;
};

struct sPropertyDesc
{
	char	szName[16];
	uint	uiFlags;
	const sPropertyConstraint*	pConstraints;
	ulong	uVersion;
	ulong	uOldVersion;
	const char*	pszParentMenu;
	const char*	pszMenuLabel;
	const char*	pszDescription;
	uint	uiNetFlags;
};

struct sPropertyTypeDesc
{
	char	szTypeName[32];
	ulong	uTypeSize;
};

struct sPropertyStoreDesc
{
	const char*	pszName;
};

struct sPropertyObjIter
{
	int iObjId;
	void* unused[4];
};

// Alse the bitmask when registering a listener.
enum ePropertyEvent
{
	kPropertyChange = 1,
	kPropertyAdd    = 2,
	kPropertyDelete = 4,
	// Don't know what 8 does,
	// sometimes shows up as event 11 which might be when a tagfile is loaded
	kPropertyInherited = 16,	// change of inherited property
	kPropertyInheritedIsRelevant = 32, // with above, when the property is still relevant
	kPropertyFromNetwork = 64,
	// These are only for registering
	kPropertyFull   = 15,
};
struct sPropertyListenMsg
{
	ePropertyEvent event;
	int iPropId;
	int iObjId;
	void* pData;	// not necessarily a pointer
	int iArchetype;
};

LG_DECLARE_HANDLE(PropListenerHandle);
LG_DECLARE_HANDLE(PropListenerData);

typedef void (__stdcall *PropListenFunc)(sPropertyListenMsg*,PropListenerData);

#define INTERFACE IPropertyStore
DECLARE_GUID(IPropertyStore);
DECLARE_INTERFACE_(IPropertyStore,IUnknown)
{
	STDMETHOD_(const sPropertyStoreDesc*,Describe)(THIS) const PURE;
	STDMETHOD_(long,SetID)(THIS_ int) PURE;
	STDMETHOD_(sDatum*,Create)(THIS_ sDatum &,int) PURE;
	STDMETHOD_(long,Delete)(THIS_ int) PURE;
	STDMETHOD_(int,Relevant)(THIS_ int) const PURE;
	STDMETHOD_(int,Get)(THIS_ int,sDatum *) const PURE;
	STDMETHOD_(long,Set)(THIS_ int,sDatum) PURE;
	STDMETHOD_(sDatum*,Copy)(THIS_ sDatum &,int,int) PURE;
	STDMETHOD_(long,Reset)(THIS) PURE;
	STDMETHOD_(long,IterStart)(THIS_ sPropertyObjIter *) const PURE;
	STDMETHOD_(int,IterNext)(THIS_ sPropertyObjIter *,int*,sDatum*) const PURE;
	STDMETHOD_(long,IterStop)(THIS_ sPropertyObjIter *) const PURE;
	STDMETHOD_(int,GetCopy)(THIS_ int,sDatum *) PURE;
	STDMETHOD_(long,ReleaseCopy)(THIS_ int,sDatum) PURE;
	STDMETHOD_(long,WriteObj)(THIS_ int,IDataOpsFile *) PURE;
	STDMETHOD_(long,ReadObj)(THIS_ int,IDataOpsFile *,int) PURE;
	STDMETHOD_(int,WriteVersion)(THIS) PURE;
	STDMETHOD_(IDataOps*,GetOps)(THIS) PURE;
	STDMETHOD_(long,SetOps)(THIS_ IDataOps *) PURE;
};
DEFINE_IIDSTRUCT(IPropertyStore,IID_IPropertyStore);
#undef INTERFACE

#define INTERFACE IProperty
DECLARE_GUID(IProperty);
DECLARE_INTERFACE_(IProperty,IUnknown)
{
	STDMETHOD_(const sPropertyDesc*,Describe)(THIS) const PURE;
	STDMETHOD_(int,GetID)(THIS) const PURE;
	STDMETHOD_(const sPropertyTypeDesc*,DescribeType)(THIS) const PURE;
	STDMETHOD_(long,Create)(THIS_ int) PURE;
	STDMETHOD_(long,Copy)(THIS_ int,int) PURE;
	STDMETHOD_(long,Delete)(THIS_ int) PURE;
	STDMETHOD_(int,IsRelevant)(THIS_ int) const PURE;
	STDMETHOD_(int,IsSimplyRelevant)(THIS_ int) const PURE;
	STDMETHOD_(int,Touch)(THIS_ int) PURE;
	STDMETHOD_(void,Notify)(THIS_ ulong,void*) PURE;
	STDMETHOD_(PropListenerHandle,Listen)(THIS_ ulong,PropListenFunc,PropListenerData) PURE;
	STDMETHOD_(long,Unlisten)(THIS_ PropListenerHandle) PURE;
	STDMETHOD_(void,IterStart)(THIS_ sPropertyObjIter*) const PURE;
	STDMETHOD_(int,IterNext)(THIS_ sPropertyObjIter*,int*) const PURE;
	STDMETHOD_(void,IterStop)(THIS_ sPropertyObjIter*) const PURE;
};
DEFINE_IIDSTRUCT(IProperty,IID_IProperty);
#undef INTERFACE

#define DEFINE_PROPERTY_IIDSTRUCT(iface)	DEFINE_IIDSTRUCT2(iface,IProperty,IID_##iface)

template<typename _Data>
interface IProperty_Type : IProperty
{
	STDMETHOD_(int,Set)(int,_Data) PURE;
	STDMETHOD_(int,TouchValue)(int,_Data) PURE;
	STDMETHOD_(int,Get)(int,_Data*) PURE;
	STDMETHOD_(int,GetSimple)(int,_Data*) PURE;
	STDMETHOD_(int,IterNextValue)(sPropertyObjIter*,int*,_Data*) const PURE;
};

typedef IProperty_Type<void*> IGenericProperty;
DEFINE_IIDSTRUCT2(IGenericProperty,IProperty,IID_IProperty);

#define DEFINE_PROPERTY_INTERFACE(iface,tdef)	interface iface : IProperty_Type< tdef > {}; \
	DEFINE_IIDSTRUCT2(iface,IProperty,IID_##iface)

DECLARE_GUID(IIntProperty);
interface IIntProperty : IProperty_Type<int> {};
DEFINE_PROPERTY_IIDSTRUCT(IIntProperty);

DECLARE_GUID(IBoolProperty);
interface IBoolProperty : IProperty_Type<Bool> {};
DEFINE_PROPERTY_IIDSTRUCT(IBoolProperty);

DECLARE_GUID(IFloatProperty);
interface IFloatProperty : IProperty_Type<float> {};
DEFINE_PROPERTY_IIDSTRUCT(IFloatProperty);

DECLARE_GUID(IStringProperty);
interface IStringProperty : IProperty_Type<const char*> {};
DEFINE_PROPERTY_IIDSTRUCT(IStringProperty);

DECLARE_GUID(IVectorProperty);
interface IVectorProperty : IProperty_Type<const mxs_vector*> {};
DEFINE_PROPERTY_IIDSTRUCT(IVectorProperty);

#endif // _LG_PROPERTIES_H

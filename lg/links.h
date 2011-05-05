/*************
 * LGS Links
 */

#ifndef _LG_LINKS_H
#define _LG_LINKS_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#include <lg/types.h>
#include <lg/defs.h>

#define INTERFACE ILinkQuery
DECLARE_GUID(ILinkQuery);
DECLARE_INTERFACE_(ILinkQuery,IUnknown)
{
	STDMETHOD_(Bool,Done)(THIS) const PURE;
	STDMETHOD(Link)(THIS_ sLink *) const PURE;
	STDMETHOD_(long,ID)(THIS) const PURE;
	// The pointer should not be freed.
	STDMETHOD_(void*,Data)(THIS) const PURE;
	STDMETHOD_(long,Next)(THIS) PURE;
	STDMETHOD_(ILinkQuery*,Inverse)(THIS) PURE;
};
DEFINE_IIDSTRUCT(ILinkQuery,IID_ILinkQuery);
#undef INTERFACE

enum eRelationEvent
{
	kRelationChange = 1,
	kRelationAdd    = 2,
	// not sure what 4 is, related to Delete somehow
	kRelationDelete = 8,

	kRelationFull   = 15
};
struct sRelationListenMsg
{
	eRelationEvent event;
	long lLink;
	int source;
	int dest;
	short flavor;
};
typedef void (__stdcall *RelListenFunc)(sRelationListenMsg*,void*);

struct sRelationDesc
{
	char szName[45];
	unsigned int uiFlags;
};

struct sRelationDataDesc
{
	char szTypeName[32];
	unsigned int uiTypeSize;
	unsigned int uiFlags;
};

#define INTERFACE IRelation
DECLARE_GUID(IRelation);
DECLARE_INTERFACE_(IRelation,IUnknown)
{
	// This function returns information about the relation
	STDMETHOD_(const sRelationDesc*,Describe)(THIS) const PURE;
	// The functions below get and set (but don't do that!) the ID of the relation
	STDMETHOD_(short,GetID)(THIS) const PURE;
	STDMETHOD(SetID)(THIS_ short) PURE;
	// This function returns the data definition of the relation
	STDMETHOD_(const sRelationDataDesc*,DescribeData)(THIS) const PURE;
	// This function returns the corresponding inverse relation (~Name)
	STDMETHOD_(IRelation*,Inverse)(THIS) PURE;
	// Add links
	STDMETHOD_(long,Add)(THIS_ int,int) PURE;
	// The contents of the data pointer are copied. (Be sure the memory it points to is large enough to be read.)
	// Wasn't originally const, I changed it to allow the use of string literals.
	STDMETHOD_(long,AddFull)(THIS_ int,int,const void *) PURE;
	STDMETHOD(Remove)(THIS_ long) PURE;
	// The function below retrieves link information, given the link ID.
	STDMETHOD_(Bool,Get)(THIS_ long,sLink *) const PURE;
	STDMETHOD(SetData)(THIS_ long,void *) PURE;
	// The pointer should not be freed
	STDMETHOD_(void*,GetData)(THIS_ long) PURE;
	STDMETHOD_(ILinkQuery*,Query)(THIS_ int,int) const PURE;
	STDMETHOD(Notify)(THIS_ ulong,void *) PURE;
	STDMETHOD(Listen)(THIS_ ulong,RelListenFunc,void *) PURE;
	STDMETHOD_(long,GetSingleLink)(THIS_ int,int) PURE;
	STDMETHOD_(Bool,AnyLinks)(THIS_ int,int) PURE;
};
DEFINE_IIDSTRUCT(IRelation,IID_IRelation);
#undef INTERFACE


///////////
// linkset
///////////
inline linkset& linkset::operator=(ILinkQuery* __q)
{
	if (query) query->Release();
	query = __q;
	return *this;
}
inline linkset::~linkset()
{
	if (query) query->Release();
}
inline link linkset::Link() const
{
	link __l;
	if (query)
		__l = query->ID();
	return __l;
}
inline void linkset::NextLink()
{
	if (query) query->Next();
}
inline bool linkset::AnyLinksLeft() const
{
	return (query && !query->Done());
}
inline void* linkset::Data() const
{
	return (query) ? query->Data() : NULL;
}
inline sLink linkset::Get() const
{
	sLink __sl;
	if (query)
		query->Link(&__sl);
	else
		__sl.flavor = __sl.dest = __sl.source = 0;
	return __sl;
}


#endif // _LG_LINKS_H

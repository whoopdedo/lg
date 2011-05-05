/***********************
 * LGS IID Helper class
 */

#ifndef _LG_IIDDEF_H
#define _LG_IIDDEF_H

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus

#include <lg/config.h>
#include <lg/objstd.h>


#define DEFINE_IIDSTRUCT(_iface,_iid)	                 \
		template<> struct IID_Def<_iface>                \
		{                                                \
			static const IID& iid() { return _iid; }            \
			static const char* name() { return #_iface; }       \
			static bool implements(const IID& riid) { return riid==_iid || IID_Def<IUnknown>::implements(riid); } \
		}
#define DEFINE_IIDSTRUCT2(_iface,_ifnext,_iid)	                 \
		template<> struct IID_Def<_iface>                \
		{                                                \
			static const IID& iid() { return _iid; }            \
			static const char* name() { return #_iface; }       \
			static bool implements(const IID& riid) { return riid==_iid || IID_Def<_ifnext>::implements(riid); } \
		}

template<typename _IFace>
struct IID_Def
{
	static const IID& iid();
	static const char* name();
	static bool implements(const IID&);
};

template<> struct IID_Def<IUnknown>
{
	static const IID& iid() { return IID_IUnknown; }
	static const char* name() { return "IUnknown"; }
	static bool implements(const IID& riid) { return riid == IID_IUnknown; }
};

DEFINE_IIDSTRUCT(IMalloc,IID_IMalloc);

#else // !__cplusplus

#define DEFINE_IIDSTRUCT(_iface,_iid)

#define DEFINE_IIDSTRUCT2(_iface,_ifnext,_iid)

#endif

#endif // _LG_IIDDEF_H

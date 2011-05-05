/*******************************
 * LGS Script and Script Module
 */

#ifndef _LG_SCRIPT_H
#define _LG_SCRIPT_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#include <lg/types.h>
#include <lg/scrmsgs.h>

#define INTERFACE IScriptModule
DECLARE_GUID(IScriptModule);
DECLARE_INTERFACE_(IScriptModule,IUnknown)
{
	STDMETHOD_(const char*,GetName)(THIS) PURE;
	STDMETHOD_(const sScrClassDesc*,GetFirstClass)(THIS_ tScrIter *) PURE;
	STDMETHOD_(const sScrClassDesc*,GetNextClass)(THIS_ tScrIter *) PURE;
	STDMETHOD_(void,EndClassIter)(THIS_ tScrIter *) PURE;
};
DEFINE_IIDSTRUCT(IScriptModule,IID_IScriptModule);
#undef INTERFACE

/* Big Honkin' Notice because I keep forgetting...
 * The reply parameter of ReceiveMessage may be NULL.
 */
#define INTERFACE IScript
DECLARE_GUID(IScript);
DECLARE_INTERFACE_(IScript,IUnknown)
{
	STDMETHOD_(const char*,GetClassName)(THIS) PURE;
	STDMETHOD(ReceiveMessage)(THIS_ sScrMsg *,sMultiParm *,eScrTraceAction) PURE;
};
DEFINE_IIDSTRUCT(IScript,IID_IScript);
#undef INTERFACE

#endif // _LG_SCRIPT_H

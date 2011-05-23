/************************
 * LGS Data Marshalling
 */

#ifndef _LG_DATA_H
#define _LG_DATA_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/types.h>

struct sDatum
{
	union {
		int i;
		float f;
		char*  psz;
		mxs_vector*  pVector;
		Bool b;
		void* pv;
	};
};

enum eDataOpSeek
{
	kSeekSet,
	kSeekCur,
	kSeekEnd
};

#define INTERFACE IDataOpsFile
DECLARE_GUID(IDataOpsFile);
DECLARE_INTERFACE_(IDataOpsFile,IUnknown)
{
	STDMETHOD_(ulong,Read)(THIS_ void*,ulong) PURE;
	STDMETHOD_(ulong,Write)(THIS_ const void*,ulong) PURE;
	STDMETHOD(Seek)(THIS_ eDataOpSeek,ulong) PURE;
	STDMETHOD_(ulong,Tell)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IDataOpsFile,IID_IDataOpsFile);
#undef INTERFACE

#define INTERFACE IDataOpsMemFile
DECLARE_GUID(IDataOpsMemFile);
DECLARE_INTERFACE_(IDataOpsMemFile,IUnknown)
{
	STDMETHOD_(ulong,Read)(THIS_ void*,ulong) PURE;
	STDMETHOD_(ulong,Write)(THIS_ const void*,ulong) PURE;
	STDMETHOD(Seek)(THIS_ eDataOpSeek,ulong) PURE;
	STDMETHOD_(ulong,Tell)(THIS) PURE;
	STDMETHOD_(void*,GetBuffer)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IDataOpsMemFile,IID_IDataOpsMemFile);
#undef INTERFACE

#define INTERFACE IDataOps
DECLARE_GUID(IDataOps);
DECLARE_INTERFACE_(IDataOps,IUnknown)
{
	STDMETHOD_(sDatum*,New)(THIS_ sDatum&) PURE;
	STDMETHOD_(sDatum*,CopyNew)(THIS_ sDatum&,sDatum) PURE;
	STDMETHOD(Delete)(THIS_ sDatum) PURE;
	STDMETHOD(Copy)(THIS_ sDatum*,sDatum) PURE;
	STDMETHOD_(long,BlockSize)(THIS_ sDatum) PURE;
	STDMETHOD_(int,Version)(THIS) PURE;
	STDMETHOD(Read)(THIS_ sDatum*,IDataOpsFile*,int) PURE;
	STDMETHOD(Write)(THIS_ sDatum,IDataOpsFile*) PURE;
};
DEFINE_IIDSTRUCT(IDataOps,IID_IDataOps);
#undef INTERFACE

#endif

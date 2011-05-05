#ifndef _LG_QUEST_H
#define _LG_QUEST_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#define INTERFACE IQuestDataIter
DECLARE_GUID(IQuestDataIter);
DECLARE_INTERFACE_(IQuestDataIter,IUnknown)
{
	STDMETHOD_(Bool,Done)(THIS) PURE;
	STDMETHOD(Next)(THIS) PURE;
	STDMETHOD_(const char*,Name)(THIS) PURE;
	STDMETHOD_(int,Value)(THIS) PURE;
};
DEFINE_IIDSTRUCT(IQuestDataIter,IID_IQuestDataIter);
#undef INTERFACE

typedef long (__cdecl *QuestSaveLoadFunc)(void *,uint,uint);
typedef Bool (__cdecl *QuestFilterFunc)(const char *,int,int);

#define INTERFACE IQuestData
DECLARE_GUID(IQuestData);
DECLARE_INTERFACE_(IQuestData,IUnknown)
{
	STDMETHOD(Create)(THIS_ const char *,int,int) PURE;
	STDMETHOD(Set)(THIS_ const char *,int) PURE;
	STDMETHOD_(int,Get)(const char *) PURE;
	STDMETHOD_(Bool,Exists)(THIS_ const char *) PURE;
	STDMETHOD(Delete)(THIS_ const char *) PURE;
	STDMETHOD_(IQuestDataIter*,Iter)(THIS_ int) PURE;
	STDMETHOD(DeleteAll)(THIS) PURE;
	STDMETHOD(DeleteAllType)(THIS_ int) PURE;
	STDMETHOD_(Bool,Save)(THIS_ QuestSaveLoadFunc,int) PURE;
	STDMETHOD_(Bool,Load)(THIS_ QuestSaveLoadFunc,int) PURE;
	STDMETHOD(SubscribeMsg)(THIS_ int,const char *,int) PURE;
	STDMETHOD(UnsubscribeMsg)(THIS_ int,const char *) PURE;
	STDMETHOD(ObjDeleteListener)(THIS_ int) PURE;
	STDMETHOD(UnsubscribeAll)(THIS) PURE;
	// WARNING Dromed only
	STDMETHOD(ObjSpewListen)(THIS_ int) PURE;
	STDMETHOD(Filter)(THIS_ QuestFilterFunc,void *) PURE;
};
DEFINE_IIDSTRUCT(IQuestData,IID_IQuestData);
#undef INTERFACE

DECLARE_GUID(ICampaign);

#endif // _LG_QUEST_H

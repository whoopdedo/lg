#ifndef _LG_OBJSTD_H
#define _LG_OBJSTD_H

#ifdef __cplusplus
#include <cstring>
#include <climits>
#else
#error "LG requires C++ ... for now"
#include <string.h>
#include <limits.h>
#endif

typedef unsigned int	Bool;
typedef unsigned char	uchar;
typedef unsigned int	uint;
typedef unsigned long	ulong;

#ifndef NULL
#define NULL 0
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

typedef void*	HANDLE;
typedef long	HRESULT;
typedef unsigned char	Byte;
typedef short	Short;
typedef unsigned short	Word;
typedef unsigned long	DWord;

#define LG_DECLARE_HANDLE(T)	typedef struct T##__{} *T

#include <windef.h>
#include <basetyps.h>
/*
#define interface struct
#define STDMETHODCALLTYPE	__stdcall
#define STDMETHODIMP	HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(t)	t STDSTDMETHODCALLTYPE
#define STDMETHOD(m)	virtual HRESULT STDMETHODCALLTYPE m
#define STDMETHOD_(t,m)	virtual t STDMETHODCALLTYPE m
#define PURE	=0
#define THIS_
#define THIS	void
#define DECLARE_INTERFACE(I)	interface I
#define DECLARE_INTERFACE_(I,B)	interface I : public B
#define EXTERN_C extern "C"
#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID
{
	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
} GUID;
typedef GUID IID;
typedef GUID CLSID;
#define REFGUID const GUID&
#define REFIID const IID&
#define REFCLSID const CLSID&
#endif
#ifdef INITGUID
#define DEFINE_GUID(n,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
	EXTERN_C const GUID n = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}
#else
#define DEFINE_GUID(n,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
	EXTERN_C const GUID n
#endif
*/
#ifdef __cplusplus
# ifndef _SYS_GUID_OPERATORS_
inline bool IsEqualGUID(REFGUID rguid1, REFGUID rguid2)
	{ return (&rguid1 == &rguid2) || !::memcmp(&rguid1, &rguid2, sizeof(GUID)); }
inline bool operator==(const GUID& guidOne, const GUID& guidOther)
	{ return IsEqualGUID(guidOne,guidOther); }
inline bool operator!=(const GUID& g1, const GUID& g2)
	{ return !(g1 == g2); }
# endif
#else
# ifndef IsEqualGUID
# define IsEqualGUID(rguid1, rguid2)	(!memcmp((rguid1), (rguid2), sizeof(GUID)))
# endif
#endif
#define DECLARE_GUID(I)	EXTERN_C const GUID IID_##I
/* system headers may add extra attributes that aren't important */
#ifdef __cplusplus
#ifndef WINAPI
#define WINAPI __stdcall
#endif
#undef DECLARE_INTERFACE
#undef DECLARE_INTERFACE_
#define DECLARE_INTERFACE(I)	interface I
#define DECLARE_INTERFACE_(I,B)	interface I : public B
#undef STDMETHOD
#undef STDMETHOD_
#define STDMETHOD(m)	virtual STDMETHODATTRIBUTE HRESULT STDMETHODCALLTYPE m
#define STDMETHOD_(t,m)	virtual STDMETHODATTRIBUTE t STDMETHODCALLTYPE m
#ifdef __GNUC__
#define STDMETHODATTRIBUTE	__attribute__((nothrow))
#elif defined(_MSC_VER)
#define STDMETHODATTRIBUTE	__declspec(nothrow)
#else
#define STDMETHODATTRIBUTE
#endif
#endif

#define INTERFACE IUnknown
DECLARE_INTERFACE(IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,void**) PURE;
	STDMETHOD_(ulong,AddRef)(THIS) PURE;
	STDMETHOD_(ulong,Release)(THIS) PURE;
};
DECLARE_GUID(IUnknown);
#undef INTERFACE

#ifdef __cplusplus
#define DECLARE_UNKNOWN_METHODS
#else
#define DECLARE_UNKNOWN_METHODS	\
	STDMETHOD(QueryInterface)(THIS_ REFIID,void**) PURE; \
	STDMETHOD_(ulong,AddRef)(THIS) PURE; \
	STDMETHOD_(ulong,Release)(THIS) PURE
#endif

#define INTERFACE IMalloc
DECLARE_INTERFACE_(IMalloc,IUnknown)
{
	STDMETHOD_(void*,Alloc)(THIS_ ulong) PURE;
	STDMETHOD_(void*,Realloc)(THIS_ void*,ulong) PURE;
	STDMETHOD_(void,Free)(THIS_ void*) PURE;
	STDMETHOD_(ulong,GetSize)(THIS_ void*) PURE;
	STDMETHOD_(int,DidAlloc)(THIS_ void*) PURE;
	STDMETHOD_(void,HeapMinimize)(THIS) PURE;
};
DECLARE_GUID(IMalloc);
#undef INTERFACE

#ifndef __cplusplus
#define IMalloc_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IMalloc_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IMalloc_Release(This) (This)->lpVtbl->Release(This)
#define IMalloc_Alloc(This,cb) (This)->lpVtbl->Alloc(This,cb)
#define IMalloc_Realloc(This,pv,cb) (This)->lpVtbl->Realloc(This,pv,cb)
#define IMalloc_Free(This,pv) (This)->lpVtbl->Free(This,pv)
#define IMalloc_GetSize(This,pv) (This)->lpVtbl->GetSize(This,pv)
#define IMalloc_DidAlloc(This,pv) (This)->lpVtbl->DidAlloc(This,pv)
#define IMalloc_HeapMinimize(This) (This)->lpVtbl->HeapMinimize(This)
#endif

#include <winerror.h>
/*
#define NOERROR	S_OK
#define SUCCEEDED(Status) ((HRESULT)(Status)>=0)
#define FAILED(Status) ((HRESULT)(Status)<0)
#define E_UNEXPECTED ((HRESULT)0x8000FFFFL)
#define E_NOTIMPL ((HRESULT)0x80004001L)
#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#define E_INVALIDARG ((HRESULT)0x80070057L)
#define E_NOINTERFACE ((HRESULT)0x80004002L)
#define E_POINTER ((HRESULT)0x80004003L)
#define E_HANDLE ((HRESULT)0x80070006L)
#define E_ABORT ((HRESULT)0x80004004L)
#define E_FAIL ((HRESULT)0x80004005L)
#define E_PENDING ((HRESULT)0x8000000AL)
#define S_OK ((HRESULT)0x00000000L)
#define S_FALSE ((HRESULT)0x00000001L)
*/

#endif // _LG_OBJSTD_H

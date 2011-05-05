/************************************************
 * LGS Interface implementation helper
 */

#ifndef _LG_INTERFACEIMP_H
#define _LG_INTERFACEIMP_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>

#ifdef __BORLANDC__
#pragma warn -inl
#endif

class cRefCnt
{
private:
	uint m_iRef;
public:
	cRefCnt() : m_iRef(1) { }
	uint IncRef();
	uint DecRef();
private:
	cRefCnt(const cRefCnt&);
	cRefCnt& operator=(const cRefCnt&);
};

class cRefCntImp
{
private:
	cRefCnt m_iRef;
protected:
	virtual void DisposeRef(void) { }
	virtual ~cRefCntImp() { }
	cRefCntImp() { }
	uint IncRef() { return m_iRef.IncRef(); }
	uint DecRef()
	{
		uint ref = m_iRef.DecRef();
		if (ref == 0)
			DisposeRef();
		return ref;
	}
};

enum eInterfaceImpSelector { kInterfaceImpStatic, kInterfaceImpDynamic };

template <class _IFace, typename _IID=IID_Def<_IFace>, const eInterfaceImpSelector _Sel=kInterfaceImpDynamic>
class cInterfaceImp : public _IFace, private cRefCntImp
{
public:
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv)
		{
			if (!_IID::implements(riid))
			{
				*ppv = 0;
				return E_NOINTERFACE;
			}
			*ppv = static_cast<_IFace*>(this);
			AddRef();
			return 0;
		}
	virtual ulong __stdcall AddRef()
		{ return IncRef(); }
	virtual ulong __stdcall Release()
		{ return DecRef(); }
	cInterfaceImp() { }
	virtual ~cInterfaceImp() { }
protected:
	virtual void DisposeRef(void)
		{
			if (_Sel == kInterfaceImpDynamic)
				delete this;
		}
};

#ifdef __BORLANDC__
#pragma warn .inl
#endif

#endif // _LG_INTERFACEIMP_H

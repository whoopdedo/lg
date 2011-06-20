/************************************************
 * LGS Auto-Release wrapper for Script interface
 */

#ifndef _LG_INTERFACE_H
#define _LG_INTERFACE_H

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus

#include <exception>
#include <cstdio>

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/iiddef.h>
#include <lg/scrmanagers.h>
//#include <lg/scrservices.h>

#ifdef __BORLANDC__
#pragma warn -inl
#endif

DECLARE_GUID(INullScriptService);

class null_pointer : public std::exception
{
public:
	null_pointer() NO_THROW { }
	virtual ~null_pointer() NO_THROW { }

	virtual const char* what() const NO_THROW
	{ return "null pointer"; }
};
#ifdef IFACE_NULLSAFE
#define THROW_IFNULL SPEC_THROW(null_pointer)
#else
#define THROW_IFNULL NO_THROW
#endif

class no_interface : public std::exception
{
	const char* ifname;
	char* buf;
public:
	no_interface() NO_THROW : ifname(NULL), buf(NULL) { }
	no_interface(const char* nm) : ifname(nm)
	{
		buf = new char[::strlen(nm) + 27];
		::sprintf(buf, "interface not available (%s)", nm);
	}
	virtual ~no_interface() NO_THROW
	{
		if (buf)
			delete[] buf;
	}

	virtual const char* what() const NO_THROW
	{
		return buf;
	}
};

/**************************************
 * Helper class for interface pointers.
 *
 * This class manages the reference count of an interface pointer.
 * Similar to the STL shared_ptr. When converting a raw pointer
 * to a wrapped pointer, the constructor will take ownership of
 * the reference, where assignment will acquire a new reference.
 * This leads to the typical use case:
 *     SInterface<IFace> sptr = function_that_creates_an_interface();
 * If you need to preserve the existing reference, use assignment.
 *     SInterface<IFace> sptr;
 *     sptr = global_interface_pointer;
 * This only applies to raw pointers of the same type. When copying
 * wrapped pointers, or coercing from another type, references are
 * always preserved.
 */
template<class _IFace, typename _IID = IID_Def<_IFace> >
class SInterface
{
	_IFace* m_pIFace;

public:
	/**
	 * Release the interface when the object is destroyed.
	 */
	~SInterface() NO_THROW
	{
		if (m_pIFace)
			m_pIFace->Release();
	}
	/**
	 * Initialize the interface with a NULL pointer.
	 */
	SInterface() NO_THROW
		: m_pIFace(NULL)
	{
	}
	/**
	 * Initialize with an acquired pointer.
	 * The wrapper takes ownership of the reference.
	 */
	SInterface(_IFace* __p) NO_THROW
		: m_pIFace(__p)
	{
	}
	/**
	 * Copy a wrapped interface.
	 */
	SInterface(const SInterface& __x) NO_THROW
		: m_pIFace(__x.get())
	{
		if (m_pIFace)
			m_pIFace->AddRef();
	}
	/**
	 * Copy a compatible wrapped interface.
	 * The reference must be static_cast-able to this type.
	 */
	template<class _ExtIFace>
	SInterface(const SInterface<_ExtIFace>& __x) NO_THROW
	{
		m_pIFace = static_cast<_IFace*>(__x.get());
		if (m_pIFace)
			m_pIFace->AddRef();
	}
	/**
	 * Create a pointer using QueryInterface.
	 * Does not alter the reference count of the source.
	 */
	SInterface(IUnknown* pSM) SPEC_THROW(no_interface)
		: m_pIFace(NULL)
	{
		set(pSM);
	}

	/**
	 * Copy a new reference to the wrapped pointer.
	 */
	SInterface& operator=(const SInterface& __x) NO_THROW
	{
		_IFace* pTemp;
		if ((pTemp = __x.get()))
			pTemp->AddRef();
		if (m_pIFace)
			m_pIFace->Release();
		m_pIFace = pTemp;
		return *this;
	}
	/**
	 * Copy a new reference to the pointer.
	 */
	SInterface& operator=(_IFace* __p) NO_THROW
	{
		if (__p)
			__p->AddRef();
		if (m_pIFace)
			m_pIFace->Release();
		m_pIFace = __p;
		return *this;
	}
	/**
	 * Copy a new reference to the compatible wrapped pointer.
	 */
	template<class _ExtIFace>
	SInterface& operator=(const SInterface<_ExtIFace>& __x) NO_THROW
	{
		_IFace* pTemp;
		if (pTemp = static_cast<_IFace*>(__x.get()))
			pTemp->AddRef();
		if (m_pIFace)
			m_pIFace->Release();
		m_pIFace = pTemp;
		return *this;
	}
	/**
	 * Acquire an interface from a generic pointer using QueryInterface.
	 * Does not alter the reference count of the source.
	 */
	SInterface& operator=(IUnknown* __p) SPEC_THROW(no_interface)
	{
		_IFace* pTemp;
		pTemp = _qi(__p);
		if (m_pIFace)
			m_pIFace->Release();
		m_pIFace = pTemp;
		return *this;
	}

	/**
	 * A wrapped pointer is "true" iff the pointer is not NULL.
	 */
	operator bool () const NO_THROW
	{
		return m_pIFace != NULL;
	}
	/**
	 * A wrapped pointer is "false" iff the pointer is NULL.
	 */
	bool operator! () const NO_THROW
	{
		return m_pIFace == NULL;
	}
	/**
	 * Returns whether wrapped pointers are identical.
	 */
	bool operator== (const SInterface& __x) const NO_THROW
	{
		return m_pIFace == __x.get();
	}
	/**
	 * Returns whether wrapped pointers are different.
	 */
	bool operator!= (const SInterface& __x) const NO_THROW
	{
		return m_pIFace != __x.get();
	}
	/**
	 * Returns whether the wrapped pointer is the same as an unwrapped pointer.
	 */
	bool operator== (const IUnknown* __p) const NO_THROW
	{
		return m_pIFace == __p;
	}
	/**
	 * Returns whether the wrapped pointer is not the same as an unwrapped pointer.
	 */
	bool operator!= (const IUnknown* __p) const NO_THROW
	{
		return m_pIFace != __p;
	}
	/**
	 * Test if this pointer implements an interface.
	 * Uses the static type information provided by IID_Def.
	 */
	bool operator== (const IID& __iid) const NO_THROW
	{
		return _IID::implements(__iid);
	}
	/**
	 * Test if this pointer does not implement an interface.
	 * Uses the static type information provided by IID_Def.
	 */
	bool operator!= (const IID& __iid) const NO_THROW
	{
		return !_IID::implements(__iid);
	}
	/**
	 * Automatically convert to the wrapped pointer type.
	 * FIXME: This has the potential to lead to leaks.
	 * On the other hand, it's nicer than typing .get() all the time.
	 * For now I'll leave it available and hope for the best.
	 */
	operator _IFace* () const NO_THROW
	{
		return m_pIFace;
	}
	/**
	 * Access a member of the interface.
	 */
	_IFace* operator->() const THROW_IFNULL
	{
#ifdef IFACE_NULLSAFE
		if (!m_pIFace)
			throw null_pointer();
#endif
		return m_pIFace;
	}
	/**
	 * Manual access to the wrapped pointer.
	 */
	_IFace* get() const NO_THROW
	{
		return m_pIFace;
	}
	/**
	 * Manually acquire an interface from a pointer.
	 * Does nothing if this pointer is already set.
	 */
	void set(IUnknown* __p) SPEC_THROW(no_interface)
	{
		if (!m_pIFace)
		{
			m_pIFace = _qi(__p);
		}
	}
	/**
	 * Acquire a new interface pointer.
	 * Releases the previous reference.
	 */
	void reset(_IFace* __p=NULL) NO_THROW
	{
		if (m_pIFace != __p)
		{
			if (m_pIFace)
				m_pIFace->Release();
			m_pIFace = __p;
		}
	}
	/**
	 * Return and abandon the reference to this pointer.
	 */
	_IFace* release() NO_THROW
	{
		_IFace* pTemp = m_pIFace;
		m_pIFace = NULL;
		return pTemp;
	}
protected:
	/**
	 * Change the pointer.
	 */
	void _set(_IFace* __p) NO_THROW
	{
		m_pIFace = __p;
	}
	_IFace* _qi(IUnknown* __p) SPEC_THROW(no_interface)
	{
		_IFace* pTemp;
		if (E_NOINTERFACE == __p->QueryInterface(_IID::iid(), reinterpret_cast<void**>(&pTemp)))
			throw no_interface(_IID::name());
		return pTemp;
	}
};


bool SService_is_null(IUnknown*);

/******************************************************
 * Helper class for script service interface pointers.
 *
 * Script services are acquired using IScriptMan::GetService
 * instead of QueryInterface. Additionally, there is no coercion
 * of script service interfaces. So this class only allows
 * copying of identical (wrapped or unwrapped) pointer types,
 * or acquisition from an IScriptMan interface.
 *
 * The management of references is the same as SInterface.
 */
template<class _IFace, typename _IID = IID_Def<_IFace> >
class SService : public SInterface<_IFace,_IID>
{
	typedef SInterface<_IFace,_IID> TInterface;
public:
	SService() NO_THROW
	{
	}
	SService(_IFace* __p) NO_THROW
		: SInterface<_IFace,_IID>(__p)
	{
	}
	SService(const SService& __x) NO_THROW
		: SInterface<_IFace,_IID>(__x)
	{
	}
	/**
	 * Create a script service pointer from a manager interface.
	 */
	explicit SService(IScriptMan* __sm) SPEC_THROW(no_interface)
	{
		set(__sm);
	}
	/**
	 * Create a script service pointer from a wrapped manager interface.
	 */
	explicit SService(const SInterface<IScriptMan>& __sm) SPEC_THROW(no_interface)
	{
		set(__sm.get());
	}

	SService& operator=(const SService& __x) NO_THROW
	{
		TInterface::operator=(__x);
		return *this;
	}
	SService& operator=(_IFace* __p) NO_THROW
	{
		TInterface::operator=(__p);
		return *this;
	}
	/**
	 * Acquire a script service pointer.
	 */
	void set(IScriptMan* pSM) SPEC_THROW(no_interface)
	{
		if (TInterface::operator!())
		{
			TInterface::_set(static_cast<_IFace*>(pSM->GetService(_IID::iid())));
			if (SService_is_null(TInterface::get()))
				throw no_interface(_IID::name());
		}
	}
private:
	template<class _ExtIFace>
	SService(const SService<_ExtIFace>&) NO_THROW
	{
	}
	template<class _ExtIFace>
	SService& operator=(const SService<_ExtIFace>&) NO_THROW
	{
	}
	SService(IUnknown*) SPEC_THROW(no_interface)
	{
	}
	SService& operator=(IUnknown*) SPEC_THROW(no_interface)
	{
	}
	void set(IUnknown* __p) SPEC_THROW(no_interface)
	{
	}
};

#ifdef __BORLANDC__
#pragma warn .inl
#endif

#endif

#endif // _LG_INTERFACE_H

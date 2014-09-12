#include "lg/config.h"
#include "lg/objstd.h"
#include "lg/interfaceimp.h"
#ifdef _MT
# include <windows.h>
#endif

uint cRefCnt::IncRef()
{
#ifdef _MT
	return InterlockedIncrement((LONG*)&m_iRef);
#else
	return ++m_iRef;
#endif
}

uint cRefCnt::DecRef()
{
	uint ref = m_iRef;
	if (ref > 0)
	{
#ifdef _MT
		ref = InterlockedDecrement((LONG*)&m_iRef);
#else
		m_iRef = --ref;
#endif
	}
	return ref;
}

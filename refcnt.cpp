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
#ifdef _MT
	uint ref = InterlockedDecrement((LONG*)&m_iRef);
	if (ref < 0)
		m_iRef = 0;
#else
	uint ref = m_iRef;
	if (ref <= 0) return -1;
	m_iRef = --ref;
#endif
	return ref;
}

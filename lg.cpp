#include "lg/lg.h"

#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <cmath>

extern IMalloc* g_pMalloc;

//////////////
// cMultiparm
//////////////

const cMultiParm cMultiParm::Undef;

cMultiParm::cMultiParm(const char* pszval)
{
	type = kMT_String;
	if (pszval && *pszval)
	{
		psz = reinterpret_cast<char*>(g_pMalloc->Alloc(::strlen(pszval)+1));
		strcpy(psz, pszval);
	}
	else
	{
		psz = reinterpret_cast<char*>(g_pMalloc->Alloc(1));
		psz[0] = '\0';
	}
}

cMultiParm::cMultiParm(const mxs_vector* pVectorval)
{
	type = kMT_Vector;
	pVector = reinterpret_cast<mxs_vector*>(g_pMalloc->Alloc(sizeof(mxs_vector)));
	if (pVectorval)
		*pVector = *pVectorval;
	else
		pVector->x = 0; pVector->y = 0; pVector->z = 0;
}

cMultiParm::cMultiParm(const mxs_vector& rVectorval)
{
	type = kMT_Vector;
	pVector = reinterpret_cast<mxs_vector*>(g_pMalloc->Alloc(sizeof(mxs_vector)));
	*pVector = rVectorval;
}

cMultiParm::cMultiParm(const sMultiParm& rcpy)
{
	switch (type = rcpy.type)
	{
	case kMT_Undef:
		psz = NULL;
		break;
	case kMT_Int:
		i = rcpy.i;
		break;
	case kMT_Float:
		f = rcpy.f;
		break;
	case kMT_String:
		if (rcpy.psz)
		{
			psz = reinterpret_cast<char*>(g_pMalloc->Alloc(strlen(rcpy.psz)+1));
			strcpy(psz, rcpy.psz);
		}
		else
		{
			psz = reinterpret_cast<char*>(g_pMalloc->Alloc(1));
			psz[0] = '\0';
		}
		break;
	case kMT_Vector:
		pVector = reinterpret_cast<mxs_vector*>(g_pMalloc->Alloc(sizeof(mxs_vector)));
		if (rcpy.pVector)
			pVector = rcpy.pVector;
		else
			pVector->x = 0; pVector->y = 0; pVector->z = 0;
		break;
	default:
		type = kMT_Undef;
		psz = NULL;
		break;
	}
}

cMultiParm::cMultiParm(const cScrStr& rcpy)
{
	type = kMT_String;
	if (!rcpy.IsEmpty())
	{
		psz = reinterpret_cast<char*>(g_pMalloc->Alloc(strlen(rcpy)+1));
		strcpy(psz, rcpy);
	}
	else
	{
		psz = reinterpret_cast<char*>(g_pMalloc->Alloc(1));
		psz[0] = '\0';
	}
}

void cMultiParm::Unset()
{
	if (psz != NULL && (type == kMT_String || type == kMT_Vector))
		g_pMalloc->Free(psz);
	type = kMT_Undef;
}

/*
void cMultiParm::Free()
{
	if (psz != NULL && (type == kMT_String || type == kMT_Vector))
		g_pMalloc->Free(psz);
	type = kMT_Undef;
}
*/

/*
cMultiParm& cMultiParm::operator= (int ival)
{
	if (psz != NULL && (type == kMT_String || type == kMT_Vector))
		g_pMalloc->Free(psz);
	i = ival;
	type = kMT_Int;
	return *this;
}

cMultiParm& cMultiParm::operator= (float fval)
{
	if (psz != NULL && (type == kMT_String || type == kMT_Vector))
		g_pMalloc->Free(psz);
	f = fval;
	type = kMT_Float;
	return *this;
}
*/

cMultiParm& cMultiParm::operator= (const char* pszval)
{
	char* pszNew;
	if (pszval && *pszval)
	{
		pszNew = reinterpret_cast<char*>(g_pMalloc->Alloc(strlen(pszval)+1));
		strcpy(pszNew, pszval);
	}
	else
	{
		pszNew = reinterpret_cast<char*>(g_pMalloc->Alloc(1));
		pszNew[0] = '\0';
	}
	Unset();
	psz = pszNew;
	type = kMT_String;
	return *this;
}

cMultiParm& cMultiParm::operator= (const mxs_vector* pVectorval)
{
	if (type == kMT_Vector && pVector != NULL)
	{
		if (pVectorval)
			*pVector = *pVectorval;
		else
			pVector->x = 0; pVector->y = 0; pVector->z = 0;
	}
	else
	{
		mxs_vector* pVectornew = reinterpret_cast<mxs_vector*>(g_pMalloc->Alloc(sizeof(mxs_vector)));
		if (pVectorval)
			*pVectornew = *pVectorval;
		else
			pVectornew->x = 0; pVectornew->y = 0; pVectornew->z = 0;
		Unset();
		pVector = pVectornew;
		type = kMT_Vector;
	}
	return *this;
}

cMultiParm& cMultiParm::operator= (const mxs_vector& rVectorval)
{
	if (type == kMT_Vector && pVector != NULL)
	{
		*pVector = rVectorval;
	}
	else
	{
		mxs_vector* pVectornew = reinterpret_cast<mxs_vector*>(g_pMalloc->Alloc(sizeof(mxs_vector)));
		*pVectornew = rVectorval;
		Unset();
		pVector = pVectornew;
		type = kMT_Vector;
	}
	return *this;
}

cMultiParm& cMultiParm::operator= (sMultiParm& mp)
{
	char* pNew;
	eMultiParmType newtype = mp.type;
	switch (newtype)
	{
	case kMT_String:
		pNew = reinterpret_cast<char*>(g_pMalloc->Alloc(strlen(mp.psz)+1));
		strcpy(pNew, mp.psz);
		break;
	case kMT_Vector:
	{
		mxs_vector* pVec = reinterpret_cast<mxs_vector*>(g_pMalloc->Alloc(sizeof(mxs_vector)));
		*pVec = *mp.pVector;
		pNew = reinterpret_cast<char*>(pVec);
		break;
	}
	default:
		pNew = mp.psz;
		break;
	}
	Unset();
	psz = pNew;
	type = newtype;
	return *this;
}

cMultiParm& cMultiParm::operator= (const cScrStr& str)
{
	char* pNew;
	if (!str.IsEmpty())
	{
		pNew = reinterpret_cast<char*>(g_pMalloc->Alloc(strlen(str)+1));
		strcpy(pNew, str);
	}
	else
	{
		pNew = reinterpret_cast<char*>(g_pMalloc->Alloc(1));
		pNew[0] = '\0';
	}
	Unset();
	psz = pNew;
	type = kMT_String;
	return *this;
}

cMultiParm::operator int () const
{
	switch (type)
	{
	  default:
	  case kMT_Undef:
		break;
	  case kMT_Int:
		return i;
	  case kMT_Float:
		return static_cast<int>(f);
	  case kMT_String:
		if (psz)
			return strtol(psz,NULL,10);
		break;
	  case kMT_Vector:
		break;
	}
	return 0;
}

cMultiParm::operator float () const
{
	switch (type)
	{
	  default:
	  case kMT_Undef:
		break;
	  case kMT_Int:
		return static_cast<float>(i);
	  case kMT_Float:
		return f;
	  case kMT_String:
		if (psz)
			return static_cast<float>(strtod(psz,NULL));
		break;
	  case kMT_Vector:
		break;
	}
	return 0.0;
}

cMultiParm::operator const char* () const
{
	static char pszNumber[64];
	switch (type)
	{
	  default:
	  case kMT_Undef:
		break;
	  case kMT_Int:
		_snprintf(pszNumber, 63, "%d", i);
		return pszNumber;
	  case kMT_Float:
		_snprintf(pszNumber, 63, "%0.12f", f);
		return pszNumber;
	  case kMT_Vector:
		_snprintf(pszNumber, 63, "(%0.6f,%0.6f,%0.6f)", pVector->x, pVector->y, pVector->z);
		return pszNumber;
	  case kMT_String:
		return psz;
	}
	return "";
}

cMultiParm::operator const mxs_vector* () const
{
	static mxs_vector vVector;
	switch (type)
	{
	  default:
	  case kMT_Undef:
		break;
	  case kMT_Int:
		break;
	  case kMT_Float:
		break;
	  case kMT_String:
		if (3 ==
			sscanf(psz, (psz[0]=='(')?"( %f, %f, %f )":"%f, %f, %f", &vVector.x, &vVector.y, &vVector.z))
			return &vVector;
		break;
	  case kMT_Vector:
		return pVector;
	}
	return NULL;
}

cMultiParm::operator bool () const
{
	switch (type)
	{
	  default:
	  case kMT_Undef:
		break;
	  case kMT_Int:
		return (i != 0);
	  case kMT_Float:
		return (f != 0.0);
	  case kMT_String:
		if (psz)
		{
			if (psz[0] == '0' || (psz[0]|0x20) == 'f')
				return false;
			if (psz[0] == '1' || (psz[0]|0x20) == 't')
				return true;
		}
		break;
	  case kMT_Vector:
		break;
	}
	return false;
}

bool cMultiParm::operator== (int rhs) const
{
	switch (type)
	{
	  default:
	  case kMT_Undef:
		return false;
	  case kMT_Int:
		return i == rhs;
	  case kMT_Float:
		return f == rhs;
	  case kMT_String:
	  {
		int lhs = psz ? strtol(psz,NULL,10) : 0;
		return lhs == rhs;
	  }
	  case kMT_Vector:
		return false;
	}
	return false;
}

bool cMultiParm::operator== (float rhs) const
{
	switch (type)
	{
	  default:
	  case kMT_Undef:
		return false;
	  case kMT_Int:
		return i == rhs;
	  case kMT_Float:
		return f == rhs;
	  case kMT_String:
	  {
		float lhs = psz ? static_cast<float>(strtod(psz,NULL)) : 0.0f;
		return lhs == rhs;
	  }
	  case kMT_Vector:
		return false;
	}
	return false;
}

bool cMultiParm::operator== (const char * rhs) const
{
	static char pszNumber[64];
	switch (type)
	{
	  default:
	  case kMT_Undef:
		return false;
	  case kMT_Int:
		_snprintf(pszNumber, 63, "%d", i);
		break;
	  case kMT_Float:
		_snprintf(pszNumber, 63, "%0.12f", f);
		break;
	  case kMT_Vector:
		_snprintf(pszNumber, 63, "(%0.6f,%0.6f,%0.6f)", pVector->x, pVector->y, pVector->z);
		break;
	  case kMT_String:
		return 0 == strcmp(psz, rhs);
	}
	return 0 == strcmp(pszNumber, rhs);
}

bool cMultiParm::operator== (const mxs_vector* rhs) const
{
	static mxs_vector vVector;
	switch (type)
	{
	  default:
	  case kMT_Undef:
	  case kMT_Int:
	  case kMT_Float:
		return false;
	  case kMT_String:
		if (3 !=
			sscanf(psz, (psz[0]=='(')?"( %f, %f, %f )":"%f, %f, %f", &vVector.x, &vVector.y, &vVector.z))
			return false;
		return 0 == memcmp(&vVector, rhs, sizeof(mxs_vector));
	  case kMT_Vector:
		return 0 == memcmp(pVector, rhs, sizeof(mxs_vector));
	}
	return false;
}

bool cMultiParm::operator== (const cMultiParm& rhs) const
{
	if (type == rhs.type)
	{
		switch (type)
		{
		  default:
		  case kMT_Undef:
			return true;
		  case kMT_Int:
			return i == rhs.i;
		  case kMT_Float:
			return f == rhs.f;
		  case kMT_String:
			if (psz == rhs.psz)
				return true;
			else if (psz && rhs.psz)
				return 0 == strcmp(psz, rhs.psz);
			return false;
		  case kMT_Vector:
			if (pVector == rhs.pVector)
				return true;
			else if (pVector && rhs.pVector)
				return 0 == memcmp(pVector, rhs.pVector, sizeof(mxs_vector));
			return false;
		}
	}
	switch (type)
	{
	  default:
	  case kMT_Undef:
		break;
	  case kMT_Int:
		return i == static_cast<int>(rhs);
	  case kMT_Float:
		return f == static_cast<float>(rhs);
	  case kMT_String:
		{
			const char* rsz = static_cast<const char*>(rhs);
			if (psz && rsz)
				return 0 == strcmp(psz, rsz);
			return false;
		}
	  case kMT_Vector:
		{
			const mxs_vector* rVector = static_cast<const mxs_vector*>(rhs);
			if (pVector && rVector)
				return 0 == memcmp(pVector, rVector, sizeof(mxs_vector));
			return false;
		}
	}
	return false;
}


////////////
// cScrStr
////////////
/* cScrStr is an immutable type. The pointer should be considered constant
 * and never freed. This is so string literals can easily and quickly be
 * cast to cScrStr. However, a few interface methods return a cScrStr on
 * the heap, which the caller has to free.
 */
const char* cScrStr::_ChNil = "";
const cScrStr cScrStr::Null;

/* Why does this constructor exist?
 * Although strings are supposed to be immutable, some pathological uses
 * ignore that. The default _ChNil value is not safe when a string may
 * be written outside the module that created it. This is one way to
 * handle the situation. The string is allocated so the external module
 * may safely use Free (assuming it uses the same heap).
 *
 * Alternately, you can set the pointer to NULL with cScrStr::MakeNull
 */
cScrStr::cScrStr(uint sz)
{
	char* psz = reinterpret_cast<char*>(g_pMalloc->Alloc(sz+1));
	m_pszData = psz;
	psz[0] = '\0';
}

void cScrStr::Free()
{
	if (m_pszData && m_pszData != _ChNil)
		g_pMalloc->Free(const_cast<char*>(m_pszData));
	m_pszData = _ChNil;
}

void cScrStr::Copy(const char* psz)
{
	if (!psz)
		m_pszData = _ChNil;
	else
	{
		m_pszData = reinterpret_cast<char*>(g_pMalloc->Alloc(strlen(psz)+1));
		strcpy(const_cast<char*>(m_pszData), psz);
	}
}

////////////
// cAnsiStr
////////////

const char* cAnsiStr::_ChNil = "";

cAnsiStr& cAnsiStr::operator= (const char* psz)
{
	Assign(strlen(psz), psz);
	return *this;
}

cAnsiStr& cAnsiStr::operator+= (const char* psz)
{
	Append(strlen(psz), psz);
	return *this;
}

cAnsiStr::~cAnsiStr()
{
	// The length check avoids trying to free the initial-empty string
	// set by the app, but because
	if (m_pchData != _ChNil && m_nAllocLength > 0)
		g_pMalloc->Free(m_pchData);
}

cAnsiStr::cAnsiStr()
{
	/*
	m_pchData = reinterpret_cast<char*>(g_pMalloc->Alloc(16));
	if (!m_pchData)
	{
		m_pchData = const_cast<char*>(_ChNil);
		m_nAllocLength = 0;
	}
	else
	{
		m_pchData[0] = '\0';
		m_nAllocLength = 16;
	}
	*/
	m_pchData = NULL;
	m_nAllocLength = 0;
	m_nDataLength = 0;
}

cAnsiStr::cAnsiStr(uint initlength)
{
	initlength = (initlength + 0x10) & ~0xF;
	m_pchData = reinterpret_cast<char*>(g_pMalloc->Alloc(initlength));
	if (!m_pchData)
	{
		m_pchData = NULL;
		m_nAllocLength = 0;
	}
	else
	{
		m_pchData[0] = '\0';
		m_nAllocLength = initlength;
	}
	m_nDataLength = 0;
}

cAnsiStr::cAnsiStr(char initchar)
{
	m_pchData = reinterpret_cast<char*>(g_pMalloc->Alloc(16));
	if (!m_pchData)
	{
		m_pchData = NULL;
		m_nAllocLength = 0;
		m_nDataLength = 0;
	}
	else
	{
		m_nAllocLength = 16;
		m_nDataLength = 1;
		m_pchData[0] = initchar;
		m_pchData[1] = '\0';
	}
}

cAnsiStr::cAnsiStr(const char *initdata)
{
	uint initlength = strlen(initdata);
	m_nDataLength = initlength;
	initlength = (initlength + 0x10) & ~0xF;
	m_pchData = reinterpret_cast<char*>(g_pMalloc->Alloc(initlength));
	if (!m_pchData)
	{
		m_pchData = NULL;
		m_nAllocLength = 0;
		m_nDataLength = 0;
	}
	else
	{
		m_nAllocLength = initlength;
		strncpy(m_pchData, initdata, m_nDataLength + 1);
	}
}

cAnsiStr::cAnsiStr(const char *initdata, uint initlength)
{
	m_nDataLength = initlength;
	initlength = (initlength + 0x10) & ~0xF;
	m_pchData = reinterpret_cast<char*>(g_pMalloc->Alloc(initlength));
	if (!m_pchData)
	{
		m_pchData = NULL;
		m_nAllocLength = 0;
		m_nDataLength = 0;
	}
	else
	{
		m_nAllocLength = initlength;
		memcpy(m_pchData, initdata, m_nDataLength);
		m_pchData[m_nDataLength] = '\0';
	}
}

cAnsiStr::cAnsiStr(const cAnsiStr &strCpy)
{
	uint initlength = strCpy.m_nDataLength;
	m_nDataLength = initlength;
	initlength = (initlength + 0x10) & ~0xF;
	m_pchData = reinterpret_cast<char*>(g_pMalloc->Alloc(initlength));
	if (!m_pchData)
	{
		m_pchData = NULL;
		m_nAllocLength = 0;
		m_nDataLength = 0;
	}
	else
	{
		memcpy(m_pchData, strCpy.m_pchData, m_nDataLength + 1);
		m_nAllocLength = initlength;
	}
}

cAnsiStr::cAnsiStr(const cScrStr &strCpy)
{
	uint initlength = strlen(static_cast<const char*>(strCpy));
	m_nDataLength = initlength;
	initlength = (initlength + 0x10) & ~0xF;
	m_pchData = reinterpret_cast<char*>(g_pMalloc->Alloc(initlength));
	if (!m_pchData)
	{
		m_pchData = NULL;
		m_nAllocLength = 0;
		m_nDataLength = 0;
	}
	else
	{
		m_nAllocLength = initlength;
		strncpy(m_pchData, static_cast<const char*>(strCpy), m_nDataLength + 1);
	}
}

void cAnsiStr::AllocBuffer(uint length)
{
	if (m_nAllocLength == 0)
	{
		length = (length + 0xF) & ~0xF;
		if (length == 0)
			length = 0x10;
		char* buf = reinterpret_cast<char*>(g_pMalloc->Alloc(length));
		if (buf)
		{
			m_pchData = buf;
			m_nAllocLength = length;
		}
		return;
	}
	if (m_nAllocLength > length)
	{
		// NO! Bad terminating null! No cookie!
		//m_pchData[length] = '\0';
		// Don't actually change m_nAllocLength,
		// we might need it later. And anyway, it's a lie.
		return;
	}
	else
	{
		if (length < m_nAllocLength * 2)
			length = m_nAllocLength * 2;
		else
			length = (length + 0xF) & ~0xF;
		char* buf = reinterpret_cast<char*>(g_pMalloc->Realloc(m_pchData, length));
		if (buf)
		{
			m_pchData = buf;
			m_nAllocLength = length;
		}
	}
}

char* cAnsiStr::AllocStr(uint nLength)
{
	return reinterpret_cast<char*>(g_pMalloc->Alloc(nLength+1));
}

char* cAnsiStr::ReallocStr(char* pchData, uint nLength)
{
	return reinterpret_cast<char*>(g_pMalloc->Realloc(pchData, nLength+1));
}

void cAnsiStr::FreeStr(char* pchData)
{
	if (pchData)
		g_pMalloc->Free(pchData);
}

void cAnsiStr::AllocCopy(cAnsiStr& rCpy, uint length, uint extra, uint start) const
{
	int nAllocLength = length + extra + 1;
	if (nAllocLength == 0)
	{
		rCpy = _ChNil;
		return;
	}
	rCpy.AllocBuffer(nAllocLength);
	if (rCpy.m_nAllocLength > length)
	{
		length = std::min(length, m_nDataLength);
		memcpy(rCpy.m_pchData, m_pchData + start, length);
		rCpy.m_pchData[length] = '\0';
		rCpy.m_nDataLength = length;
	}
}

void cAnsiStr::Attach(char* pchData, uint nLength, uint nAlloc)
{
	if (m_pchData == pchData)
		return;
	if (m_nAllocLength > 0)
	{
		g_pMalloc->Free(m_pchData);
	}
	if (!pchData)
	{
		m_pchData = const_cast<char*>(_ChNil);
		m_nDataLength = 0;
		m_nAllocLength = 0;
		return;
	}
	m_pchData = pchData;
	m_nDataLength = nLength;
	m_nAllocLength = nAlloc;
}

char* cAnsiStr::Detach(void)
{
	char* ret = m_pchData;
	if (ret == _ChNil)
	{
		ret = AllocStr(0);
		ret[0] = '\0';
	}
	m_pchData = const_cast<char*>(_ChNil);
	m_nDataLength = 0;
	m_nAllocLength = 0;
	return ret;
}

void cAnsiStr::BufDone(uint nLength, uint nAlloc)
{
	m_nDataLength = nLength;
	if (nAlloc > 0)
		m_nAllocLength = nAlloc;
}

void cAnsiStr::Assign(uint nLength, const char * pchData)
{
	if (nLength == 0)
	{
		if (m_nAllocLength > 0)
		{
			m_pchData[0] = '\0';
			m_nDataLength = 0;
		}
		return;
	}
	if (pchData && pchData != m_pchData)
	{
		AllocBuffer(nLength + 1);
		memcpy(m_pchData, pchData, nLength);
		m_pchData[nLength] = '\0';
		m_nDataLength = nLength;
	}
}

void cAnsiStr::Append(uint nLength, const char* pchData)
{
	if (nLength && pchData)
	{
		uint length = m_nDataLength + nLength;
		AllocBuffer(length + 1);
		memcpy(m_pchData + m_nDataLength, pchData, nLength);
		m_pchData[length] = '\0';
		m_nDataLength = length;
	}
}

void cAnsiStr::Append(char ch)
{
	AllocBuffer(m_nDataLength + 2);
	m_pchData[m_nDataLength] = ch;
	m_pchData[m_nDataLength + 1] = '\0';
	++m_nDataLength;
}

void cAnsiStr::ConcatCopy(uint len1, const char* data1, uint len2, const char* data2)
{
	uint nTotalLength = len1 + len2;
	if (nTotalLength == 0)
		return;
	AllocBuffer(nTotalLength + 1);
	memcpy(m_pchData, data1, len1);
	memcpy(m_pchData + len1, data2, len2);
	m_pchData[nTotalLength] = '\0';
	m_nDataLength = nTotalLength;
}

uint cAnsiStr::Insert(const char* str, uint start)
{
	if (!str || start > m_nDataLength)
		return 0;
	uint length = strlen(str);
	if (length == 0)
		return 0;
	AllocBuffer(m_nDataLength + length + 1);
	char* pos = m_pchData + start;
	if (start == m_nDataLength)
	{
		m_pchData[start + length] = '\0';
	}
	else
	{
		memmove(pos + length, pos, m_nDataLength - start + 1);
	}
	memcpy(pos, str, length);
	m_nDataLength += length;
	return length;
}

uint cAnsiStr::Insert(char ch, uint start)
{
	if (start > m_nDataLength)
		return 0;
	AllocBuffer(m_nDataLength + 2);
	if (start == m_nDataLength)
	{
		m_pchData[start] = ch;
		m_pchData[start+1] = '\0';
	}
	else
	{
		memmove(m_pchData + start + 1, m_pchData + start, m_nDataLength - start + 1);
		m_pchData[start] = ch;
	}
	m_nDataLength++;
	return 1;
}

void cAnsiStr::Remove(uint start, uint length)
{
	if (start >= m_nDataLength)
		return;
	uint end = start + length;
	if (end < m_nDataLength)
	{
		memmove(m_pchData + start, m_pchData + end, m_nDataLength - end + 1);
	}
	else
		m_pchData[start] = '\0';
	m_nDataLength -= length;
}

void cAnsiStr::Empty(void)
{
	if (m_nDataLength != 0)
	{
		m_pchData[0] = '\0';
		m_nDataLength = 0;
	}
}

uint cAnsiStr::Replace(const char* str, uint start, uint length)
{
	if (!str || start > m_nDataLength)
		return 0;
	uint end = start + length;
	uint str_length = strlen(str);
	AllocBuffer(m_nDataLength + str_length - length + 1);
	if (end < m_nDataLength)
	{
		memmove(m_pchData + start + str_length, m_pchData + end, m_nDataLength - end + 1);
		m_nDataLength += str_length - length;
	}
	else
	{
		m_pchData[start + str_length] = '\0';
		m_nDataLength = start + str_length;
	}
	memcpy(m_pchData + start, str, str_length);
	return str_length;
}

int cAnsiStr::Compare(uint nLen, const char *pchData) const
{
	int ret = memcmp(m_pchData, pchData, std::min(nLen, m_nDataLength));
	if (ret == 0)
	{
		int d = m_nDataLength - nLen;
		ret = (d) ? (d < 0) ? -1 : 1 : 0;
	}
	return ret;
}

void cAnsiStr::Trim(void)
{
	if (m_nDataLength == 0)
		return;
	char* start = m_pchData;
	while ((*start >= '\t' && *start <= '\r') || *start == ' ')
		++start;
	char* end = m_pchData + m_nDataLength;
	if (end == start)
	{
		m_pchData[0] = '\0';
		m_nDataLength = 0;
		return;
	}
	do
		--end;
	while ((*end >= '\t' && *end <= '\r') || *end == ' ');
	*++end = '\0';
	if (start != m_pchData)
		memmove(m_pchData, start, end - start + 1);
	m_nDataLength = end - start;
}

uint cAnsiStr::Find(const char *str, uint start) const
{
	if (!str || start > m_nDataLength)
		return MaxPos;
	char* p = strstr(m_pchData + start, str);
	return (p) ? p - m_pchData : MaxPos;
}

uint cAnsiStr::Find(char ch, uint start) const
{
	if (start > m_nDataLength)
		return MaxPos;
	char* p = reinterpret_cast<char*>(memchr(m_pchData + start, ch, m_nDataLength - start));
	return (p) ? p - m_pchData : MaxPos;
}

uint cAnsiStr::ReverseFind(char ch) const
{
	char* p = strrchr(m_pchData, ch);
	return (p) ? p - m_pchData : MaxPos;
}

uint cAnsiStr::FindOneOf(const char* chrs, uint start) const
{
	if (!chrs || start > m_nDataLength)
		return MaxPos;
	char* p = strpbrk(m_pchData + start, chrs);
	return (p) ? p - m_pchData : MaxPos;
}

uint cAnsiStr::SpanIncluding(const char* chrs, uint start) const
{
	if (!chrs || start > m_nDataLength)
		return 0;
	return strspn(m_pchData + start, chrs);
}

uint cAnsiStr::SpanExcluding(const char* chrs, uint start) const
{
	if (!chrs || start > m_nDataLength)
		return 0;
	return strcspn(m_pchData + start, chrs);
}

uint cAnsiStr::ReverseIncluding(const char* chrs, uint start) const
{
	if (!chrs || start == 0)
		return 0;
	char* pos = m_pchData + std::min(size_t(start),size_t(m_nDataLength)) - 1;
	char mask[256];
	memset(mask, 0, 256);
	for (const unsigned char* c = reinterpret_cast<const unsigned char*>(chrs); *c; ++c)
		mask[*c] = 1;
	char* spn = pos;
	while (spn >= m_pchData)
	{
		if (mask[*reinterpret_cast<unsigned char*>(spn)] == 0)
			break;
		--spn;
	}
	return pos - spn;
}

uint cAnsiStr::ReverseExcluding(const char* chrs, uint start) const
{
	if (!chrs || start == 0)
		return 0;
	char* pos = m_pchData + std::min(start,m_nDataLength) - 1;
	char mask[256];
	memset(mask, 0, 256);
	for (const unsigned char* c = reinterpret_cast<const unsigned char*>(chrs); *c; ++c)
		mask[*c] = 1;
	char* spn = pos;
	while (spn >= m_pchData)
	{
		if (mask[*reinterpret_cast<unsigned char*>(spn)] == 1)
			break;
		--spn;
	}
	return pos - spn;
}

// This function modifies the string in-place
// I'm unsure whether I should handle single-quotes as well
cAnsiStr& cAnsiStr::Quoted(eQuoteMode mode)
{
	switch (mode)
	{
		case kOff:
			break;
		case kDoubleQuotes:
		{
			AllocBuffer(m_nDataLength + (m_nDataLength >> 1));
			uint pos = 0;
			while ((pos = Find('"', pos)) != MaxPos)
			{
				Insert('"', pos);
				pos += 2;
			}
			Insert('"');
			Append('"');
			break;
		}
		case kEscapeQuotes:
		{
			AllocBuffer(m_nDataLength + (m_nDataLength >> 1));
			uint pos = 0;
			while ((pos = Find('"', pos)) != MaxPos)
			{
				Insert('\\', pos);
				pos += 2;
			}
			Insert('"');
			Append('"');
			break;
		}
		case kQuoteIfWhite:
		{
			if (FindOneOf(" \t\n\r") != MaxPos)
			{
				AllocBuffer(m_nDataLength + 3);
				Insert('"');
				Append('"');
			}
			break;
		}
		case kRemoveEmbeddedQuotes:
		{
			uint pos = 0;
			while ((pos = Find('"', pos)) != MaxPos)
			{
				Remove(pos, 1);
			}
			break;
		}
	}
	return *this;
}

void cAnsiStr::FmtStr(uint nLen, const char* pszFormat, ...)
{
	va_list va;
	AllocBuffer(nLen+1);
	va_start(va, pszFormat);
	if (m_nAllocLength <= nLen)
		nLen = m_nAllocLength-1;
	_vsnprintf(m_pchData, nLen+1, pszFormat, va);
	va_end(va);
	m_pchData[nLen] = '\0';
	return;
}

void cAnsiStr::FmtStr(const char* pszFormat, ...)
{
	va_list va;
	int nLen;
	va_start(va, pszFormat);
	nLen = _vsnprintf(NULL, 0, pszFormat, va);
	va_end(va);
	if (nLen >= 0)
	{
		AllocBuffer(nLen + 1);
		va_start(va, pszFormat);
		_vsnprintf(m_pchData, nLen+1, pszFormat, va);
		va_end(va);
		m_nDataLength = nLen;
		m_pchData[nLen] = '\0';
	}
	else
	{
		uint nTempLen = 1024;
		char *pTempBuf = new(std::nothrow) char[nTempLen];
		for (;;)
		{
			if (!pTempBuf)
				return;
			va_start(va, pszFormat);
			nLen = _vsnprintf(pTempBuf, nTempLen, pszFormat, va);
			va_end(va);
			if (nLen > 0)
				break;
			delete[] pTempBuf;
			nTempLen += 1024;
			pTempBuf = new(std::nothrow) char[nTempLen];
		}
		Assign(nLen, pTempBuf);
		delete[] pTempBuf;
	}
}

/*
void cAnsiStr::ReleaseBuffer(void);
void cAnsiStr::DoGrowBuffer(uint);
char* cAnsiStr::GetBuffer(uint);
*/

cAnsiStr operator + (const cAnsiStr& lStr, const cAnsiStr& rStr)
{
	cAnsiStr ret;
	ret.ConcatCopy(lStr.m_nDataLength, lStr.m_pchData, rStr.m_nDataLength, rStr.m_pchData);
	return ret;
}

cAnsiStr operator + (const cAnsiStr& lStr, const char* rStr)
{
	cAnsiStr ret;
	if (rStr == NULL)
	{
		ret = lStr;
		return ret;
	}
	ret.ConcatCopy(lStr.m_nDataLength, lStr.m_pchData, strlen(rStr), rStr);
	return ret;
}

cAnsiStr operator + (const char* lStr, const cAnsiStr& rStr)
{
	cAnsiStr ret;
	if (lStr == NULL)
	{
		ret = rStr;
		return ret;
	}
	ret.ConcatCopy(strlen(lStr), lStr, rStr.m_nDataLength, rStr.m_pchData);
	return ret;
}


///////////
// cScrVec
///////////
const cScrVec cScrVec::Zero;

/*
cScrVec cScrVec::operator+ (float g) const
{
	double u = sqrt((x*x) + (y*y) + (z*z));
	if (u <= epsilon) u = 1;
	return cScrVec(x+((x*g)/u),y+((y*g)/u),z+((z*g)/u));
}
cScrVec& cScrVec::operator+= (float g)
{
	double u = sqrt((x*x) + (y*y) + (z*z));
	if (u <= epsilon) u = 1;
	x += (x*g)/u;
	y += (y*g)/u;
	z += (z*g)/u;
	return *this;
}
cScrVec cScrVec::operator- (float g) const
{
	double u = sqrt((x*x) + (y*y) + (z*z));
	if (u <= epsilon) u = 1;
	return cScrVec(x-((x*g)/u),y-((y*g)/u),z-((z*g)/u));
}
cScrVec& cScrVec::operator-= (float g)
{
	double u = sqrt((x*x) + (y*y) + (z*z));
	if (u <= epsilon) u = 1;
	x -= (x*g)/u;
	y -= (y*g)/u;
	z -= (z*g)/u;
	return *this;
}
*/
cScrVec cScrVec::Normal() const
{
	double i = fabs(x), j = fabs(y), k = fabs(z);
	if (j > i)
	{
		double t = i;
		i = j;
		j = t;
	}
	if (k > i)
	{
		double t = i;
		i = k;
		k = t;
	}
	double v = i*i;
	if (v <= epsilon)
	{
		return cScrVec();
	}
	double u = sqrt((((j*j) + (k*k)) / v) + 1.0) * i;
	v = x/u;
	i = (fabs(v) < epsilon) ? 0.0f : static_cast<float>(v);
	v = y/u;
	j = (fabs(v) < epsilon) ? 0.0f : static_cast<float>(v);
	v = z/u;
	k = (fabs(v) < epsilon) ? 0.0f : static_cast<float>(v);
	return cScrVec(i,j,k);
}
void cScrVec::Normalize()
{
	cScrVec u = Normal();
	x = u.x;
	y = u.y;
	z = u.z;
}
double cScrVec::Magnitude() const
{
	return sqrt((x*x) + (y*y) + (z*z));
}
double cScrVec::MagSquared() const
{
	return (x*x) + (y*y) + (z*z);
}
double cScrVec::Dot(const mxs_vector& r) const
{
	return (x*r.x) + (y*r.y) + (z*r.z);
}
cScrVec cScrVec::Cross(const mxs_vector& r) const
{
	return cScrVec(
		(y*r.z) - (z*r.y),
		(z*r.x) - (x*r.z),
		(x*r.y) - (y*r.x)
	);
}
double cScrVec::Distance(const mxs_vector& r) const
{
	double i = r.x - x;
	double j = r.y - y;
	double k = r.z - z;
	return sqrt((i*i) + (j*j) + (k*k));
}


/////////////////
// cDynArrayBase
/////////////////
void cDynArrayBase::_resize(void **p, uint sz, uint c) SPEC_THROW(std::bad_alloc)
{
	void* d = *p;
	if (c != 0)
	{
		if (d != NULL)
			d = g_pMalloc->Realloc(d, sz * c);
		else
			d = g_pMalloc->Alloc(sz * c);
		if (d == NULL)
			throw std::bad_alloc();
	}
	else
		if (d != 0)
		{
			g_pMalloc->Free(d);
			d = NULL;
		}
	*p = d;
}

cDynArrayBase::~cDynArrayBase()
{
	if (m_data != NULL)
		g_pMalloc->Free(m_data);
}

bool SService_is_null(IUnknown* __p)
{
	void* pTemp;
	if (E_NOINTERFACE != __p->QueryInterface(IID_INullScriptService, &pTemp))
	{
		reinterpret_cast<IUnknown*>(pTemp)->Release();
		return true;
	}
	return false;
}


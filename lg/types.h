/**********************
 * LGS Types
 */

#ifndef _LG_TYPES_H
#define _LG_TYPES_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>

class cMultiParm;


struct true_bool
{
	Bool f;

	true_bool() : f(0) { }
	true_bool(Bool v) : f(v) { }
	true_bool(bool v) : f(v) { }

	true_bool& operator= (int v) { f = v; return *this; }
	true_bool& operator= (Bool v) { f = v; return *this; }
	true_bool& operator= (bool v) { f = v; return *this; }

	operator int () const { return (f) ? 1 : 0; }
	operator bool () const { return f != 0; }
	operator Bool () const { return f; }

	bool operator== (const true_bool& v) const { return (f) ? (v.f != 0) : (v.f == 0); }
	bool operator!= (const true_bool& v) const { return (f) ? (v.f == 0) : (v.f != 0); }
	bool operator== (Bool v) const { return (f) ? (v != 0) : (v == 0); }
	bool operator!= (Bool v) const { return (f) ? (v == 0) : (v != 0); }
	bool operator== (bool v) const { return (f) ? v : !v; }
	bool operator!= (bool v) const { return (f) ? !v : v; }
	bool operator! () const { return f == 0; }
};

struct mxs_vector
{
	float x, y, z;
};

struct mxs_angvec
{
	unsigned short x, y, z;
};

#define MXS_ANG2RAD(a)	(((float)(a) * M_PI) / 32768.0f)
#define MXS_RAD2ANG(r)	((unsigned short)(((float)(r) * 32768.0f) / M_PI))
#define MXS_ANG2DEG(a)	(((float)((long)(a) * 180)) / 32768.0f)
#define MXS_DEG2ANG(d)	((unsigned short)(((float)(d) * 32768.0f) / 180.0f))
#define MXS_A2D(a)		(((long)(a) * 180) / 32768)
#define MXS_D2A(d)		((unsigned short)(((long)(d) * 32768) / 180))

class cScrVec : public mxs_vector
{
public:
	cScrVec()
		{ x=0; y=0; z=0; }
	cScrVec(float i, float j, float k)
		{ x=i; y=j; z=k; }
	cScrVec(double i, double j, double k)
		{ x=(float)i; y=(float)j; z=(float)k; }
	cScrVec(int i, int j, int k)
		{ x=(float)i; y=(float)j; z=(float)k; }
	cScrVec(const mxs_vector& rV)
		{ x=rV.x; y=rV.y; z=rV.z; }
	cScrVec(const mxs_vector* pV)
		{ if (pV) { x=pV->x; y=pV->y; z=pV->z; } else { x=0; y=0; z=0; } }
	operator bool () const
		{ return x!=0 || y!=0 || z!=0; }
	bool operator! () const
		{ return x==0 && y==0 && z==0; }
	cScrVec& operator= (const mxs_vector& v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	}
	cScrVec operator+ (const mxs_vector& r) const
	{
		return cScrVec(x+r.x, y+r.y, z+r.z);
	}
	cScrVec& operator+= (const mxs_vector& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	}
	cScrVec operator- (const mxs_vector& r) const
	{
		return cScrVec(x-r.x, y-r.y, z-r.z);
	}
	cScrVec& operator-= (const mxs_vector& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
	cScrVec operator- () const
	{
		return cScrVec(-x,-y,-z);
	}
	cScrVec operator* (const mxs_vector& r) const
	{
		return cScrVec(x*r.x, y*r.y, z*r.z);
	}
	cScrVec operator* (float g) const
	{
		return cScrVec(x*g, y*g, z*g);
	}
	cScrVec operator* (double g) const
	{
		return cScrVec(x*g, y*g, z*g);
	}
	cScrVec& operator*= (const mxs_vector& r)
	{
		x *= r.x;
		y *= r.y;
		z *= r.z;
		return *this;
	}
	cScrVec& operator*= (float g)
	{
		x *= g;
		y *= g;
		z *= g;
		return *this;
	}
	cScrVec& operator*= (double g)
	{
		x = (float)(x * g);
		y = (float)(y * g);
		z = (float)(z * g);
		return *this;
	}
	cScrVec operator/ (const mxs_vector& r) const
	{
		return cScrVec(x/r.x, y/r.y, z/r.z);
	}
	cScrVec operator/ (float g) const
	{
		return cScrVec(x/g, y/g, z/g);
	}
	cScrVec operator/ (double g) const
	{
		return cScrVec(x/g, y/g, z/g);
	}
	cScrVec& operator/= (const mxs_vector& r)
	{
		x /= r.x;
		y /= r.y;
		z /= r.z;
		return *this;
	}
	cScrVec& operator/= (float g)
	{
		x /= g;
		y /= g;
		z /= g;
		return *this;
	}
	cScrVec& operator/= (double g)
	{
		x = (float)(x / g);
		y = (float)(y / g);
		z = (float)(z / g);
		return *this;
	}
	void Adjust(float g)
	{
		x += g;
		y += g;
		z += g;
	}
	void Adjust(double g)
	{
		x = (float)(x + g);
		y = (float)(y + g);
		z = (float)(z + g);
	}
	cScrVec Normal() const;
	void Normalize();
	double Magnitude() const;
	double MagSquared() const;
	double Dot(const mxs_vector& r) const;
	cScrVec Cross(const mxs_vector& r) const;
	double Distance(const mxs_vector& r) const;
	static constexpr float epsilon = 0.00001f;
	static const cScrVec Zero;
};


// A cScrStr should _never_ be NULL.
class cScrStr
{
	const char* m_pszData;

	static const char* _ChNil;
public:
	cScrStr () : m_pszData(_ChNil)
		{ }
	cScrStr (const char* psz)
		{ m_pszData = IF_NOT(psz, _ChNil); }
	cScrStr (uint sz);

	cScrStr& operator = (const char* psz)
		{ m_pszData = IF_NOT(psz, _ChNil); return *this;}

	operator const char* () const
		{ return m_pszData; }

	// Normally, a cScrStr should be considered const
	// In a few cases, you may need to do this, however.
	// No checking is performed, so be absolutely sure when you call this.
	void Free();
	void Copy(const char* psz);
	// Set the string pointer to NULL before using it as
	// an output parameter.
	void MakeNull()
		{ m_pszData = NULL; }

	Bool IsEmpty(void) const
		{ return *m_pszData == 0; }

	static const cScrStr Null;
};

class cAnsiStr
{
	char*	m_pchData;
	uint	m_nDataLength;
	uint	m_nAllocLength;

	static const char* _ChNil;

public:
	~cAnsiStr();
	cAnsiStr();
	cAnsiStr(uint);
	cAnsiStr(const char *);
	cAnsiStr(char);
	cAnsiStr(const char *, uint);
	cAnsiStr(const cAnsiStr &);
	cAnsiStr(const cScrStr &);

	operator const char* () const
		{ return IF_NOT(m_pchData, _ChNil); }

	cAnsiStr& operator= (const cAnsiStr& rCpy)
		{ Assign(rCpy.m_nDataLength, rCpy.m_pchData); return *this; }
	cAnsiStr& operator= (const char* psz);
	cAnsiStr& operator= (const cScrStr& rCpy)
		{ return *this = static_cast<const char*>(rCpy); }
	cAnsiStr& operator+= (const cAnsiStr& rCat)
		{ Append(rCat.m_nDataLength, rCat.m_pchData); return *this; }
	cAnsiStr& operator+= (const char* psz);
	cAnsiStr& operator+= (const cScrStr& rCat)
		{ return *this += static_cast<const char*>(rCat); }

	friend cAnsiStr operator+ (const cAnsiStr&, const cAnsiStr&);
	friend cAnsiStr operator+ (const cAnsiStr&, const char*);
	friend cAnsiStr operator+ (const char*, const cAnsiStr&);

	char* AllocStr(uint);
	char* ReallocStr(char*, uint);
	void FreeStr(char*);
	void AllocBuffer(uint);

	void Attach(char*, uint, uint);
	char* Detach(void);
	void BufDone(uint nLength, uint nAlloc);

	// Creates a new string with an allocated buffer of length + extra
	// and copies length characters from us beginning at start.
	void AllocCopy(cAnsiStr&, uint length, uint extra, uint start) const;

	void Assign(uint, const char *);
	void Append(uint, const char *);
	void Append(char);
	void ConcatCopy(uint, const char*, uint, const char*);

	uint Insert(const char *, uint pos = 0);
	uint Insert(char, uint pos = 0);
	void Remove(uint pos, uint length);
	uint Replace(const char *, uint pos, uint length);
	void Empty(void);
	void Trim(void);

	uint GetLength(void) const
		{ return m_nDataLength; }
	bool IsEmpty(void) const
		{ return m_nDataLength == 0; }
	bool IsInitialEmpty(void) const
		{ return !m_pchData || m_pchData == _ChNil; }
	operator bool () const
		{ return !IsEmpty(); }
	bool operator! () const
		{ return IsEmpty(); }

	static const uint MaxPos = uint(-1);

	char GetAt(uint pos) const
		{ return (pos < m_nDataLength) ? m_pchData[pos] : '\0'; }
	char SetAt(uint pos, char ch)
		{ return (pos < m_nDataLength) ? m_pchData[pos] = ch : '\0'; }
	char operator [] (uint pos) const
		{ return m_pchData[pos]; }

	int Compare(uint, const char *) const;
	int Compare(const cAnsiStr& rStr) const
		{ return Compare(rStr.m_nDataLength, rStr.m_pchData); }
	int Compare(const char *pchData) const
		{ return Compare(strlen(pchData) + 1, pchData); }

	uint Find(const char *, uint start = 0) const;
	uint Find(char, uint start = 0) const;
	uint ReverseFind(char) const;
	uint FindOneOf(const char*, uint start = 0) const;

	uint SpanIncluding(const char*, uint start = 0) const;
	uint SpanExcluding(const char*, uint start = 0) const;
	uint ReverseIncluding(const char*, uint start = MaxPos) const;
	uint ReverseExcluding(const char*, uint start = MaxPos) const;

	enum eQuoteMode
	{
		kOff,
		kDoubleQuotes,
		kEscapeQuotes,
		kQuoteIfWhite,
		kRemoveEmbeddedQuotes
	};

	cAnsiStr& Quoted(eQuoteMode);
	void FmtStr(uint, const char*, ...);
	void FmtStr(const char*, ...);
};

cAnsiStr operator+ (const cAnsiStr&, const cAnsiStr&);
cAnsiStr operator+ (const cAnsiStr&, const char*);
cAnsiStr operator+ (const char*, const cAnsiStr&);
inline bool operator == (const cAnsiStr& lStr, const cAnsiStr& rStr)
	{ return lStr.Compare(rStr) == 0; }
inline bool operator == (const cAnsiStr& lStr, const char *rStr)
	{ return lStr.Compare(strlen(rStr) + 1, rStr) == 0; }
inline bool operator != (const cAnsiStr& lStr, const cAnsiStr& rStr)
	{ return lStr.Compare(rStr) != 0; }
inline bool operator != (const cAnsiStr& lStr, const char *rStr)
	{ return lStr.Compare(strlen(rStr) + 1, rStr) != 0; }

/*
	SetAt...
	Compare...
	CompareNoCase...
	Collate...
	Mid...
	MakeUpper...
	MakeLower...
	MakeReverse...
	void FmtStr(unsigned int, const char*, ...);
	void FmtStr(const char*, ...);
	void FmtStr(unsigned int, unsigned short, ...);
	void FmtStr(unsigned short, ...);
	char* GetBuffer(int);
	void ReleaseBuffer(void);
	GetBufferSetLength...
	BufIn
	BufOut
	BufInOut
not really sure why we need this
	void DoGrowBuffer(int);
	int ToStream(class cOStore&) const;
	int FromStream(class cIStore&);
	int LoadString(unsigned short);
*/


// TODO: Make these classes use IObjectSystem/ILinkManager
class object
{
public:
	object (int iId = 0) : id(iId) { }
	object& operator= (int i)
		{ id = i; return *this; }
	/*
	object (const char *psz);
	const char* Name();
	*/
	operator int () const
		{ return id; }
	operator bool () const
		{ return id != 0; }
	bool operator! () const
		{ return id == 0; }
	bool operator== (const object& o)
		{ return id == o.id; }
	bool operator== (int i)
		{ return id == i; }
	bool operator!= (const object& o)
		{ return id != o.id; }
	bool operator!= (int i)
		{ return id != i; }
	bool operator< (const object& o) const
		{return id < o.id; }
	int id;
};


// Link IDs are ffffffffffffttttiiiiiiiiiiiiiiii
// f - flavor, i - ID, t - if either object is concrete
#define LINKID_TO_LINKKIND(l)	((long)(l)>>20)
#define LINKID_MASK(l)		((long)(l)&((1<<20)-1))
#define LINKID_MAKE(f,i)	(((long)(f)<<20)|((long)(i)&((1<<20)-1)))

class link
{
public:
	link (long i = 0) : id(i) { }
	link& operator= (long i)
		{ id = i; return *this; }
	/*
	object To();
	object From();
	void* Data();
	cMultiParm* GetData (cMultiParm&, const char * field);
	void SetData (const char *, cMultiParm &);
	*/
	operator long () const
		{ return id; }
	operator bool () const
		{ return id != 0; }
	bool operator! () const
		{ return id == 0; }
	bool operator== (long i) const
		{ return id == i; }
	bool operator== (const link& l) const
		{ return id == l.id; }
	bool operator!= (long i) const
		{ return id != i; }
	bool operator!= (const link& l) const
		{ return id != l.id; }
	bool operator< (const link& l) const
		{ return id < l.id; }
	link operator- () const
		{ return link(LINKID_MAKE(-LINKID_TO_LINKKIND(id),id)); }
	long id;
};

class linkkind
{
public:
	linkkind (int iId = 0) : id(iId) { }
	linkkind (const link& l) : id(LINKID_TO_LINKKIND(l.id)) { }
	linkkind& operator= (int iId)
		{ id = iId; return *this; }
	/*
	linkkind (const char *psz);
	operator const char* () const;
	*/
	operator long () const
		{ return id; }
	operator short () const
		{ return (short)id; }
	operator int () const
		{ return (int)id; }
	operator bool () const
		{ return id != 0; }
	bool operator! () const
		{ return id == 0; }
	bool operator== (long l)
		{ return id == l; }
	bool operator== (const linkkind& f)
		{ return id == f.id; }
	bool operator!= (long l)
		{ return id != l; }
	bool operator!= (const linkkind& f)
		{ return id != f.id; }
	bool operator< (const linkkind& f) const
		{ return id < f.id; }
	linkkind operator- () const
		{ return linkkind(-id); }
	long id;
};

interface ILinkQuery;

struct sLink
{
	object   source;
	object   dest;
	linkkind flavor;
};

class linkset
{
public:
	/*
	linkset(object from, object to, linkkind flavor);
	*/
	inline linkset& operator=(ILinkQuery* __q);
	linkset() : query(NULL) { }
	linkset(ILinkQuery* __q) : query(__q) { }
	inline ~linkset();
	inline link Link() const;
	inline void NextLink();
	inline bool AnyLinksLeft() const;
	inline void* Data() const;
	inline sLink Get() const;

	ILinkQuery* query;
private:
	// Prevent copying.
	linkset(const linkset&) { }
	linkset& operator= (const linkset&) { return *this; }
};

class reaction_kind
{
public:
	reaction_kind (long iId = 0) : id(iId) { }
	reaction_kind& operator= (long iId)
		{ id = iId; return *this; }
	/*
	reaction_kind (const char* psz);
	operator const char* () const;
	*/
	operator long () const
		{ return id; }
	operator short () const
		{ return (short)id; }
	operator int () const
		{ return (int)id; }
	operator bool () const
		{ return id != 0; }
	bool operator! () const
		{ return id == 0; }
	bool operator== (long l)
		{ return id == l; }
	bool operator== (const reaction_kind& r)
		{ return id == r.id; }
	bool operator!= (long l)
		{ return id != l; }
	bool operator!= (const reaction_kind& r)
		{ return id != r.id; }
	bool operator< (const linkkind& f) const
		{ return id < f.id; }
	long id;
};


// Multi-parm type
enum eMultiParmType
{
	kMT_Undef,
	kMT_Int,
	kMT_Float,
	kMT_String,
	kMT_Vector,
	kMT_Max = 0xFFFFFFFF
};

struct sMultiParm
{
	union {
		int i;
		float  f;
		char*  psz;
		mxs_vector*  pVector;
		unsigned int b;
	};
	eMultiParmType type;
};

class cMultiParm : public sMultiParm
{
public:
	~cMultiParm()
		{ Unset(); }

	cMultiParm()
		{ psz = NULL; type = kMT_Undef; }
	cMultiParm(int ival)
		{ i = ival; type = kMT_Int; }
	cMultiParm(long ival)
		{ i = ival; type = kMT_Int; }
	cMultiParm(uint ival)
		{ i = ival; type = kMT_Int; }
	cMultiParm(ulong ival)
		{ i = ival; type = kMT_Int; }
	cMultiParm(short ival)
		{ i = ival; type = kMT_Int; }
	cMultiParm(object oval)
		{ i = oval; type = kMT_Int; }
	cMultiParm(float fval)
		{ f = fval; type = kMT_Float; }
	cMultiParm(double fval)
		{ f = (float)fval; type = kMT_Float; }
	cMultiParm(const char* pszval);
	cMultiParm(const mxs_vector* pVectorval);
	cMultiParm(const mxs_vector& rVectorval);
	cMultiParm(const sMultiParm& rcpy);
	cMultiParm(const cScrStr& rcpy);

	// Simple assignment methods.
	void Unset();
	void Set(int ival)
		{ Unset(); i = ival; type = kMT_Int; }
	void Set(float fval)
		{ Unset(); f = fval; type = kMT_Float; }
	void Set(char* pszval)
		{ if (psz != pszval) Unset(); psz = pszval; type = kMT_String; }
	void Set(mxs_vector* pVectorval)
		{ if (pVector != pVectorval) Unset();  pVector = pVectorval; type = kMT_Vector; }

	// Assignment will destroy a string or vector pointer.
	cMultiParm& operator= (int ival)
		{ Set(ival); return *this; }
	cMultiParm& operator= (long ival)
		{ Set(static_cast<int>(ival)); return *this; }
	cMultiParm& operator= (float fval)
		{ Set(fval); return *this; }
	cMultiParm& operator= (double fval)
		{ Set(static_cast<float>(fval)); return *this; }
	cMultiParm& operator= (const char* pszval);
	cMultiParm& operator= (const mxs_vector* pVectorval);
	cMultiParm& operator= (const mxs_vector& rVectorval);
	//cMultiParm& operator= (bool bval)
	//	{ Set(bval); return *this; }
	//cMultiParm& operator= (const true_bool& bval)
	//	{ Set(static_cast<bool>(bval)); return *this; }
	cMultiParm& operator= (sMultiParm& mp);
	cMultiParm& operator= (const cScrStr& str);

	operator int () const;
	operator long () const
		{ return static_cast<int>(*this); }
	operator uint () const
		{ return static_cast<int>(*this); }
	operator ulong () const
		{ return static_cast<int>(*this); }
	operator object () const
		{ return static_cast<int>(*this); }
	operator float () const;
	operator double () const
		{ return static_cast<float>(*this); }
	operator bool () const;
	// These pointers are constant, don't fsck with them.
	operator const char* () const;
	operator const mxs_vector* () const;

	bool operator== (int rhs) const;
	bool operator== (float rhs) const;
	bool operator== (const char * rhs) const;
	bool operator== (const mxs_vector* rhs) const;
	bool operator== (const cScrVec& rhs) const
		{ return operator==(static_cast<const mxs_vector*>(&rhs)); }
	bool operator== (const cMultiParm& rhs) const;

	// Explicit destructor. Use Unset instead.
	//void Free();

	static const cMultiParm Undef;
};


interface IScript;
typedef IScript* (__cdecl *ScriptFactoryProc)(const char*, int);

struct sScrClassDesc
{
	const char* pszModule;
	const char* pszClass;
	const char* pszBaseClass;
	ScriptFactoryProc pfnFactory;
};

enum eScrTraceAction {
	kNoAction,
	kBreak,
	kSpew,
	kScrTraceMax = 0xFFFF
};

LG_DECLARE_HANDLE(tScrIter);
LG_DECLARE_HANDLE(tScrTimer);

enum eScrTimedMsgKind {
	kSTM_OneShot,
	kSTM_Periodic
};

struct sScrDatumTag
{
	int  objId;
	const char *  pszClass;
	const char *  pszName;
};


enum eFieldType
{
	kFieldTypeInt = 0,
	kFieldTypeBoolean,
	kFieldTypeShortInt,
	kFieldTypeBitVector,
	kFieldTypeEnum,
	kFieldTypeString,
	kFieldTypeStringPtr,
	kFieldTypePtr,		// don't use this
	kFieldTypePoint,
	kFieldTypeVector,
	kFieldTypeFloat,
	kFieldTypeFixed,	// 16.16 bits (multiply by 65536)
	// Following are SS2/T2 only
	kFieldTypeFixVec,
	kFieldTypeDouble,
	kFieldTypeRGBA,
	kFieldTypeDoubleVec,
	kFieldTypeAng,		// 180.0 <-> 32768
	kFieldTypeAngVec
};

enum eStructFlags
{
	kStructFlagHidden = 1,
	kStructFlagReadOnly = 2,
	kFieldFlagUnsigned = 32,
	kFieldFlagBinary = 64
};

struct sFieldDesc
{
	char name[32];
	eFieldType type;
	ulong size;
	ulong offset;
	int  flags;
	int  min, max;
	int num_bits;
	const char* * bit_names;
};

struct sStructDesc
{
	char name[32];
	ulong size;
	int  flags;
	int  num_fields;
	sFieldDesc* fields;
};


struct sTraitDesc
{
	char name[32];
	int  flags;
};

enum eHierarchyEvent
{
	kHierarchyAdd = 0,
	kHierarchyRemove
};
struct sHierarchyMsg
{
	eHierarchyEvent event;
	int iSubjId;
	int iObjId;
};

// AI uses this
struct sSoundInfo
{
};

struct Location
{
	mxs_vector vec;
	short cell;
	short unused;
};

struct Position
{
	Location loc;
	mxs_angvec facing;
};

struct Point
{
	short x, y;
};

struct Rect
{
	short left, top, right, bottom;
};

#endif // _LG_TYPES_H

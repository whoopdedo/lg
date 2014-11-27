/**************************
 * portability macros
 */

#ifndef _LG_CONFIG_H
#define _LG_CONFIG_H

#if _MSC_VER > 1000
#pragma once
#endif

#if __cplusplus < 201103L && !defined(__GXX_EXPERIMENTAL_CXX0X__)
#define constexpr const
#endif

#ifdef _MSC_VER

// "__thiscall" is not, as I was led to believe, valid syntax.
// Just have to rely on it being the default.
#define __thiscall
#define _MSCOMPAT 1

// MSVC doesn't know what the hell a 'throw' function spec is

#define SPEC_THROW(x)	throw(...)
#define NO_THROW throw()

#else // !_MSC_VER

#ifndef __thiscall
#define __thiscall
#endif

#define SPEC_THROW(x)	throw(x)
#define NO_THROW throw()

#endif // _MSC_VER

#ifdef __GNUC__

#define IF_NOT(a,b)	((a)?:(b))

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#define _MSCOMPAT 1
#endif

#else // !__GNUC__

#ifndef __attribute__
#define __attribute__(x)
#endif

#define IF_NOT(a,b)	((a)?(a):(b))

#endif // !__GNUC__

#ifdef __BORLANDC__

#endif

#ifndef _MSCOMPAT
#define _MSCOMPAT 0
#endif

#endif // _LG_CONFIG_H

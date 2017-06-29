

#pragma once

#include <algorithm>
#include <cassert>
#include <cstring>

#ifdef _DEBUG
#define ASSERT(c) assert(c)
#else
#define ASSERT(c) if(c) {}
#endif

#if defined(__GNUC__) || (defined(_MSC_VER) && _MSC_VER >= 1400)
#define RESTRICT __restrict
#else
#define RESTRICT
#endif

#ifdef __GNUC__
#define UNUSED __attribute__((unused)) //make sure unused code won't get optimized away.
#else
#define UNUSED
#endif

/// Delete Pointer, Wrapper around delete, sets pointer to NULL afterwards(!).
#define DELETEP(p) if(p) { delete   p; p = 0; }

/// Delete Array, Wrapper around delete[], sets pointer to NULL afterwards(!).
#define DELETEA(p) if(p) { delete[] p; p = 0; }

/// Check if a given type is a class.
template<class T> struct isclass
{
    template<class C> static char test(void (C::*)(void));
    template<class C> static int test(...);
    enum
    {
        yes = sizeof(test<T>(0)) == 1 ? 1 : 0,
        no = yes^1
    };
};

#ifdef WIN32
/// Compare Strings, ignore case.
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#else
// adapt macros to OS specifications
#define __cdecl
#define _vsnprintf vsnprintf
#endif


inline char *copystring(char *d, const char *s, size_t len)
{
    size_t slen = std::min(strlen(s), len-1);
    memcpy(d, s, slen);
    d[slen] = 0;
    return d;
}
template<size_t N> inline char *copystring(char(&d)[N], const char *s) { return copystring(d, s, N); }

/// Compare c-strings using memcmp.
template<size_t N> inline bool matchstring(const char *s, size_t len, const char(&d)[N])
{
    return len == N-1 && !memcmp(s, d, N-1);
}

inline char *newstring(size_t l) { return new char[l+1]; }
inline char *newstring(const char *s, size_t l) { return copystring(newstring(l), s, l+1); }
inline char *newstring(const char *s) { size_t l = strlen(s); char *d = newstring(l); memcpy(d, s, l+1); return d; }


struct stringslice
{
    const char *str;
    int len;
    stringslice() {}
    stringslice(const char *str, int len) : str(str), len(len) {}
    stringslice(const char *str, const char *end) : str(str), len(int(end-str)) {}

    const char *end() const { return &str[len]; }
};

inline char *newstring(const stringslice &s) { return newstring(s.str, s.len); }
inline const char *stringptr(const char *s) { return s; }
inline const char *stringptr(const stringslice &s) { return s.str; }
inline int stringlen(const char *s) { return int(strlen(s)); }
inline int stringlen(const stringslice &s) { return s.len; }

inline char *copystring(char *d, const stringslice &s, size_t len)
{
    size_t slen = std::min(size_t(s.len), len-1);
    memcpy(d, s.str, slen);
    d[slen] = 0;
    return d;
}
template<size_t N> inline char *copystring(char(&d)[N], const stringslice &s) { return copystring(d, s, N); }


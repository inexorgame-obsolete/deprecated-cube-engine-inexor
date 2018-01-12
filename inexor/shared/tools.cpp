/// @file General tools, typedefines and generic definitions.

#include <stdarg.h>                           // for va_end, va_list, va_start

#include "inexor/shared/cube_formatting.hpp"  // for vformatstring
#include "inexor/shared/cube_types.hpp"       // for string, MAXSTRLEN

static string tmpstr[4];
static int tmpidx = 0;

char *tempformatstring(const char *fmt, ...)
{
    tmpidx = (tmpidx+1)%4;
    char *buf = tmpstr[tmpidx];    

    va_list v;
    va_start(v, fmt);
    vformatstring(buf, fmt, v, MAXSTRLEN);
    va_end(v);

    return buf;
}


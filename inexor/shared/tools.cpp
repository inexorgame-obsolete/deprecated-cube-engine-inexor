/// @file General tools, typedefines and generic definitions.

#include "inexor/shared/cube.hpp"
#ifndef WIN32
#include <unistd.h>
#endif

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


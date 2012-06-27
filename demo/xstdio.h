#ifndef __DEMO_XSTDIO_H__
#define __DEMO_XSTDIO_H__

#include <stdio.h>

#ifdef UNDER_TEST

int xfprintf(FILE *stream, const char *format, ...);

#else

#define xfprintf fprintf

#endif

#endif

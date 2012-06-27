#ifndef __DEMO_XSTDIO_H__
#define __DEMO_XSTDIO_H__

#include <stdio.h>

#ifdef UNDER_TEST

void STUB_xfprintf(int return_value);
void MOCK_xfprintf(FILE *stream, const char *format);
int UNDER_TEST_xfprintf(FILE *stream, const char *format, ...);
int xfprintf(FILE *stream, const char *format, ...);

#else

#define xfprintf fprintf

#endif

#endif

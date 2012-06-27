#ifndef __MOCKME_TEST_H__
#define __MOCKME_TEST_H__

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <mockme/cmockery.h>

#define MOCK(function, args...)\
	MOCK_ ## function(args)

#define N_MOCK(n, function, args...)\
	do {\
		int __i;\
		for(__i = 0; __i < n; ++__i)\
			MOCK_ ## function(args);\
	}\
	while (0)

#define STUB(function, args...)\
	STUB_ ## function(args)

#define N_STUB(n, function, args...)\
	do {\
		int __i;\
		for(__i = 0; __i < n; ++__i)\
			STUB_ ## function(args);\
	}\
	while (0)

#define CALL(function_call)\
	UNDER_TEST_ ## function_call

typedef UnitTest unit_test_t;

#endif

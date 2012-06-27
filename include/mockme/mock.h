#ifndef __MOCKME_MOCK_H__
#define __MOCKME_MOCK_H__

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <mockme/cmockery.h>

#define INPUT_VALUE(value)
#define INPUT_MEMORY(ptr, size)
#define INPUT_STRING(value)

#define __FIRST_ARG(x, args...)\
	x

#define DEFAULT_STUB(args...)\
	return __FIRST_ARG(args)

#endif

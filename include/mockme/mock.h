#ifndef __MOCKME_MOCK_H__
#define __MOCKME_MOCK_H__

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <mockme/cmockery.h>

#if !defined(MOCK_ME)

#define INPUT_VALUE(value)			do { (void)value; } while(0)
#define INPUT_MEMORY(ptr, size)		do { (void)ptr; (void)size; } while(0)
#define INPUT_STRING(value)         do { (void)value; } while(0)

#define __FIRST_ARG(x, args...)\
	x

#define DEFAULT_STUB(args...)\
	return __FIRST_ARG(args)

#endif

#endif

#ifndef __MOCKME_MOCK_H__
#define __MOCKME_MOCK_H__

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <mockme/cmockery.h>

#if !defined(MOCK_ME)

#define INPUT_VALUE(value)\
	do { (void)value; } while(0)  					// avoid your IDE to go all "variable not used"

#define INPUT_MEMORY(ptr, size)\
	do { (void)ptr; (void)size; } while(0)          // avoid your IDE to go all "variable not used"

#define INPUT_STRING(value)\
	do { (void)value; } while(0)					// avoid your IDE to go all "variable not used"

#define __HAPPY_RETURN_VALUE(value, args...)\
	value

#define RETURN(args...)\
	return __HAPPY_RETURN_VALUE(args)				// avoid your IDE to go all "missing return statement"

#endif

#endif

#ifndef __MOCKME_MOCK_H__
#define __MOCKME_MOCK_H__

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <mockme/cmockery.h>

#if !defined(MOCK_ME)

#define INPUT_VALUE(name)\
	(void)name									// avoid your IDE to go all "variable not used"

#define INPUT_MEMORY(name, size)\
	(void)name									// avoid your IDE to go all "variable not used"

#define INPUT_STRING(name)\
	(void)name									// avoid your IDE to go all "variable not used"

#define OUTPUT_VALUE(name, default_value)\
	(void)name									// avoid your IDE to go all "variable not used"

#define __HAPPY_RETURN_VALUE(value, args...)\
	value

#define RETURN(args...)\
	return __HAPPY_RETURN_VALUE(args)			// avoid your IDE to go all "missing return statement"

#endif

#endif

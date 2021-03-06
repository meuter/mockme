#ifndef __MOCKME_MOCK_H__
#define __MOCKME_MOCK_H__

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <mockme/cmockery.h>

#if !defined(MOCK_ME)

	// These macros will be replaced by actual cmockery code by mockme

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





#define __VA_N_ARGS__(args...) \
		 __VA_COUNT_ARGS__(64,##args,63,62,61,60,  \
		 59,58,57,56,55,54,53,52,51,50, \
		 49,48,47,46,45,44,43,42,41,40, \
		 39,38,37,36,35,34,33,32,31,30, \
		 29,28,27,26,25,24,23,22,21,20, \
		 19,18,17,16,15,14,13,12,11,10, \
		 9,8,7,6,5,4,3,2,1,0)

#define __VA_COUNT_ARGS__(_0,\
		 _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
		 _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
		 _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
		 _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
		 _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
		 _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
		 _61,_62,_63,N,...) N

#define INPUT_VALUES_AND_RETURN_1(x, args...)\
	RETURN(x)

#define INPUT_VALUES_AND_RETURN_2(x, args...)\
	INPUT_VALUE(x);\
	INPUT_VALUES_AND_RETURN_1(args)

#define INPUT_VALUES_AND_RETURN_3(x, args...)\
	INPUT_VALUE(x);\
	INPUT_VALUES_AND_RETURN_2(args)

#define INPUT_VALUES_AND_RETURN_4(x, args...)\
	INPUT_VALUE(x);\
	INPUT_VALUES_AND_RETURN_3(args)

#define INPUT_VALUES_AND_RETURN_5(x, args...)\
	INPUT_VALUE(x);\
	INPUT_VALUES_AND_RETURN_4(args)

#define INPUT_VALUES_AND_RETURN_6(x, args...)\
	INPUT_VALUE(x);\
	INPUT_VALUES_AND_RETURN_5(args)

#define INPUT_VALUES_AND_RETURN_7(x, args...)\
	INPUT_VALUE(x);\
	INPUT_VALUES_AND_RETURN_6(args)

#define INPUT_VALUES_AND_RETURN_8(x, args...)\
	INPUT_VALUE(x);\
	INPUT_VALUES_AND_RETURN_7(args)

#define INPUT_VALUES_AND_RETURN_9(x, args...)\
	INPUT_VALUE(x);\
	INPUT_VALUES_AND_RETURN_8(args)

#define INPUT_VALUES_AND_RETURN_10(x, args...)\
	INPUT_VALUE(x);\
	INPUT_VALUES_AND_RETURN_1(args)

#define CONCATENATE(a,b) a ## b

#define INPUT_VALUES_AND_RETURN_N(N, args...)\
	CONCATENATE(INPUT_VALUES_AND_RETURN_, N)(args)

#define INPUT_VALUES_AND_RETURN(args...)\
	INPUT_VALUES_AND_RETURN_N( __VA_N_ARGS__(args), args)




#endif

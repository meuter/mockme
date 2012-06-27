#ifndef __MOCKME_UNDER_TEST_H__
#define __MOCKME_UNDER_TEST_H__

#define DECLARE_FUNCTION(return_type, name, args...)\
	void STUB_ ## name(return_type return_value);\
	void MOCK_ ## name(args);\
	return_type UNDER_TEST_ ## name(args);\
	return_type name(args)


#ifndef UNDER_TEST

	#define DEFINE_FUNCTION(return_type, name, args...)\
		return_type name(args)

#else


	#define DEFINE_FUNCTION(return_type, name, args...)\
		return_type UNDER_TEST_ ## name(args)

#endif

#endif




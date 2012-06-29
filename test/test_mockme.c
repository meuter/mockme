#include <mockme/mock.h>
#include <mockme/test.h>
#include <mockme/under_test.h>

/**********************************************************************************************************************/

DEFINE_FUNCTION(void, function_no_arg_to_return_value)
{
	return;
}

void function_no_arg_to_return_value()
{
	RETURN();
}

static void test__function_no_arg_to_return_value__can_be_called()
{
	function_no_arg_to_return_value();
}

static void test__function_no_arg_to_return_value__can_be_mocked()
{
	MOCK(function_no_arg_to_return_value);
	function_no_arg_to_return_value();
}

static void test__function_no_arg_to_return_value__can_be_stubbed()
{
	STUB(function_no_arg_to_return_value);
	function_no_arg_to_return_value();
}

/**********************************************************************************************************************/

DEFINE_FUNCTION(int, function_no_arg_int_return_value)
{
	return 42;
}

int function_no_arg_int_return_value()
{
	RETURN(42);
}

static void test__function_no_arg_int_return_value__can_be_called()
{
	assert_int_equal(function_no_arg_int_return_value(), 42);
}

static void test__function_no_arg_int_return_value__can_be_mocked()
{
	MOCK(function_no_arg_int_return_value);
	assert_int_equal(function_no_arg_int_return_value(), 42);
}

static void test__function_no_arg_int_return_value__can_be_stubbed()
{
	STUB(function_no_arg_int_return_value, 43);
	assert_int_equal(function_no_arg_int_return_value(), 43);
}

/**********************************************************************************************************************/

DEFINE_FUNCTION(void, function_input_value_no_return_value,
	int x
)
{
	(void)x;
	return;
}

void function_input_value_no_return_value(int x)
{
	INPUT_VALUE(x);
	RETURN();
}

static void test__function_input_value_no_return_value__can_be_called()
{
	function_input_value_no_return_value(15);
}

static void test__function_input_value_no_return_value__can_be_mocked()
{
	MOCK(function_input_value_no_return_value, 16);
	function_input_value_no_return_value(16);
}

static void test__function_input_value_no_return_value__can_be_stubbed()
{
	STUB(function_input_value_no_return_value);
	function_input_value_no_return_value(16);
}

/**********************************************************************************************************************/

DEFINE_FUNCTION(void, function_input_string_no_return_value,
	const char *s
)
{
	(void)s;
	return;
}

void function_input_string_no_return_value(const char *s)
{
	INPUT_STRING(s);
	RETURN();
}

static void test__function_input_string_no_return_value__can_be_called()
{
	function_input_string_no_return_value("test");
}

static void test__function_input_string_no_return_value__can_be_mocked()
{
	MOCK(function_input_string_no_return_value, "foo");
	function_input_string_no_return_value("foo");
}

static void test__function_input_string_no_return_value__can_be_stubbed()
{
	STUB(function_input_string_no_return_value);
	function_input_string_no_return_value("bar");
}

/**********************************************************************************************************************/

DEFINE_FUNCTION(int, function_input_value_int_return_value,
	int x
)
{
	(void)x;
	return x+1;
}

int function_input_value_int_return_value(int x)
{
	INPUT_VALUE(x);
	RETURN(x+1);
}

static void test__function_input_value_int_return_value__can_be_called()
{
	assert_int_equal(function_input_value_int_return_value(10), 11);
}

static void test__function_input_value_int_return_value__can_be_mocked()
{
	MOCK(function_input_value_int_return_value, 15);
	assert_int_equal(function_input_value_int_return_value(15), 16);
}

static void test__function_input_value_int_return_value__can_be_stubbed()
{
	STUB(function_input_value_int_return_value, 1515);
	assert_int_equal(function_input_value_int_return_value(10), 1515);
}

/**********************************************************************************************************************/

int main()
{
	unit_test_t all_tests[] =
	{
		unit_test(test__function_no_arg_to_return_value__can_be_called),
		unit_test(test__function_no_arg_to_return_value__can_be_mocked),
		unit_test(test__function_no_arg_to_return_value__can_be_stubbed),

		unit_test(test__function_no_arg_int_return_value__can_be_called),
		unit_test(test__function_no_arg_int_return_value__can_be_mocked),
		unit_test(test__function_no_arg_int_return_value__can_be_stubbed),

		unit_test(test__function_input_value_no_return_value__can_be_called),
		unit_test(test__function_input_value_no_return_value__can_be_mocked),
		unit_test(test__function_input_value_no_return_value__can_be_stubbed),

		unit_test(test__function_input_string_no_return_value__can_be_called),
		unit_test(test__function_input_string_no_return_value__can_be_mocked),
		unit_test(test__function_input_string_no_return_value__can_be_stubbed),

		unit_test(test__function_input_value_int_return_value__can_be_called),
		unit_test(test__function_input_value_int_return_value__can_be_mocked),
		unit_test(test__function_input_value_int_return_value__can_be_stubbed),

	};

	return run_tests(all_tests);
}

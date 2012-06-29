#include <mockme/mock.h>
#include <mockme/test.h>
#include <mockme/under_test.h>

#include <stdint.h>

/**********************************************************************************************************************/

DEFINE_FUNCTION(void, function_no_arg_to_return_value)
{
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
}

void function_input_string_no_return_value(const char *s)
{
	INPUT_STRING(s);
	RETURN();
}

static void test__function_input_string_no_return_value__can_be_called()
{
	function_input_string_no_return_value("bar");
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

DEFINE_FUNCTION(void, function_input_memory_fixed_size_no_return_value,
	uint8_t *p
)
{
	(void)p;
}

void function_input_memory_fixed_size_no_return_value(uint8_t *p)
{
	INPUT_MEMORY(p, 4);
	RETURN();
}

static void test__function_input_memory_fixed_size_no_return_value__can_be_called()
{
	uint8_t p[] = { 0x01, 0x02, 0x03, 0x04 };
	function_input_memory_fixed_size_no_return_value(p);
}

static void test__function_input_memory_fixed_size_no_return_value__can_be_mocked()
{
	uint8_t p[] = { 0x01, 0x02, 0x03, 0x04 };
	uint8_t expected_p[] = { 0x01, 0x02, 0x03, 0x04 };
	MOCK(function_input_memory_fixed_size_no_return_value, expected_p);
	function_input_memory_fixed_size_no_return_value(p);
}

static void test__function_input_memory_fixed_size_no_return_value__can_be_stubbed()
{
	uint8_t p[] = { 0x01, 0x02, 0x03, 0x04 };
	STUB(function_input_memory_fixed_size_no_return_value);
	function_input_memory_fixed_size_no_return_value(p);
}

/**********************************************************************************************************************/

DEFINE_FUNCTION(void, function_input_memory_and_size_fixed_size_no_return_value,
	uint8_t *p,
	size_t s
)
{
	(void)p;
	(void)s;
}

void function_input_memory_and_size_fixed_size_no_return_value(uint8_t *p, size_t s)
{
	INPUT_VALUE(s);
	INPUT_MEMORY(p, s);
	RETURN();
}

static void test__function_input_memory_and_size_fixed_size_no_return_value__can_be_called()
{
	uint8_t p[] = { 0x01, 0x02, 0x03 };
	function_input_memory_and_size_fixed_size_no_return_value(p, sizeof(p));
}

static void test__function_input_memory_and_size_fixed_size_no_return_value__can_be_mocked()
{
	uint8_t p[] = { 0x01, 0x02 };
	uint8_t expected_p[] = { 0x01, 0x02 };
	MOCK(function_input_memory_and_size_fixed_size_no_return_value, expected_p, sizeof(expected_p));
	function_input_memory_and_size_fixed_size_no_return_value(p, sizeof(p));
}

static void test__function_input_memory_and_size_fixed_size_no_return_value__can_be_stubbed()
{
	uint8_t test_buffer[] = { 0x01, 0x02, 0x03, 0x04 };
	STUB(function_input_memory_and_size_fixed_size_no_return_value);
	function_input_memory_and_size_fixed_size_no_return_value(test_buffer, sizeof(test_buffer));
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

DEFINE_FUNCTION(void, function_output_value_no_return_value,
	int *x
)
{
	(void)x;
}

void function_output_value_no_return_value(int *x)
{
	OUTPUT_VALUE(x, 42);
	RETURN();
}

static void test__function_output_value_no_return_value__can_be_called()
{
	int x;
	function_output_value_no_return_value(&x);
	assert_int_equal(x, 42);
}

static void test__function_output_value_no_return_value__can_be_mocked()
{
	int x;
	MOCK(function_output_value_no_return_value);
	function_output_value_no_return_value(&x);
	assert_int_equal(x, 42);
}

static void test__function_output_value_no_return_value__can_be_stubbed()
{
	int x;
	STUB(function_output_value_no_return_value, 43);
	function_output_value_no_return_value(&x);
	assert_int_equal(x, 43);
}

/**********************************************************************************************************************/

DEFINE_FUNCTION(int, function_that_does_a_bit_of_everything,
	uint8_t *p,
	size_t l,
	char *s,
	int *x
)
{
	(void)p;
	(void)l;
	(void)s;
	(void)x;
	return 1;
}

int function_that_does_a_bit_of_everything(uint8_t *p, size_t l, char *s, int *x)
{
	INPUT_VALUE(l);
	INPUT_MEMORY(p, l);
	INPUT_STRING(s);
	OUTPUT_VALUE(x, 42);
	RETURN(1);
}

static void test__function_that_does_a_bit_of_everything__can_be_called()
{
	int x;
	uint8_t p[] = { 0x01, 0x02 };
	assert_int_equal(function_that_does_a_bit_of_everything(p, sizeof(p), "bar", &x), 1);
	assert_int_equal(x, 42);
}

static void test__function_that_does_a_bit_of_everything__can_be_mocked()
{
	int x;
	uint8_t p[] = { 0x01, 0x02 };
	uint8_t expected_p[] = { 0x01, 0x02 };
	MOCK(function_that_does_a_bit_of_everything, expected_p, sizeof(expected_p), "foo");
	assert_int_equal(function_that_does_a_bit_of_everything(p, sizeof(p), "foo", &x), 1);
	assert_int_equal(x, 42);
}

static void test__function_that_does_a_bit_of_everything__can_be_stubbed()
{
	int x;
	uint8_t p[] = { 0x01, 0x02 };
	STUB(function_that_does_a_bit_of_everything, -1, 43);
	assert_int_equal(function_that_does_a_bit_of_everything(p, sizeof(p), "foo", &x), -1);
	assert_int_equal(x, 43);
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

		unit_test(test__function_input_memory_fixed_size_no_return_value__can_be_called),
		unit_test(test__function_input_memory_fixed_size_no_return_value__can_be_mocked),
		unit_test(test__function_input_memory_fixed_size_no_return_value__can_be_stubbed),

		unit_test(test__function_input_memory_and_size_fixed_size_no_return_value__can_be_called),
		unit_test(test__function_input_memory_and_size_fixed_size_no_return_value__can_be_mocked),
		unit_test(test__function_input_memory_and_size_fixed_size_no_return_value__can_be_stubbed),

		unit_test(test__function_input_value_int_return_value__can_be_called),
		unit_test(test__function_input_value_int_return_value__can_be_mocked),
		unit_test(test__function_input_value_int_return_value__can_be_stubbed),

		unit_test(test__function_output_value_no_return_value__can_be_called),
		unit_test(test__function_output_value_no_return_value__can_be_mocked),
		unit_test(test__function_output_value_no_return_value__can_be_stubbed),

		unit_test(test__function_that_does_a_bit_of_everything__can_be_called),
		unit_test(test__function_that_does_a_bit_of_everything__can_be_mocked),
		unit_test(test__function_that_does_a_bit_of_everything__can_be_stubbed),

	};

	return run_tests(all_tests);
}

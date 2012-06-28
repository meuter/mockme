#include <mockme/test.h>
#include <mockme/mock.h>

#include <stdlib.h>
#include "demo.h"

/**********************************************************************************************************************/

#define TEST_OUTPUT  ((FILE*)0x666)
#define TEST_BYTES   ((uint8_t *)"abcde")
#define TEST_SIZE    (5)

/**********************************************************************************************************************/

int print_as_ascii_hex(FILE *output, const uint8_t *bytes, const size_t size)
{
	INPUT_VALUE(output);
	INPUT_MEMORY(bytes, size);
	DEFAULT_STUB(0);
}

int xfprintf(FILE *stream, const char *format, ...)
{
	INPUT_VALUE(stream);
	INPUT_STRING(format);
	DEFAULT_STUB(1);
}

void print_prefix()
{
	DEFAULT_STUB();
}

const char *get_prefix()
{
	DEFAULT_STUB("> ");
}

/**********************************************************************************************************************/

static void test__print_prefix__calls_fprintf()
{
	MOCK(xfprintf, stdout, "%s");
	CALL(print_prefix());
}

/**********************************************************************************************************************/

static void test__print_as_scii_hex__print_prefix()
{
	MOCK(print_prefix);
	CALL(print_as_ascii_hex(TEST_OUTPUT, TEST_BYTES, TEST_SIZE));
}

static void test__print_as_ascii_hex__returns_0_on_success()
{
	assert_int_equal(0, CALL(print_as_ascii_hex(TEST_OUTPUT, TEST_BYTES, TEST_SIZE)));
}

static void test__print_as_ascii_hex__prints_all_bytes()
{
	N_MOCK(TEST_SIZE, xfprintf, TEST_OUTPUT, "%02X");
	CALL(print_as_ascii_hex(TEST_OUTPUT, TEST_BYTES, TEST_SIZE));
}

static void test__print_as_ascii_hex__returns_minus_1_if_fprintf_of_one_byte_fails()
{
	N_STUB(TEST_SIZE-1, xfprintf, 1);
	STUB(xfprintf, -1);
	assert_int_equal(-1, CALL(print_as_ascii_hex(TEST_OUTPUT, TEST_BYTES, TEST_SIZE)));
}

static void test__print_as_ascii_hex__prints_trailing_new_line()
{
	N_STUB(TEST_SIZE, xfprintf, 1);
	MOCK(xfprintf, TEST_OUTPUT, "\n");
	CALL(print_as_ascii_hex(TEST_OUTPUT, TEST_BYTES, TEST_SIZE));
}

static void test__print_as_ascii_hex__returns_minus_1_if_fprintf_of_trailing_newline()
{
	N_STUB(TEST_SIZE, xfprintf, 1);
	STUB(xfprintf, -1);
	assert_int_equal(-1, CALL(print_as_ascii_hex(TEST_OUTPUT, TEST_BYTES, TEST_SIZE)));
}

static void test__print_as_ascii_hex__does_nothing_else()
{
	disable_auto_stubs();
	STUB(print_prefix);
	N_STUB(TEST_SIZE, xfprintf, 1);
	STUB(xfprintf, 1);
	CALL(print_as_ascii_hex(TEST_OUTPUT, TEST_BYTES, TEST_SIZE));
}

/**********************************************************************************************************************/

int UNDER_TEST_main();

static void test__main__returns_EXIT_FAILURE_if_print_as_ascii_hex_fails()
{
	STUB(print_as_ascii_hex, -1);
	assert_int_equal(EXIT_FAILURE, CALL(main()));
}

static void test__main__prints_some_bytes()
{
	const uint8_t bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
	MOCK(print_as_ascii_hex, stdout, bytes, sizeof(bytes));
	CALL(main());
}

static void test__main__returns_EXIT_SUCCESS_on_success()
{
	assert_int_equal(CALL(main()), EXIT_SUCCESS);
}

/** main **************************************************************************************************************/

int main()
{
	unit_test_t all_tests[] =
	{
		unit_test(test__print_prefix__calls_fprintf),

		unit_test(test__print_as_scii_hex__print_prefix),
		unit_test(test__print_as_ascii_hex__returns_0_on_success),
		unit_test(test__print_as_ascii_hex__prints_all_bytes),
		unit_test(test__print_as_ascii_hex__returns_minus_1_if_fprintf_of_one_byte_fails),
		unit_test(test__print_as_ascii_hex__prints_trailing_new_line),
		unit_test(test__print_as_ascii_hex__returns_minus_1_if_fprintf_of_trailing_newline),
		unit_test(test__print_as_ascii_hex__does_nothing_else),

		unit_test(test__main__returns_EXIT_SUCCESS_on_success),
		unit_test(test__main__prints_some_bytes),
		unit_test(test__main__returns_EXIT_FAILURE_if_print_as_ascii_hex_fails),
	};

	return run_tests(all_tests);
}

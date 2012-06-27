#include <mockme/test.h>
#include <mockme/mock.h>
#include "utils.h"

/** test data *********************************************************************************************************/

#define TEST_OUTPUT  ((FILE*)0x666)
#define TEST_BYTES   ((uint8_t *)"abcde")
#define TEST_SIZE    (5)

/** mocks/stubs********************************************************************************************************/

int do_stuff(void)
{
	DEFAULT_STUB(0);
}

void do_other_stuff(int x)
{
	INPUT_VALUE(x);
	DEFAULT_STUB();
}

void do_some_other_stuff(void)
{
	DEFAULT_STUB();
}

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

/** tests *************************************************************************************************************/

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
	N_STUB(TEST_SIZE, xfprintf, 1);
	STUB(xfprintf, 1);
	CALL(print_as_ascii_hex(TEST_OUTPUT, TEST_BYTES, TEST_SIZE));
}

/** main **************************************************************************************************************/

int main()
{
	unit_test_t all_tests[] = {
		unit_test(test__print_as_ascii_hex__returns_0_on_success),
		unit_test(test__print_as_ascii_hex__prints_all_bytes),
		unit_test(test__print_as_ascii_hex__returns_minus_1_if_fprintf_of_one_byte_fails),
		unit_test(test__print_as_ascii_hex__prints_trailing_new_line),
		unit_test(test__print_as_ascii_hex__returns_minus_1_if_fprintf_of_trailing_newline),
		unit_test(test__print_as_ascii_hex__does_nothing_else),
	};

	return run_tests(all_tests);
}

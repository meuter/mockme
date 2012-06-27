#include <mockme/test.h>
#include <stdio.h>

/**********************************************************************************************************************/

#include "utils.h"

/**********************************************************************************************************************/

#define TEST_OUTPUT  ((FILE*)0x666)
#define TEST_BYTES   ((uint8_t *)"abcde")
#define TEST_SIZE    (5)

static void test__print_as_ascii_hex__returns_0_on_success()
{
	assert_int_equal(0, UNDER_TEST_print_as_ascii_hex(TEST_OUTPUT, TEST_BYTES, TEST_SIZE));
}

/**********************************************************************************************************************/

int main()
{
	unit_test_t all_tests[] = {
			unit_test(test__print_as_ascii_hex__returns_0_on_success),
	};

	return run_tests(all_tests);
}

#include <mockme/under_test.h>
#include <stdint.h>
#include <stdlib.h>

#include "utils.h"
#include "xstdio.h"

DEFINE_FUNCTION(int, print_as_ascii_hex,
	FILE *output,
	const uint8_t *bytes,
	const size_t size
)
{
	uint32_t i;

	for (i = 0; i < size; ++i)
		if (xfprintf(output, "%02X", bytes[i]) < 0)
			return -1;

	if (xfprintf(output, "\n") < 0)
		return -1;

	return 0;
}


DEFINE_FUNCTION(int, main)
{
	const uint8_t bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

	if (print_as_ascii_hex(stdout, bytes, sizeof(bytes)) < 0)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

#include <mockme/under_test.h>
#include <stdlib.h>
#include <string.h>

#include "demo.h"


DEFINE_FUNCTION(int, get_string_length,
	const char *string,
	size_t *length
)
{
	if (length == NULL || string == NULL)
		return -1;

	(*length) = strlen(string);

	return 0;
}


DEFINE_FUNCTION(const char *, get_prefix)
{
	return "> ";
}

DEFINE_FUNCTION(void, print_prefix)
{
	xfprintf(stdout, "%s", get_prefix());
}

DEFINE_FUNCTION(int, print_as_ascii_hex,
	FILE *output,
	const uint8_t *bytes,
	const size_t size
)
{
	uint32_t i;

	print_prefix();

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

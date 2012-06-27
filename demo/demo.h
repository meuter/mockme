#ifndef __DEMO_H__
#define __DEMO_H__

#include <mockme/under_test.h>
#include <stdint.h>
#include "xstdio.h"

DECLARE_FUNCTION(const char *, get_prefix);

DECLARE_FUNCTION(void, print_prefix);

DECLARE_FUNCTION(int, print_as_ascii_hex,
	FILE *output,
	const uint8_t *bytes,
	const size_t size
);

#endif

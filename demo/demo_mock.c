#include <mockme/mock.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void STUB_print_as_ascii_hex(int return_value)
{
    expect_any(print_as_ascii_hex, output);
    expect_any(print_as_ascii_hex, size);
    expect_any(print_as_ascii_hex, bytes);
    will_return(print_as_ascii_hex, return_value);
}
void MOCK_print_as_ascii_hex(FILE *output, const size_t size, const uint8_t *bytes)
{
    expect_value(print_as_ascii_hex, output, output);
    expect_value(print_as_ascii_hex, size, size);
    expect_value(print_as_ascii_hex, bytes, bytes);
    will_return(print_as_ascii_hex, 0);
}

int print_as_ascii_hex(FILE *output, const size_t size, const uint8_t *bytes)
{
    if (auto_stub())
        STUB_print_as_ascii_hex(0);
    check_expected(output);
    check_expected(size);
    check_expected(bytes);
    return (int)mock();
}

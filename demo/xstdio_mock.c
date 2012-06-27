#include <mockme/mock.h>
#include "xstdio.h"

void STUB_xfprintf(int return_value)
{
    expect_any(xfprintf, stream);
    expect_any(xfprintf, format);
    will_return(xfprintf, return_value);
}

void MOCK_xfprintf(FILE *stream, const char *format)
{
    expect_value(xfprintf, stream, stream);
    expect_string(xfprintf, format, format);
    will_return(xfprintf, 1);
}

int xfprintf(FILE *stream, const char *format, ...)
{
    if (auto_stub())
        STUB_xfprintf(1);
    check_expected(stream);
    check_expected(format);
    return (int)mock();
}

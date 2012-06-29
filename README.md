MockMe! 
=======

Introduction:
------------

MockMe! is a unit test framework for the C language based on top of (a patched)
version of cmockery (http://code.google.com/p/cmockery/). The main idea behind
this framework is to avoid manually writing mocks and stubs for your unit tests
(you know what happens when you do that http://www.youtube.com/watch?v=T-Qn_-F2x1c).
MockMe! uses PyCParser (http://code.google.com/p/pycparser/) for all its parsing
needs.

*Contributors*: Cédric Meuter, Nicolas Maquet with guidance by Erik Talboom

CLI:
---
At the heart of this, stands the mockme script. It acts as a C preprocessor that
auto-magically generates proper mocking and stubbing function for your double (*).
It has a simple command line interface:

<pre>
$ ./mockme --help
Usage: mockme [options] <INFILE>

Automatically generates and add cmockery mocks/stubs/double functions to a C
module

Options:
  -h, --help    show this help message and exit
  -I <DIR>      add the directory <DIR> to the list of directories to be
                searched for header files.
  -D <NAME>     predefine <NAME> as a macro, with definition 1
  -o <OUTFILE>  sets <OUTFILE> as output; if no file is provided, the standard
                output will be used
</pre>

(*) for a good description of mocks/stubs and double function, see:
    http://martinfowler.com/articles/mocksArentStubs.html


Example:
-------
Imagine you are testing a function that prints some bytes as ASCII hex. You already have
such a function, but your want to mock/stub it out for your test. You can simply write 
this:

<pre>
int print_as_ascii_hex(FILE *output, const uint8_t *bytes, const size_t size)
{
    INPUT_VALUE(output);
    INPUT_VALUE(size);
    INPUT_MEMORY(bytes, size);
    RETURN(0);
}
</pre>

which, using mockme, will be replaced by this:

<pre>
void STUB_print_as_ascii_hex(int return_value)
{
    expect_any(print_as_ascii_hex, output);
    expect_any(print_as_ascii_hex, size);
    expect_any(print_as_ascii_hex, bytes);
    will_return(print_as_ascii_hex, return_value);
}

void MOCK_print_as_ascii_hex(FILE *output, const uint8_t *bytes, const size_t size)
{
    expect_value(print_as_ascii_hex, output, output);
    expect_value(print_as_ascii_hex, size, size);
    expect_memory(print_as_ascii_hex, bytes, bytes, size);
    will_return(print_as_ascii_hex, 0);
}

int print_as_ascii_hex(FILE *output, const uint8_t *bytes, const size_t size)
{
    if (auto_stub())
        STUB_print_as_ascii_hex(0);
    check_expected(output);
    check_expected(size);
    check_expected(bytes);
    return (int)mock();
}
</pre>

which, in turn, allow you to write test like these:

<pre>
static void test__my_function__returns_minus_one_if_print_as_ascii_hex_fails() 
{
    STUB(print_as_ascii_hex, -1);
    assert_int_equal(-1, CALL(my_function()));
}

static void test__my_function__prints_some_bytes()
{    const uint8_t expected_bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };    MOCK(print_as_ascii_hex, stdout, expected_bytes, sizeof(expected_bytes));    CALL(my_function());}
</pre>



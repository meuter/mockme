MockMe! 
=======

Introduction
------------

*MockMe!* is a unit test framework for the C language based on top of (a patched)
version of <a href="http://code.google.com/p/cmockery/">cmockery</a>. The main idea behind
this framework is to avoid manually writing mocks and stubs for your unit tests
(you know what happens when you do that <a href="http://www.youtube.com/watch?v=T-Qn_-F2x1c">;-p</a>.
*MockMe!* relies on <a href="http://code.google.com/p/pycparser/">PyCParser</a> for all its parsing
needs.

<b>Contributors</b>: Cédric Meuter, Nicolas Maquet with guidance by Erik Talboom

mockme
------

At the heart of this, stands the mockme script. It acts as a C preprocessor that
auto-magically generates proper mocking and stubbing function for your double (*).
It has a simple command line interface:

<pre>
$ ./mockme --help
Usage: mockme [options] &lt;INFILE&gt;

Automatically generates and add cmockery mocks/stubs/double functions to a C
module.

Options:
  -h, --help    show this help message and exit
  -I &lt;DIR&gt;      add the directory &lt;DIR&gt; to the list of directories to be
                searched for header files.
  -D &lt;NAME&gt;     predefine &lt;NAME&gt; as a macro, with definition 1
  -o &lt;OUTFILE&gt;  sets &lt;OUTFILE&gt; as output; if no file is provided, the standard
                output will be used

/!\ do not forget the -I/path/to/fake_libc
</pre>

(*) for a very nice description of mocks/stubs/double functions (and much more!), you 
    can have a look at <a href="http://martinfowler.com/articles/mocksArentStubs.html">this article</a>
    by Martin Fowler.


Example
-------
Let's say you've written a function that prints some bytes as ASCII hex:

<pre>
int my_function()
{
	const uint8_t bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

	if (print_as_ascii_hex(stdout, bytes, sizeof(bytes)) == -1)
		return -1;

	return 0;
}
</pre>

Now you want to unit test the hello out of it (ok maybe you want to write 
the tests before writing the actual function, but that's another topic).
For the purpose of your test, you'll want to mock/stub print_as_ascii_hex() out.
You have two choices: (1) you write the mock/stub/double functions by hand,
which is long, painful and error prone or (2) you can describe it using the
following syntax:

<pre>
int print_as_ascii_hex(FILE *output, const uint8_t *bytes, const size_t size)
{
    INPUT_VALUE(output);
    INPUT_VALUE(size);
    INPUT_MEMORY(bytes, size);  
    RETURN(0);	// 0 is the default return value
}
</pre>

and let the mockme script generated this cmockery code:

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

which, in turn, can be used to write tests like these:

<pre>
static void test__my_function__returns_minus_one_if_print_as_ascii_hex_fails() 
{
	// inject -1 as the return value for print_as_ascii_hex()
    STUB(print_as_ascii_hex, -1);  
    // check that my_function cactches the error
    assert_int_equal(-1, CALL(my_function()));
}

static void test__my_function__prints_some_bytes()
{
	// tell the function print_as_ascii_hex() to expect some bytes to be printed on stdout
    const uint8_t expected_bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };    MOCK(print_as_ascii_hex, stdout, expected_bytes, sizeof(expected_bytes));

	// call my_function()    
    CALL(my_function());}
</pre>

For a more detailed example, you can have a look at 
<a href="https://github.com/meuter/mockme/blob/master/demo/demo_unit_test.c">demo_unit_test.c</a>.

Extra
-----

As an added bonus, for those of you who use <a href="http://www.scons.org/">scons</a>, you can check the
<a href="https://github.com/meuter/mockme/blob/master/SConstruct">SConstruct</a> to see how
mockme can be nicely integrated in a build script.


*Happy Testing!*

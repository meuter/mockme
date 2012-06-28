MockMe! 

MockMe! is a unit test framework for the C language based on top of (a patched)
version of cmockery (http://code.google.com/p/cmockery/). The main idea behind
this framework is to avoid manually writing mocks and stubs for your unit tests
(you what happens when you do that http://www.youtube.com/watch?v=T-Qn_-F2x1c).

Contributors: Cédric Meuter, Nicolas Maquet with some guidance by Erik Talboom



The mockme script acts as a C preprocessor that replaces this kind of stuff:

<pre>
int print_as_ascii_hex(FILE *output, const uint8_t *bytes, const size_t size)
{
    INPUT_VALUE(output);
    INPUT_MEMORY(bytes, size);
    DEFAULT_STUB(0);
}
</pre>

by this:

>  void STUB_print_as_ascii_hex(int return_value)
>  {
>      expect_any(print_as_ascii_hex, output);
>      expect_any(print_as_ascii_hex, size);
>      expect_any(print_as_ascii_hex, bytes);
>      will_return(print_as_ascii_hex, return_value);
>  }
>  
>  void MOCK_print_as_ascii_hex(FILE *output, const uint8_t *bytes, const size_t size)
>  {
>      expect_value(print_as_ascii_hex, output, output);
>      expect_value(print_as_ascii_hex, size, size);
>      expect_memory(print_as_ascii_hex, bytes, bytes, size);
>      will_return(print_as_ascii_hex, 0);
>  }
>  
>  int print_as_ascii_hex(FILE *output, const uint8_t *bytes, const size_t size)
>  {
>      if (auto_stub())
>          STUB_print_as_ascii_hex(0);
>      check_expected(output);
>      check_expected(size);
>      check_expected(bytes);
>      return (int)mock();
>  }

which in turn allow you to write test like these:

>  static void test__my_function__returns_minus_one_if_print_as_ascii_hex_fails() 
>  {
>      STUB(print_as_ascii_hex, -1);
>      assert_int_equal(-1, CALL(my_function()));
>  }
>  
>  static void test__my_function__prints_some_bytes()
>  {
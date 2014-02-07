.. _c_unit:

The C Unit Tests
================

This isn't about how to write C unit tests.

The assumption is that you already have working tests that you just want to run
and that these tests output some sort of Pass/Fail information.

For the sake of example say we have a test case like this:

.. code-block:: c

    #include "test_macros.h"

    void test_some_strings()
    {
        char *foo = "This is foo";
        char *bar = "This is bar";

        ASSERT_EQUAL_STR(foo, foo);
        ASSERT_EQUAL_STR(foo, bar);
    }

    int main()
    {
        test_some_strings();

        return 0;
    }

And when we compile and run it we get output like this::

    $ test/test_basic_strings

    [PASS] test_basic_strings.c:test_some_strings():8

    [FAIL] test_basic_strings.c:test_some_strings():9
      [TST] ASSERT_EQUAL_STR(foo, bar)
      [EXP] This is foo
      [GOT] This is bar

This is typical of a lot of test output and although the format is simple it
contains a lot of useful information:

* The Pass/Fail condition.
* The C file name.
* The function/test name.
* The line number of the test assertion.
* The assertion that failed.
* The expected and actual output.

So, let's see how we can run this or any number of similar tests automatically
and capture and summarise the output.

The first step is to write the :ref:`conftest`.


## Using py.test as a testrunner for C unit test files

This is an simple example of using `py.test` as a testrunner for C unit tests.

Py.test collects the C unit test files, executes them, captures the output and displays it.


This is a work in progress. Check back later.


    $ sudo pip install pytest

    $ make

    $ py.test -v
    ========================= test session starts ==========================
    =============================== FAILURES ===============================
    platform darwin -- Python 2.7.2 -- py-1.4.20 -- pytest-2.5.2
    collected 9 items

    test/test_basic_integers.c:14: test_some_integers() PASSED
    test/test_basic_integers.c:15: test_some_integers() PASSED
    test/test_basic_integers.c:21: test_more_integers() FAILED
    test/test_basic_integers.c:22: test_more_integers() FAILED
    test/test_basic_strings.c:16: test_some_strings() PASSED
    test/test_basic_strings.c:17: test_some_strings() PASSED
    test/test_basic_strings.c:26: test_more_strings() FAILED
    test/test_basic_strings.c:27: test_more_strings() FAILED
    test/test_basic_strings.c:28: test_more_strings() PASSED

    =============================== FAILURES ===============================
    _________________________ test_more_integers() _________________________
    Test failed : ASSERT_EQUAL_STR(313, 33) at test_basic_integers.c:21
             got: 33
        expected: 313

    _________________________ test_more_integers() _________________________
    Test failed : ASSERT_EQUAL_STR(12, 2) at test_basic_integers.c:22
             got: 2
        expected: 12

    _________________________ test_more_strings() __________________________
    Test failed : ASSERT_EQUAL_STR(bar, bar + 1) at test_basic_strings.c:26
             got: his is bar
        expected: This is bar

    _________________________ test_more_strings() __________________________
    Test failed : ASSERT_EQUAL_STR(foo, NULL) at test_basic_strings.c:27
             got: (null)
        expected: This is foo

    ================== 4 failed, 5 passed in 0.06 seconds ==================
    make: *** [test] Error 1

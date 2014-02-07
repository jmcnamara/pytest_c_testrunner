
## Using `pytest` as a testrunner for C unit test files

This is an simple tutorial on how to use the Python [`pytest`](http://pytest.org/latest/index.html) testing tool as a testrunner for C unit tests.

It includes [documentation](http://pytest-c-testrunner.readthedocs.org) and working examples.

![image](https://raw.github.com/jmcnamara/pytest_c_testrunner/master/docs/source/_images/output.png)


The tutorial shows how to extend pytest to collect C unit test files, execute them, capture the output and displays it.


    $ sudo pip install pytest

    $ make

    $ py.test -v
    ========================= test session starts ==========================
    platform darwin -- Python 2.7.2 -- py-1.4.20 -- pytest-2.5.2
    collected 9 items

    test/test_basic_integers.c:13: test_some_integers() PASSED
    test/test_basic_integers.c:14: test_some_integers() PASSED
    test/test_basic_integers.c:19: test_more_integers() FAILED
    test/test_basic_integers.c:20: test_more_integers() FAILED
    test/test_basic_strings.c:16: test_some_strings() PASSED
    test/test_basic_strings.c:17: test_some_strings() FAILED
    test/test_basic_strings.c:25: test_more_strings() FAILED
    test/test_basic_strings.c:26: test_more_strings() FAILED
    test/test_basic_strings.c:27: test_more_strings() PASSED

    =============================== FAILURES ===============================
    _________________________ test_more_integers() _________________________
    Test failed : ASSERT_EQUAL_STR(313, 33) at test_basic_integers.c:19
             got: 33
        expected: 313

    _________________________ test_more_integers() _________________________
    Test failed : ASSERT_EQUAL_STR(12, 2) at test_basic_integers.c:20
             got: 2
        expected: 12

    _________________________ test_some_strings() __________________________
    Test failed : ASSERT_EQUAL_STR(foo, bar) at test_basic_strings.c:17
             got: This is bar
        expected: This is foo

    _________________________ test_more_strings() __________________________
    Test failed : ASSERT_EQUAL_STR(bar, bar + 1) at test_basic_strings.c:25
             got: his is bar
        expected: This is bar

    _________________________ test_more_strings() __________________________
    Test failed : ASSERT_EQUAL_STR(foo, NULL) at test_basic_strings.c:26
             got: (null)
        expected: This is foo

    ================== 5 failed, 4 passed in 0.23 seconds ==================


[Read the full documentation](http://pytest-c-testrunner.readthedocs.org).

.. _running:

Running the Tests
=================

So finally we are at the stage where we can run the test cases.

If you'd like to try this for yourself
`the code is included in a project on GitHub <http://github.com/jmcnamara/pytest_c_testrunner>`_
so that you try out different options. The examples below show some of the
more common ones.


The Default Output
------------------

Here is the default output from ``py.test`` (the command line testrunner of
``pytest``)::

    $ make

    $ py.test
    ========================= test session starts ==========================
    platform darwin -- Python 2.7.2 -- py-1.4.20 -- pytest-2.5.2
    collected 9 items

    test/test_basic_integers.c ..FF
    test/test_basic_strings.c .FFF.

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

    ================== 5 failed, 4 passed in 0.19 seconds ==================


The Verbose Output
------------------

Here is the verbose output::

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


The first part of this is shown is colour:

.. image:: _images/output.png


Minimal Output
--------------

Here is some "quiet" output with the trace back hidden::

    $ py.test -q --tb=no
    ..FF.FFF.
    5 failed, 4 passed in 0.19 seconds


Filtered Tests
--------------

Here are results from all tests filtered to show only ones that match "strings"
in the name::

    $ py.test -k strings
    ========================= test session starts ==========================
    platform darwin -- Python 2.7.2 -- py-1.4.20 -- pytest-2.5.2
    collected 9 items

    test/test_basic_strings.c .FFF.

    =============================== FAILURES ===============================
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

    ================== 4 tests deselected by '-kstrings' ===================
    =========== 3 failed, 2 passed, 4 deselected in 0.19 seconds ===========


Other py.test Options
---------------------

Other testrunner options are shown in the Pytest
`Usage and Invocations <http://pytest.org/latest/usage.html#usage>`_
documentation.

You can also :ref:`learn_more` about this document and the sample test code.

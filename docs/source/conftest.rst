.. _conftest:

The Pytest hooks
================

One of the many useful features of ``pytest`` is its easy extensibility. The
``pytest`` documentation has a full description of
`Working with non-python tests <http://pytest.org/latest/example/nonpython.html#non-python-tests>`_
on which this C unit test extension is heavily based.

At its simplest, ``pytest`` supports the creation of hooks in a file called
``conftest.py`` that can be placed in the root folder where we wish to run the
tests. This allows us to define, in Python, code to find test files, run them,
and collect the results. The nice thing about this is that we can create a
hook layer between ``pytest`` and the C unit tests without changing code in
either one.

The ``conftest.py`` file is actually a per-directory file, so we can have
different files for different test directories if required.


The conftest.py file
--------------------

First let's look at the C unit test ``conftest.py`` in its entirety:

.. literalinclude:: ../../conftest.py
   :lines: 7-


This is less than 100 lines of Python, including comments, but it provides a
lot of functionality.

If you would like to see this functionality in use then move on to
:ref:`running`.

If you are interested in seeing how this functionality is implemented, and how
you could extend ``pytest`` for similar tests then read on below and we will
see how the ``conftest.py`` code works.

:ref:`running` or the Gory Details. Choose your own adventure!



Finding test files
------------------

The first function in the code is a ``pytest`` hook function called
``pytest_collect_file()``::

    def pytest_collect_file(parent, path):
        if path.ext == ".c" and path.basename.startswith("test_"):
            return CTestFile(path, parent)

This collects files based on any rule that we wish to write. In this case it
collects files that look like
``test_*.c`` but we could make the rule as specific as we wanted.

Once a file of the correct type is found a ``pytest.Node`` object of the
corresponding type is created and returned. In our case this is a
``CTestFile`` object which is derived from the ``pytest.File`` class.


The CTestFile Class
-------------------

The ``CTestFile`` object that we instantiated in the ``pytest_collect_file()``
hook inherits from the ``pytest.File`` class which in turn inherits from
``pytest.Collection`` and ``pytest.Node``. The ``Node`` class and its
subclasses have a ``collect()`` method which returns ``pytest.Items`` objects::

    class CTestFile(pytest.File):

        def collect(self):
            # Returns pytest.Items.

The ``pytest`` hierarchy and methods are explained in more detail in the
`Working with plugins and conftest files <http://pytest.org/latest/plugins.html>`_
section of the Pytest documentation.

Depending on the types of tests that are being run the collected items might be
individual test results or even test cases that are being staged to run.

However, in our case we are going to take a simplified approach that lends
itself to statically compiled test cases such as C unit tests:

* For each ``test_something.c`` file assume there is a ``test_something``
  executable.
* Run the ``test_something`` executable and capture the output.
* Parse the Pass/Fail results and any available metadata.
* Return each test results as a python dict with information that can be used
  for reporting.

Collecting the C unit test data
-------------------------------

So with this methodology in mind the first step is to run the collected C unit
tests and capture the output.

As stated above we are going to assume that the C unit tests are structured so
that for each ``test_something.c`` source file there is a ``test_something``
executable. This is a reasonable assumption based on the way most test suites
are laid out but it may not hold for specific implementations where, for
example, multiple ``.c`` files might be compiled to object files and linked
into a single test runner executable. For cases like that more a sophisticated
``pytest_collect_file()`` implementation can be used.

We are also going to assume, again reasonably, that the unit test executables
are tied into a build system and have already been built via ``make``,
``make test`` or something similar.

In ``conftest.py`` the following code runs the executable that corresponds to
the ``.c`` file and captures the output::

    def collect(self):

        test_exe = os.path.splitext(str(self.fspath))[0]
        test_output = subprocess.check_output(test_exe)

A more robust implementation would probably confirm the existence of the
executable and return a fail condition if it wasn't present.

Extracting the test data
------------------------

This section of the code shows the main functionality that converts the output
of the test cases into a format that can be used by ``pytest``. If you are
using this document as a guide to running your own tests then this section is
the part that you will have to modify to conform to your test output.

In our sample unit test the captured output will look something like the
following::

    [PASS] test_basic_strings.c:test_some_strings():8

    [FAIL] test_basic_strings.c:test_some_strings():9
      [TST] ASSERT_EQUAL_STR(foo, bar)
      [EXP] This is foo
      [GOT] This is bar


We clean up the unit test output and remove non test data lines as follows::

        lines = test_output.split("\n")
        lines = [line.strip() for line in lines]
        lines = [line for line in lines if line.startswith("[")]


We then extract the test metadata from the reformatted test output::

        test_results = []
        for line in lines:
            token, data = line.split(" ", 1)
            token = token[1:-1]

            if token in ("PASS", "FAIL"):
                file_name, function_name, line_number = data.split(":")
                test_results.append({"condition": token,
                                     "file_name": file_name,
                                     "function_name": function_name,
                                     "line_number": int(line_number),
                                     "EXP": 'EXP(no data found)',
                                     "GOT": 'GOT(no data found)',
                                     "TST": 'TST(no data found)',
                                     })
            elif token in ("EXP", "GOT", "TST"):
                test_results[-1][token] = data

Once this is complete we should end up with a collection of data structures
like the following::

    {'condition':     'FAIL',
     'file_name':     'test_basic_strings.c',
     'function_name': 'test_some_strings()',
     'TST':           'ASSERT_EQUAL_STR(foo, bar)',
     'EXP':           'This is foo',
     'GOT':           'This is bar',
     'line_number':   9 }

These results are then returned as a ``pytest.Item``::

        for test_result in test_results:
            yield CTestItem(test_result["function_name"], self, test_result)

Note, it isn't essential that we capture all of the information shown above.
None of it is strictly required by ``pytest`` apart from the test function
name. The idea here is that we try to capture any usefule information that we
want to display in the testrunner output. In the next section we will see how
we can format and display that information.

Formatting the test report
--------------------------

The ``pytest.Item`` that we return in the previous step is an instance of a
subclass so that we can control the test result formatting. We also override
the constructor so that we can pass the test result data structure as an
additional parameter::

    class CTestItem(pytest.Item):

        def __init__(self, name, parent, test_result):
            super(CTestItem, self).__init__(name, parent)
            self.test_result = test_result

To control the test result reporting and formatting we have to override three
``pytest.Item`` methods: ``runtest()``, ``repr_failure()`` and
``reportinfo()``.

In our case, the ``runtest()`` method isn't actually used to run a test since
we already did that in the ``collect()`` method of our ``CTestFile`` class.
Instead we just check for ``FAIL`` results and throw an exception when we find
one::

        def runtest(self):
            if self.test_result["condition"] == "FAIL":
                raise CTestException(self, self.name)

We use a user defined exception class in order to distinguish it from other
exceptions. The exception is then caught and handled in the ``repr_failure()``
method where we format the output for the failed test case::

        def repr_failure(self, exception):
            if isinstance(exception.value, CTestException):
                return ("Test failed : {TST} at {file_name}:{line_number}\n"
                        "         got: {GOT}\n"
                        "    expected: {EXP}\n".format(**self.test_result))

Finally we provide one additional piece of information that will be used in
verbose test display::

        def reportinfo(self):
            return self.fspath, self.test_result["line_number"] - 1, self.name

Achievement Unlocked
--------------------

Congratulations. You made it to the end of the code and have unlocked the
**Adventurous** badge.

Now let's see how to we go about :ref:`running`.

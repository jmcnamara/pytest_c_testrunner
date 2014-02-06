.. _index:

Pytest & C
==========

.. toctree::
   :hidden:

   c_unit_test.rst
   conftest.rst
   running.rst
   learn_more.rst

Using pytest as a testrunner for C unit tests
---------------------------------------------

This document shows how to use the Python ``pytest`` test tool to run unit
tests written in C.

.. image:: _images/output.png


Wait, what?
-----------

I'm going to show you how to run C unit tests using the Python test tool
``pytest``.


Are you sure that is a good idea?
---------------------------------

No. I'm pretty sure it isn't.

If you want to write and run C unit tests then there are a lot of alternatives
such as `googletest <https://code.google.com/p/googletest/>`_ or
`Unity <http://throwtheswitch.org/white-papers/unity-intro.html>`_ which are
generally better solutions.


So, what is the use case?
-------------------------

Established C/C++ test frameworks and test runners are a better solution when
you are starting a project from scratch. However, if you have existing C unit
tests that you just want to execute, then rewriting them to conform to a new
framework probably isn't worth the effort.

Equally, writing a testrunner that will run all or a subset of the tests, that
will dump the results into JUnit or other formats, that will filter results or
display them in concise or verbose output probably isn't worth the effort
either.

In which case it would be better to use an existing testrunner that supports
all these features and that can be easily extended to capture the output from
existing C unit tests without having to modify them.


Why Pytest?
-----------

`Pytest <http://pytest.org/latest/index.html>`_ is a really nice Python testing
tool.

It has `good documentation <http://pytest.org/latest/contents.html#toc>`_,
clean code, lots of tests, a large but clear set of options for running tests
and collecting results and best of all it is easily extensible.


Okay. I'm still with you, but barely
------------------------------------

Then read on and I'll see if I can convince you with a working example.

So let's start with :ref:`c_unit`.

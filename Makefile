###############################################################################
#
# Makefile for pytest_c_testrunner.
#
# Copyright 2014, John McNamara, jmcnamara@cpan.org
#

# Keep the output quiet by default.
Q=@
ifdef V
Q=
endif

.PHONY: docs

# Build the test executables.
all :
	$(Q)make -C test

# Clean the test executables.
clean :
	$(Q)make clean -C test
	$(Q)make clean -C docs

# Run the unit tests.
test : all
	$(Q)py.test test -v

# Run a passing test for TravisCI integration
test_travis : all
	$(Q)py.test test/test_passing.c -v

# Targets for documentation.
html: docs

docs:
	$(Q)make -C docs html

pdf:
	$(Q)make -C docs latexpdf

readthedocs:
	curl -X POST http://readthedocs.org/build/pytest-c-testrunner

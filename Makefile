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

# Run the unit tests.
test : all
	$(Q)py.test test -v

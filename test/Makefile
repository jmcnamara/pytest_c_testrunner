###############################################################################
#
# Makefile to compiler the unit tests for pytest_c_testrunner.
#
# Copyright 2014, John McNamara, jmcnamara@cpan.org
#

# Keep the output quiet by default.
Q=@
ifdef V
Q=
endif

# Directory variables.
INC_DIR = .

# Flags passed to the C++ compiler.
CFLAGS += -g -Wall -Wextra -Wno-nonnull

# Source files to compile.
SRCS = $(wildcard *.c)
EXES = $(patsubst %.c,%,$(SRCS))

all : $(EXES)

clean :
	$(Q)rm -f $(EXES)

# Executable targets.
%: %.c test_macros.h
	$(Q)$(CC) -I$(INC_DIR) $(CFLAGS) $< -o $@ $(LIBS)

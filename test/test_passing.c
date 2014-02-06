/*****************************************************************************
 * Simple unit tests for use with pytest_c_testrunner.
 *
 * Copyright 2014, John McNamara, jmcnamara@cpan.org
 *
 */

#include "test_macros.h"


void test_passing()
{
    char *foo = "This is foo";

    ASSERT_EQUAL_STR(foo, foo);
    ASSERT_EQUAL_INT(1, 1);
}

int main()
{
    test_passing();

    return 0;
}

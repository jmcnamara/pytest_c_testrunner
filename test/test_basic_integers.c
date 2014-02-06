/*****************************************************************************
 * Simple unit tests for use with pytest_c_testrunner.
 *
 * Copyright 2014, John McNamara, jmcnamara@cpan.org
 *
 */

#include "test_macros.h"


void test_some_integers()
{
    ASSERT_EQUAL_INT(1, 1);
    ASSERT_EQUAL_INT(234, 234);
}

void test_more_integers()
{
    ASSERT_EQUAL_INT(313, 33);
    ASSERT_EQUAL_INT(12, 2);
}

int main()
{
    test_some_integers();
    test_more_integers();

    return 0;
}

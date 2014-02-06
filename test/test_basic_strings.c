/*****************************************************************************
 * Simple unit tests for use with pytest_c_testrunner.
 *
 * Copyright 2014, John McNamara, jmcnamara@cpan.org
 *
 */

#include "test_macros.h"


void test_some_strings()
{
    char *foo = "This is foo";
    char *bar = "This is bar";

    ASSERT_EQUAL_STR(foo, foo);
    ASSERT_EQUAL_STR(foo, bar);
}

void test_more_strings()
{
    char *foo = "This is foo";
    char *bar = "This is bar";

    ASSERT_EQUAL_STR(bar, bar + 1);
    ASSERT_EQUAL_STR(foo, NULL);
    ASSERT_EQUAL_STR(foo, foo);
}

int main()
{
    test_some_strings();
    test_more_strings();

    return 0;
}

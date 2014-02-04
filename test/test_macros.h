/*****************************************************************************
 * Simple unit test macros for use with pytest_c_testrunner.
 *
 * Copyright 2014, John McNamara, jmcnamara@cpan.org
 *
 */

#include <stdio.h>
#include <string.h>

#define ASSERT_EQUAL_INT(exp, got)                                           \
    do {                                                                     \
        if ((exp) == (got)) {                                                \
            printf("\n[PASS] %s():%d\n", __func__, __LINE__);                \
        }                                                                    \
        else {                                                               \
            printf("\n[FAIL] %s():%d\n", __func__, __LINE__);                \
            printf("  [TST] ASSERT_EQUAL_INT(%d, %d)\n", (exp), (got));      \
            printf("  [EXP] %d\n", exp);                                     \
            printf("  [GOT] %d\n", got);                                     \
        }                                                                    \
    } while (0);

#define ASSERT_EQUAL_STR(exp, got)                                           \
    do {                                                                     \
        if ((exp) && (got) && strcmp((exp), (got)) == 0) {                   \
            printf("\n[PASS] %s():%d\n", __func__, __LINE__);                \
        }                                                                    \
        else {                                                               \
            printf("\n[FAIL] %s():%d\n", __func__, __LINE__);                \
            printf("  [TST] ASSERT_EQUAL_STR(exp, got)\n");                  \
            printf("  [EXP] %s\n", exp);                                     \
            printf("  [GOT] %s\n", got);                                     \
        }                                                                    \
    } while (0);

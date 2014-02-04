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
            printf("\n[PASS] %s:%s():%d\n", __FILE__, __func__, __LINE__);   \
        }                                                                    \
        else {                                                               \
            printf("\n[FAIL] %s:%s():%d\n", __FILE__, __func__, __LINE__);   \
            printf("  [TST] ASSERT_EQUAL_STR(" #exp ", " #got ")\n");        \
            printf("  [EXP] %d\n", (exp));                                   \
            printf("  [GOT] %d\n", (got));                                   \
        }                                                                    \
    } while (0);

#define ASSERT_EQUAL_STR(exp, got)                                           \
    do {                                                                     \
        if ((exp) && (got) && strcmp((exp), (got)) == 0) {                   \
            printf("\n[PASS] %s:%s():%d\n", __FILE__, __func__, __LINE__);   \
        }                                                                    \
        else {                                                               \
            printf("\n[FAIL] %s:%s():%d\n", __FILE__, __func__, __LINE__);   \
            printf("  [TST] ASSERT_EQUAL_STR(" #exp ", " #got ")\n");        \
            printf("  [EXP] %s\n", (exp) ? (exp) : "(null)");                \
            printf("  [GOT] %s\n", (got) ? (got) : "(null)");                \
        }                                                                    \
    } while (0);

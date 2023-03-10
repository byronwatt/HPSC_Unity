#include "unity.h"

typedef struct test_defn_t {
    UnityTestFunction func;
    const char *func_name;
    const uint32_t line_num;
    const char *filename;
    struct test_defn_t *next;
} test_defn_t;

extern struct test_defn_t *global_test_list;

void hpsc_add_test( test_defn_t * );

/*
 * HPSC_TEST(test_x)
 * {
 * }
 * 
 * replaces
 * 
 * void test_x()
 * {
 * }
 * 
 * and additionally adds the function to a list of test functions.
 */
#define HPSC_TEST( test_function ) \
    \
    void test_function(void); \
    \
    /* a static structure used to register a test function */ \
    static test_defn_t test_definition_##test_function = { \
        .func = test_function, \
        .func_name = #test_function, \
        .filename = __FILE__, \
        .line_num = __LINE__, \
        .next = NULL, \
    }; \
    \
    /* this function gets called before main() because it has attribute((__constructor__ )) */ \
    __attribute__((constructor)) void register_##test_function() { \
        hpsc_add_test( &test_definition_##test_function ); \
    } \
    \
    void test_function(void)

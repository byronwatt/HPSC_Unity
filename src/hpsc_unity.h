#include "unity.h"

typedef struct test_defn_t {
    UnityTestFunction func;
    const char *func_name;
    const uint32_t line_num;
    const char *filename;
    struct test_defn_t *next;
} test_defn_t;

void hpsc_add_test( test_defn_t *link );

#define HPSC_TEST( test_function ) \
void test_function(void); \
static test_defn_t test_definition_##test_function = { \
    .func = test_function, \
    .func_name = #test_function, \
    .filename = __FILE__, \
    .line_num = __LINE__, \
    .next = NULL, \
}; \
__attribute__((constructor)) void register_##test_function() { \
    hpsc_add_test( &test_definition_##test_function ); \
} \
void test_function(void)

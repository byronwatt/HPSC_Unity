typedef struct test_defn_t {
    UnityTestFunction func;
    const char *func_name;
    const uint32_t line_num;
    const char *filename;
    struct test_defn_t *next;
} test_defn_t;

extern test_defn_t *global_test_list;

#define REGISTER_TEST_FUNCTION( test_function ) \
  void register_##test_function() __attribute__((constructor)); \
  void register_##test_function() { \
    test_defn_t *link = &test_definition_##test_function; \
    link->next = global_test_list; \
    global_test_list = link; \
  }

#define HPSC_TEST( test_function ) \
void test_function(void); \
static test_defn_t test_definition_##test_function = { \
    .func = test_function, \
    .func_name = #test_function, \
    .filename = __FILE__, \
    .line_num = __LINE__, \
    .next = NULL, \
}; \
REGISTER_TEST_FUNCTION( test_function ) \
void test_function(void)

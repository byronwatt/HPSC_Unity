#include "unity.h"

#include "hpsc_unity.h"

static struct test_defn_t *global_test_list = 0;
static struct test_defn_t *global_test_list_tail = 0;

void hpsc_add_test( test_defn_t *link )
{
    if (global_test_list == 0)
    {
        global_test_list = link;
        global_test_list_tail = link;
    }
    else
    {
        global_test_list_tail->next = link;
        global_test_list_tail = link;
        link->next = NULL;
    }
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    for (test_defn_t *link = global_test_list;
        link != NULL;
        link = link->next)
    {
        Unity.TestFile = link->filename;
        UnityDefaultTestRun(link->func, link->func_name, link->line_num);
    }
    return UNITY_END();
}

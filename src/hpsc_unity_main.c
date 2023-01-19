#include "unity.h"

#include "hpsc_unity.h"

test_defn_t *global_test_list = NULL;
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

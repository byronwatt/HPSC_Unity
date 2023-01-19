#include "unity.h"

#include "hpsc_unity.h"

// note: setUp and tearDown are global functions !


HPSC_TEST( more_tests )
{
    //test stuff
}

HPSC_TEST( stuff )
{
    //more test stuff
}

test_defn_t *global_test_list;
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

#include "hpsc_unity.h"
#include "hpsc_arg.h"
#include <stddef.h>

// not needed when using generate_test_runner.rb
int main(int argc, char **argv) {
    parse_args( argc, argv );
    // parse_json_string();
    UNITY_BEGIN();
    for (test_defn_t *link = global_test_list;
        link != NULL;
        link = link->next)
    {
        Unity.TestFile = link->filename;
        /// ... filter stuff here ...
        UnityDefaultTestRun(link->func, link->func_name, link->line_num);
    }
    return UNITY_END();
}

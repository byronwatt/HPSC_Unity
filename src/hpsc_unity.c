#include "hpsc_unity.h"
#include "hpsc_arg.h"
#include <string.h>
#include <stddef.h>

struct test_defn_t *global_test_list = NULL;
static struct test_defn_t *global_test_list_tail = NULL;

void hpsc_add_test( test_defn_t *link )
{
    if (global_test_list == NULL)
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
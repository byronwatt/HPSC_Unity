#include "hpsc_arg.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static struct hpsc_arg_defn_t *global_arg_list = 0;
static struct hpsc_arg_defn_t *global_arg_list_tail = 0;


void hpsc_add_arg( hpsc_arg_defn_t *link )
{
    if (global_arg_list == 0)
    {
        global_arg_list = link;
        global_arg_list_tail = link;
    }
    else
    {
        global_arg_list_tail->next = link;
        global_arg_list_tail = link;
        link->next = NULL;
    }
}

/**
 * @brief
 *   display a usage message to stdout
 */
void Usage()
{
    uint32_t max_len = 0;
    for (hpsc_arg_defn_t *link = global_arg_list;
        link != NULL;
        link = link->next)
    {
        uint32_t len = strlen(link->arg_name);
        if (len > max_len)
        {
            max_len = len;
        }
    }
    for (hpsc_arg_defn_t *link = global_arg_list;
        link != NULL;
        link = link->next)
    {
        if (*link->arg_name == 0)
        {
            // if the argument name is blank, this is just an extra help message.
            printf("%s\n", link->arg_help);
        }
        else
        {
            // print link name left justified in the first column
            printf("  %*s - %s\n", -max_len, link->arg_name, link->arg_help);
        }
    }
    exit(-1);
}

// not needed when using generate_test_runner.rb
void parse_args( int argc, char *argv[] )
{
    for (int i = 1; i < argc; i++)
    {
        const char *s = argv[i];
        char token[100];
        const char *val_str;
        char *equals;

        /* make the '-' optional */
        if (s[0] == '-')
        {
            s++;
            if (s[0] == '-')
            {
                s++;
            }
        }
        strncpy(token, s, 99);
        equals = strchr(token, '=');
        if (equals == NULL)
        {
            val_str = (char *)"";
        }
        else
        {
            *equals = 0;
            equals++;
            val_str = &s[equals - token];
        }
        bool matched = false;
        for (hpsc_arg_defn_t *link = global_arg_list;
            link != NULL;
            link = link->next)
        {
            if (strcmp(token, link->arg_name) == 0)
            {
                if (!link->arg_parse(link,val_str))
                {
                    printf("error parsing '%s'\n", argv[i]);
                    Usage();
                }
                matched = true;
            }
        }
        if (!matched)
        {
            printf("no match for '%s'\n", token);
            Usage();
        }
    }
}

#include "hpsc_arg.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief
 *   Parse an integer from a string handles leading '0x'
 *
 * @param[in] s - command line argument string
 * @param[in] temp - pointer to first non-integer character in the string
 *
 * @return int32_t - integer value
 */
int32_t parse_int(const char *s, char **temp)
{
    int32_t value;
    if (strncmp(s, "0x", 2) == 0)
    {
        value = strtol(s + 2, temp, 16);
    }
    else
    {
        value = strtol(s, temp, 10);
    }
    return value;
}

bool hpsc_int32_parse( hpsc_int32_arg_t *arg, const char *s )
{
    char *temp;
    *(arg->var) = parse_int(s, &temp);
    if (*temp != 0)
        return false;
    /* printf("%s=%d (%x)\n",name,option_field,option_field); */
    return true;
}
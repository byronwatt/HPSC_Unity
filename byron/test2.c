#include "hpsc_unity.h"
#include "hpsc_arg.h"
#include <stdio.h>

static int32_t hello = 0;
INT32_ARG( hello, "hello", "this is the hello option" );

// note: setUp and tearDown are global functions !

HPSC_TEST( more_tests )
{
    printf("hello = %d\n",hello);
    //test stuff
}

HPSC_TEST( stuff )
{
    //more test stuff
}


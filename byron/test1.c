#include "hpsc_unity.h"

// note: setUp and tearDown are global functions !

/// @param  
void setUp(void) {
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}
/*
note: 
   HPSC_TEST( test_function_should_doBlahAndBlah ) 

expands to

    void test_function_should_doBlahAndBlah(void);
    static test_defn_t test_definition_test_function_should_doBlahAndBlah =
    {
        .func = test_function_should_doBlahAndBlah,
        .func_name = "test_function_should_doBlahAndBlah",
        .filename = "../byron/test1.c",
        .line_num = 17,
        .next = ((void *)0),
    }; 
    __attribute__((constructor)) void register_test_function_should_doBlahAndBlah() 
    {
        hpsc_add_test( &test_definition_test_function_should_doBlahAndBlah );
    }
    void test_function_should_doBlahAndBlah(void)
*/

HPSC_TEST( test_function_should_doBlahAndBlah )
{
    //test stuff
}

HPSC_TEST( test_function_should_doAlsoDoBlah )
{
    //more test stuff
}

#include <stdint.h>
#include <stdbool.h>

/*

note: the only parts of this header file that are used is the XXX_ARG macros and parse_args

in various .c files we link variables to command line arguments using the XXX_ARG macro:

e.g. in test_something.c:
    static int32_t hello = 0;
    INT32_ARG( hello, "hello", "this is the hello option" );

and in main() somewhere we call:
    parse_options(argc,argv);

that will set hello to <number> if 'hello=<number>' is on the command line. 

*/



/* base structure used internally by XXX_ARG macros */
typedef struct hpsc_arg_defn_t {
    struct hpsc_arg_defn_t *next;
    const char *arg_name;
    const char *arg_help;
    int (*arg_parse)( struct hpsc_arg_defn_t *, const char * );
} hpsc_arg_defn_t;

/* generic parse function type */
typedef int (*hpsc_arg_parse_fn)( struct hpsc_arg_defn_t *, const char * );

extern void parse_args( int argc, char *argv[] );

/* helper function used by XXX_ARG (not called directly) */
extern void hpsc_add_arg( hpsc_arg_defn_t * );

/* note: if we decide to use this style of argument parsing,
 * we will need to add double/uint32/64/string/bool.
 * and my favourite: enum.
 */

/* every argument type defines a XXX_ARG() macro,
 * and that macro uses a type hpsc_xxx_arg_t which extends the base hpsc_arg_defn_t structure,
 * and the arg_parse function is set to hpsc_xxx_parse().
 * the hpsc_xxx_parse() function is implemented in the function hpsc_xxx_arg.c,... 
 * and this means that only the functions that are used are pulled into the executable at link time.
 */
typedef struct {
    hpsc_arg_defn_t base;
    int32_t *var;
} hpsc_int32_arg_t;

/* helper function used by INT32_ARG (not called directly) */
extern bool hpsc_int32_parse( hpsc_int32_arg_t *, const char * );

/*
 * allow an int32_t variable to be set by a command line option.
 *
 * e.g.
 * static int32_t hello = 0;
 * INT32_ARG( hello, "hello", "this is the hello option" );
 * 
 * and in main() call:
 * parse_options(argc,argv);
 * that will set hello to xxx if 'hello=xxx' is on the command line. 
 */
#define INT32_ARG( variable, name, help ) \
    /* a static structure is linked in with a global list of arguments */ \
    static hpsc_int32_arg_t arg_defn_##variable = { \
        .base = { \
            .next = NULL, \
            .arg_name = name, \
            .arg_help = help, \
            .arg_parse = (hpsc_arg_parse_fn)hpsc_int32_parse, \
        }, \
        .var = &variable \
    }; \
    \
    /* this function is called before main() because of the __attribute__((constructor)) */ \
    __attribute__((constructor)) void register_##variable() { \
        hpsc_add_arg( (hpsc_arg_defn_t*)&arg_defn_##variable ); \
    }

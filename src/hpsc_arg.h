#include <stdint.h>
#include <stdbool.h>

typedef struct hpsc_arg_defn_t {
    struct hpsc_arg_defn_t *next;
    const char *arg_name;
    const char *arg_help;
    int (*arg_parse)( struct hpsc_arg_defn_t *, const char * );
} hpsc_arg_defn_t;

typedef int (*hpsc_arg_parse_fn)( struct hpsc_arg_defn_t *, const char * );

typedef struct {
    hpsc_arg_defn_t base;
    int32_t *var;
} hpsc_int32_arg_t;

extern void hpsc_add_arg( hpsc_arg_defn_t * );

extern bool hpsc_int32_parse( hpsc_int32_arg_t *, const char * );

extern void parse_args( int argc, char *argv[] );

/*
 * allow the variable to be set by a command line option.
 */
#define INT32_ARG( variable, name, help ) \
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
    __attribute__((constructor)) void register_##variable() { \
        hpsc_add_arg( (hpsc_arg_defn_t*)&arg_defn_##variable ); \
    }

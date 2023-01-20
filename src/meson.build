#
# build script written by : Michael Gene Brockus.
# github repo author: Mike Karlesky, Mark VanderVoord, Greg Williams.
#
# license: MIT
#
unity_dir = include_directories('.')

unity_lib = static_library(meson.project_name(),
    'hpsc_unity_main.c',
    'hpsc_unity.c',
    'hpsc_arg.c',
    'hpsc_int32_arg.c',
    'unity.c',
    include_directories: unity_dir,
    native: true
)



#
# build script written by : Michael Gene Brockus.
# github repo author: Mike Karlesky, Mark VanderVoord, Greg Williams.
#
# license: MIT
#
project('unity', 'c',
    license: 'MIT',
    meson_version: '>=0.37.0',
    default_options: ['werror=true', 'c_std=c11'])

add_global_arguments('-save-temps',
    language:['c','cpp'] )
    
subdir('src')
unity_dep = declare_dependency(link_with: unity_lib, include_directories: unity_dir)

  
executable('byron', 
  'byron/test1.c',
  'byron/test2.c',
   dependencies: unity_dep)
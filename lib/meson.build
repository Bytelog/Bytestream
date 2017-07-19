lib_inc = include_directories('.')

sds = static_library('sds',
    'sds/sds.c',
    override_options: ['c_std=c99']
)

util = static_library('util',
    'util/rand.c',
    'util/isaac/isaac64.c',
    dependencies: [math],
)

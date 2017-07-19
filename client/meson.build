glfw = dependency('glfw3', default_options: [])
gl = dependency('gl')
openal = dependency('openal')
x11 = dependency('x11')
raylib = cc.find_library('raylib', dirs: '/usr/local/lib')

executable('g1',
    'main.c',
    include_directories: lib_inc,
    c_args: cflags,
    dependencies: [raylib, jemalloc, glfw, gl, openal, x11],
    link_with: [sds, util]
)

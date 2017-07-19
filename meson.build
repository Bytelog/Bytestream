project('bytestream', 'c',
    version: '0',
    license: 'MIT',
    default_options: [
        'buildtype=debugoptimized',
        'layout=flat',
        'c_std=c11',
        'b_lto=true',
        'warning_level=3'
    ]
)

cc = meson.get_compiler('c')

jemalloc = cc.find_library('jemalloc', required: false)
math = cc.find_library('m', required: false)

cflags = ['-ffast-math', '-Wpedantic']

src_dir = join_paths(meson.source_root(), 'src')
lib_dir = join_paths(meson.source_root(), 'lib')

subdir('lib')
subdir('client')


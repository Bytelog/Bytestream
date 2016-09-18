project(lib)

add_library(sds
    sds/sds.h
    sds/sdsalloc.h
    sds/sds.c
)

target_include_directories(sds SYSTEM PUBLIC .)
target_compile_options(sds PRIVATE -w)

project(common)

add_library(common
    coordinates.c
    coordinates.h
)

target_include_directories(common PUBLIC .)
target_compile_options(common PRIVATE ${CFLAGS})

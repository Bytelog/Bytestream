project(common)

add_library(common
    coordinates.c
    coordinates.h
)

target_include_directories(common PUBLIC .)
target_compile_options(common PRIVATE ${CFLAGS})

if(BUILD_SHARED_LIBS)
  target_compile_definitions(common PRIVATE COMMON_EXPORTS)
  target_compile_definitions(common INTERFACE COMMON_IMPORTS)
endif()

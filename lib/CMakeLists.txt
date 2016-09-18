project(lib)

add_library(sds
    sds/sds.h
    sds/sdsalloc.h
    sds/sds.c
)

target_include_directories(sds SYSTEM PUBLIC .)
target_compile_options(sds PRIVATE -w)

if(BUILD_SHARED_LIBS)
  target_compile_definitions(sds PRIVATE SDS_EXPORTS)
  target_compile_definitions(sds INTERFACE SDS_IMPORTS)
endif()

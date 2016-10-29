project(lib)

add_library(iniparser
    iniparser/src/dictionary.c
    iniparser/src/iniparser.c
    iniparser/src/iniparser.h
)

add_library(klib
	klib/kbit.h
	klib/kbtree.h
	klib/kdq.h
	klib/khash.h
	klib/klist.h
	klib/kmath.c
	klib/kmath.h
	klib/ksort.h
	klib/kvec.h
)

add_library(mpack
	mpack/mpack.h
	mpack/mpack.c
)

add_library(sds
	sds/sds.h
	sds/sdsalloc.h
	sds/sds.c
)

target_include_directories(iniparser SYSTEM PUBLIC iniparser/src)
target_include_directories(klib SYSTEM PUBLIC .)
target_include_directories(mpack SYSTEM PUBLIC .)
target_include_directories(sds SYSTEM PUBLIC .)

# Disable compiler warnings
target_compile_options(iniparser PRIVATE -w)
target_compile_options(klib PRIVATE -w)
target_compile_options(mpack PRIVATE -w)
target_compile_options(sds PRIVATE -w)


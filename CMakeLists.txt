cmake_minimum_required(VERSION 3.2)
project(game C)

include(CheckCCompilerFlag)

# Default to Debug configuration
if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "CMAKE_BUILD_TYPE not set. Using debug configuration")
	set(CMAKE_BUILD_TYPE DEBUG)
endif()

# Use jemalloc if available
find_library(JEMALLOC_LIBRARY NAMES jemalloc)
if (JEMALLOC_LIBRARY)
	message(STATUS "jemalloc found: ${JEMALLOC_LIBRARY}")
	list(APPEND ADDITIONAL_LIBRARIES ${JEMALLOC_LIBRARY})
endif()

# Require C11 support
check_c_compiler_flag(-std=c11 HAS_C11)
if (NOT HAS_C11)
	message(FATAL_ERROR "Compiler must support C11")
endif()



set(CFLAGS -std=c11 -pipe -ffast-math -march=native -pedantic)


# Compiler specific flags
if (CMAKE_C_COMPILER_ID MATCHES "Clang")
	set(CFLAGS ${CFLAGS} -Weverything -Wno-documentation-unknown-command -Wno-padded)
elseif (CMAKE_C_COMPILER_ID MATCHES "GNU")
	set(CFLAGS ${CFLAGS} -Wall -Wextra -Wshadow)
endif()

#check for LTO and GOLD
check_c_compiler_flag(-flto HAS_LTO)
if (HAS_LTO)
	message(STATUS "Compiler supports LTO, using")
	set(CFLAGS ${CFLAGS} -flto)
endif()

option(USE_GOLD "Use GNU GOLD linker rather than LD")
if (USE_GOLD)
execute_process(COMMAND ${CMAKE_C_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LD_VERSION)
	if (NOT "${LD_VERSION}" MATCHES "GNU gold")
		message(FATAL_ERROR "GNU gold linker isn't available.")
	endif()
	message(STATUS "LD.GOLD found, using...")
	set(CFLAGS ${CFLAGS} -fuse-ld=gold)
endif()

if (CMAKE_BUILD_TYPE MATCHES DEBUG)
	set(CFLAGS ${CFLAGS} -DDEBUG -Wno-gnu-zero-variadic-macro-arguments)
endif (CMAKE_BUILD_TYPE MATCHES DEBUG)

if (CMAKE_BUILD_TYPE MATCHES RELEASE)
	set(CFLAGS ${CFLAGS} -Werror)
endif (CMAKE_BUILD_TYPE MATCHES RELEASE)

add_subdirectory(lib)
add_subdirectory(common)
add_subdirectory(client)

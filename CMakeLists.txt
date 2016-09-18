cmake_minimum_required(VERSION 3.0)
project(game C)

include(CheckCCompilerFlag)

# Default to Debug configuration
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE not set. Using debug configuration")
    set(CMAKE_BUILD_TYPE "Debug")
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

set(CFLAGS -std=c11 -pipe -ffast-math -pedantic)

# Compiler specific flags
if (CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CFLAGS ${CFLAGS} -Weverything -Wno-documentation-unknown-command)
elseif (CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CFLAGS ${CFLAGS} -Wall -Wextra -Wshadow)
endif()

if (CMAKE_BUILD_TYPE MATCHES RELEASE)
    message("debug mode")
endif (CMAKE_BUILD_TYPE MATCHES RELEASE)

add_subdirectory(lib)
add_subdirectory(common)
add_subdirectory(client)

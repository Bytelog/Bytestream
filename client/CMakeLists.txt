project(client)

include(FindPkgConfig)

add_executable(client client.c)

pkg_search_module(SDL2 REQUIRED sdl2 SDL2)

target_compile_options(client PRIVATE ${CFLAGS})
target_include_directories(client PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(client common sds ${SDL2_LIBRARIES})

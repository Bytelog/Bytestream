project(client)

include(FindPkgConfig)

add_executable(client
    client.c
    assets.c
)

pkg_search_module(SDL2 REQUIRED sdl2 SDL2)
pkg_search_module(SDL2_IMAGE REQUIRED sdl2_image SDL2_Image SDL2_image SDL2_IMAGE)

target_compile_options(client PRIVATE ${CFLAGS})
target_include_directories(client PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(client common iniparser klib mpack sds m ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

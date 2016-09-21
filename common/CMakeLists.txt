project(common)

file(GLOB COMMON_SRC
	"*.h"
	"*.c"
)

add_library(common ${COMMON_SRC})
target_include_directories(common PUBLIC .)
target_compile_options(common PRIVATE ${CFLAGS})
target_link_libraries(common klib m)

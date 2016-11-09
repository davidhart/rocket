cmake_minimum_required(VERSION 3.4)
project(rocket)

include ("common.cmake")

file(GLOB_RECURSE ROCKET_SOURCES
    RELATIVE ${PROJECT_SOURCE_DIR}
    GROUP 
    "src/rocket/*.cpp"
    "src/rocket/*.mm"
    "include/rocket/*.h"
    "include/rocket/*.inl")

add_library("rocket" SHARED ${ROCKET_SOURCES})
target_compile_definitions("rocket" PRIVATE "ROCKET_LIB_EXPORT")
target_include_directories("rocket" PRIVATE "include/rocket")
define_source_root_groups("include" "include/rocket")
define_source_root_groups("src" "src/rocket")

find_package(OpenGL REQUIRED)
target_link_libraries("rocket" ${OPENGL_LIBRARIES})

if (APPLE)
    target_link_libraries("rocket" "-framework Cocoa")
    target_link_libraries("rocket" "-framework Carbon")
    target_link_libraries("rocket" "-framework CoreFoundation")
endif()


file(GLOB_RECURSE ROCKET_EXAMPLE_GAME_SOURCES
	RELATIVE ${PROJECT_SOURCE_DIR}
	GROUP
	"src/example_game/*.cpp"
	"include/example_game/*.h")

add_executable("example_game" ${ROCKET_EXAMPLE_GAME_SOURCES})
target_link_libraries("example_game" "rocket")
target_include_directories("example_game" PRIVATE "include/example_game")
target_include_directories("example_game" PRIVATE "include/rocket")
define_source_root_groups("src" "src/example_game")
define_source_root_groups("include" "include/example_game")

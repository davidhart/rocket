cmake_minimum_required(VERSION 3.4)
project(rocket)

include ("common.cmake")

include_directories("include/rocket")

file(GLOB_RECURSE ROCKET_SOURCES
    RELATIVE ${PROJECT_SOURCE_DIR}
    GROUP 
    "src/rocket/*.cpp"
    "src/rocket/*.mm"
    "include/rocket/*.h"
    "include/rocket/*.inl")

add_library("rocket" SHARED ${ROCKET_SOURCES})
target_compile_definitions("rocket" PRIVATE "ROCKET_LIB_EXPORT")
define_source_root_groups("include" "include/rocket")
define_source_root_groups("src" "src/rocket")

find_package(OpenGL REQUIRED)
target_link_libraries("rocket" ${OPENGL_LIBRARIES})

if (APPLE)
    set(COCOA_LIBRARIES "-framework Cocoa -framework CoreFoundation")
    target_link_libraries("rocket" ${COCOA_LIBRARIES})
endif()



file(GLOB_RECURSE ROCKET_BOOTSTRAP_SOURCES
    RELATIVE ${PROJECT_SOURCE_DIR}
    GROUP
    "src/bootstrap/*.cpp"
    "include/bootstrap/*.h")

add_executable("rocket_bootstrap" ${ROCKET_BOOTSTRAP_SOURCES})
target_link_libraries("rocket_bootstrap" "rocket")
target_include_directories("rocket_bootstrap" PRIVATE "include/bootstrap")
define_source_root_groups("src" "src/bootstrap")
define_source_root_groups("include" "include/bootstrap")


file(GLOB_RECURSE ROCKET_EXAMPLE_GAME_SOURCES
	RELATIVE ${PROJECT_SOURCE_DIR}
	GROUP
	"src/example_game/*.cpp"
	"include/example_game/*.h")

add_library("example_game" SHARED ${ROCKET_EXAMPLE_GAME_SOURCES})
target_link_libraries("example_game" "rocket")
target_include_directories("example_game" PRIVATE "include/example_game")
define_source_root_groups("src" "src/example_game")
define_source_root_groups("include" "include/example_game")
add_dependencies("rocket_bootstrap" "example_game")
set_target_properties("example_game" PROPERTIES
    PREFIX ""
    SUFFIX "")

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
    "src/bootstrap/*.h")

add_executable("rocket_bootstrap" ${ROCKET_BOOTSTRAP_SOURCES})
target_link_libraries("rocket_bootstrap" "rocket")
target_include_directories("rocket_bootstrap" PRIVATE "include/bootstrap")
define_source_root_groups("src" "src/bootstrap")

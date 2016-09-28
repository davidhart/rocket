cmake_minimum_required(VERSION 3.4)

macro(define_source_root_groups grouproot base directory)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${base}/${directory} ${PROJECT_SOURCE_DIR}/${base}/${directory}*)
	foreach(child ${children})
		set(childpath ${PROJECT_SOURCE_DIR}/${base}/${directory}${child})

		if (IS_DIRECTORY ${childpath})
			define_source_root_groups(${grouproot} ${base} ${directory}${child}/)
		else()
			string(REPLACE "/" "\\" groupname "${directory}")
			source_group(${grouproot}\\${groupname} FILES ${base}/${directory}/${child})
		endif()
	endforeach()
endmacro()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE TESTPROGRAM_SOURCES
    GROUP
    src/rocket/*.cpp
    include/rocket/*.h
	include/rocket/*.inl)

include_directories(include/rocket)

define_source_root_groups(include include/rocket "")
define_source_root_groups(src src/rocket "")

SET(CMAKE_CXX_FLAGS "-std=c++11")

find_package(OpenGL REQUIRED)


add_executable(rocket ${TESTPROGRAM_SOURCES})
target_link_libraries(rocket ${OPENGL_LIBRARIES})

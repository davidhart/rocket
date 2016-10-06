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

#Require c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Increase level of warnings
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

file(GLOB_RECURSE ROCKET_SOURCES
	RELATIVE ${PROJECT_SOURCE_DIR}
    GROUP 
    src/rocket/*.cpp
	src/rocket/*.mm
    include/rocket/*.h
	include/rocket/*.inl)

include_directories(include/rocket)

define_source_root_groups(include include/rocket "")
define_source_root_groups(src src/rocket "")

add_executable(rocket ${ROCKET_SOURCES})

find_package(OpenGL REQUIRED)
target_link_libraries(rocket ${OPENGL_LIBRARIES})

if (APPLE)
	set(COCOA_LIBRARIES "-framework Cocoa -framework CoreFoundation")
	target_link_libraries(rocket ${COCOA_LIBRARIES})
endif()

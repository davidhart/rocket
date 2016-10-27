set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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

macro(define_source_root_groups_internal grouproot base directory)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${base}/${directory} ${PROJECT_SOURCE_DIR}/${base}/${directory}*)
	foreach(child ${children})
		set(childpath ${PROJECT_SOURCE_DIR}/${base}/${directory}${child})

		if (IS_DIRECTORY ${childpath})
			define_source_root_groups_internal(${grouproot} ${base} ${directory}${child}/)
		else()
			string(REPLACE "/" "\\" groupname "${directory}")
			source_group(${grouproot}\\${groupname} FILES ${base}/${directory}/${child})
		endif()
	endforeach()
endmacro()

macro(define_source_root_groups grouproot base)
	define_source_root_groups_internal(${grouproot} ${base} "")
endmacro()


cmake_minimum_required(VERSION 3.9)

project(felide)

if(MSVC)
	add_definitions("/std:c++latest")
else()
	set (CMAKE_CXX_STANDARD 17)
endif(MSVC)

include_directories("dep/wtl/Include")

add_subdirectory("src/felide")

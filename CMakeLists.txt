
cmake_minimum_required(VERSION 3.5)

project(felide)

option(FELIDE_UI_WINDOWS "Build the IDE user interface using the Windows API" OFF)
option(FELIDE_UI_GTK3      "Build the IDE user interface using the GTK+ toolkit" OFF)

# Specify the use of the C++17 standard
if(MSVC)
    add_definitions("/std:c++latest")
else()
    set (CMAKE_CXX_STANDARD 17)
endif(MSVC)

# Windows API
if(FELIDE_UI_WINDOWS)
    include_directories("dep/wtl/Include")
    add_subdirectory("src/felide-win")
endif()

# GTK3 Toolkit
if(FELIDE_UI_GTK3)
    add_subdirectory("src/felide-gtk3")
endif()

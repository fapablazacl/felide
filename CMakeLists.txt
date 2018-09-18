
cmake_minimum_required (VERSION 3.5)

project (felide)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_definitions (-DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR})

option (FELIDE_UI_WINDOWS 	"Build the IDE user interface using the Windows API"  OFF)
option (FELIDE_UI_GTK3      "Build the IDE user interface using the GTK+ toolkit" OFF)
option (FELIDE_UI_QT5       "Build the IDE user interface using the Qt5 toolkit"  OFF)

# we will require Boost ...
find_package(Boost REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# format library
add_subdirectory("dep/fmt/")
include_directories("dep/cxxopts/include")

set (YAML_CPP_BUILD_TESTS OFF CACHE BOOL "Enable parse tools")
set (YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "Enable testing")
set (YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "Enable contrib stuff in library")
add_subdirectory("dep/yaml-cpp")
include_directories("dep/yaml-cpp/include")

# Specify the use of the C++17 standard
if (MSVC)
    add_definitions ("/std:c++latest")
else ()
    set (CMAKE_CXX_STANDARD 17)
endif (MSVC)

# IDE Core
include_directories ("src/felide.core")
add_subdirectory ("src/felide.core")

# CLI Tools
include_directories ("src/felide-cli")
#add_subdirectory ("src/felide-cli")

# IDE GUI
add_subdirectory ("src/felide")

# Windows template library
if (FELIDE_UI_WINDOWS)
    include_directories ("dep/wtl/Include")
    add_subdirectory ("src/felide.ui.wtl")
endif ()

# GTK3 Toolkit
if (FELIDE_UI_GTK3)
    add_subdirectory ("src/felide.ui.gtk3")
endif ()

# QT5 Toolkit
if (FELIDE_UI_QT5)
    add_subdirectory ("src/felide.ui.qt5")
endif ()

add_subdirectory("src/sandbox")

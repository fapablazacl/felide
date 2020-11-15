
cmake_minimum_required (VERSION 3.5)

project (felide)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_definitions (-DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR})

if (FELIDE_STATIC_LINK)
    add_definitions (-DFELIDE_STATIC_LINK)
endif ()

# we will require Boost ...
find_package(Boost REQUIRED COMPONENTS filesystem program_options)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

if (UNIX)
    # TODO: Link with install prefix
    set(CMAKE_INSTALL_RPATH "/usr/local/lib")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif ()

# Specify the use of the C++17 standard
if (MSVC)
    add_definitions ("/std:c++latest")
else ()
    set (CMAKE_CXX_STANDARD 17)
endif (MSVC)

if (UNIX)
    add_definitions ("-fPIC")
endif ()

# IDE Core
add_subdirectory ("sources/felide.core")
add_subdirectory ("sources/felide.gui")
add_subdirectory ("sources/felide")
add_subdirectory ("sources/felide.gui.qt5")
add_subdirectory ("sources/gui-mvp")
add_subdirectory ("sources/qt5-scintilla-poc")

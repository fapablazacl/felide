
cmake_minimum_required (VERSION 3.5)

project (felide)

option (FELIDE_UI_WINDOWS 	"Build the IDE user interface using the Windows API"  OFF)
option (FELIDE_UI_GTK3      "Build the IDE user interface using the GTK+ toolkit" OFF)
option (FELIDE_UI_QT5       "Build the IDE user interface using the Qt5 toolkit"  OFF)

add_subdirectory("dep/fmt/")
include_directories("dep/cxxopts/include")

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
add_subdirectory ("src/felide-cli")

# Windows API
if (FELIDE_UI_WINDOWS)
    include_directories ("dep/wtl/Include")
    add_subdirectory ("src/felide.ui.wtl")
endif ()

# GTK3 Toolkit
if (FELIDE_UI_GTK3)
    add_subdirectory ("src/felide.ui.gtk3")
endif ()

if (FELIDE_UI_QT5)
    add_subdirectory ("src/felide.ui.qt5")
endif ()

add_subdirectory("src/sandbox")

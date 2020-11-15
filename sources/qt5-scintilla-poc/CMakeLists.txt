set (target "qt5-scintilla-poc")

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# this doesn't work on Linux (arch)
if (WIN32)
  find_library(QScintilla REQUIRED)
endif()

include_directories("${Qt5_DIR}/../../../include")
link_directories("${Qt5_DIR}/../../")

include_directories("../gui-mvp")

set (sources 
    "src/main.cpp"
    "src/QMainFrame.cpp"
    "src/QMainFrame.hpp"
)

add_definitions (-DFELIDE_TARGET_NAME=${target})
add_library(${target} ${sources})

# TODO: Determine if we need a static linking library for QScintilla
target_include_directories(${target} PUBLIC "include/")
target_compile_definitions (${target} PRIVATE "QSCINTILLA_DLL")

# TODO: Parametrize QScintilla for Windows Builds
if (WIN32)
    target_link_libraries (
        ${target} 
        Qt5::Widgets
        debug qscintilla2_qt5d
        optimized qscintilla2_qt5
        felide.core
        felide.gui
    )
else()
    target_link_libraries (
        ${target} 
        Qt5::Widgets
        qscintilla2_qt5
        felide.core
        felide.gui
    )
endif()

install (TARGETS ${target} DESTINATION "lib")

set (target "felide.gui.qt5")

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# this doesn't work on Linux (arch)
#find_library(QScintilla REQUIRED)

include_directories("${Qt5_DIR}/../../../include")
link_directories("${Qt5_DIR}/../../")

set (sources 
    "src/main_qt5.cpp"
    "include/src/FindReplaceDialogQt.hpp"
    "src/FindReplaceDialogQt.cpp"
    "include/src/IDEFrameQt.hpp"
    "src/IDEFrameQt.cpp"
    "include/src/DialogManagerQt.hpp"
    "src/DialogManagerQt.cpp"
    "include/src/FolderBrowserQt.hpp"
    "src/FolderBrowserQt.cpp"
    "include/src/FileSearchDialogQt.hpp"
    "src/FileSearchDialogQt.cpp"
    "include/src/FileSearchDialogItemWidgetQt.hpp"
    "src/FileSearchDialogItemWidgetQt.cpp"
    "include/src/UtilitiesQt.hpp"
    "src/UtilitiesQt.cpp"
    "include/src/DocumentManagerMdiQt.hpp"
    "src/DocumentManagerMdiQt.cpp"
    "include/src/DocumentMdiSubWindowQt.hpp"
    "src/DocumentMdiSubWindowQt.cpp"

)

add_definitions (-DFELIDE_TARGET_NAME=${target})
add_library(${target} ${sources})

# TODO: Determine if we need a static linking library for QScintilla
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

set (target "Xenoide.Gui.Qt5")

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# this doesn't work on Linux (arch)
if (WIN32)
  find_library(QScintilla REQUIRED)
endif()

set (sources
    "include/Xenoide/Gui/Qt5/FindReplaceDialogQt.hpp"
    "include/Xenoide/Gui/Qt5/IDEFrameQt.hpp"
    "include/Xenoide/Gui/Qt5/DialogManagerQt.hpp"
    "include/Xenoide/Gui/Qt5/FolderBrowserQt.hpp"
    "include/Xenoide/Gui/Qt5/FileSearchDialogQt.hpp"
    "include/Xenoide/Gui/Qt5/FileSearchDialogItemWidgetQt.hpp"
    "include/Xenoide/Gui/Qt5/UtilitiesQt.hpp"
    "include/Xenoide/Gui/Qt5/DocumentManagerMdiQt.hpp"
    "include/Xenoide/Gui/Qt5/DocumentMdiSubWindowQt.hpp"

    "src/main_qt5.cpp"
    "src/FindReplaceDialogQt.cpp"
    "src/IDEFrameQt.cpp"
    "src/DialogManagerQt.cpp"
    "src/FolderBrowserQt.cpp"
    "src/FileSearchDialogQt.cpp"
    "src/FileSearchDialogItemWidgetQt.cpp"
    "src/UtilitiesQt.cpp"
    "src/DocumentManagerMdiQt.cpp"
    "src/DocumentMdiSubWindowQt.cpp"
)

add_definitions (-DXENOIDE_TARGET_NAME=${target})
add_library(${target} ${sources})

# this is needed for QScintilla
target_include_directories(${target} PRIVATE "${Qt5_DIR}/../../../include")
target_link_directories(${target} PUBLIC "${Qt5_DIR}/../../")

target_include_directories(${target} PUBLIC "include/")
target_compile_definitions (${target} PRIVATE "QSCINTILLA_DLL")

if (WIN32)
    target_link_libraries (
        ${target} 
        Qt5::Widgets
        debug qscintilla2_qt5d
        optimized qscintilla2_qt5
        Xenoide.Core
        Xenoide.Gui
    )
else()
    target_link_libraries (
        ${target} 
        Qt5::Widgets
        qscintilla2_qt5
        Xenoide.Core
        Xenoide.Gui
    )
endif()

install (TARGETS ${target} DESTINATION "lib")

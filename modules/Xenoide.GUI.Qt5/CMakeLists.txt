set (target "Xenoide.GUI.Qt5")

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# this doesn't work on Linux (arch)
if (WIN32)
  find_library(QScintilla REQUIRED)
endif()

set (sources 
    "src/main_qt5.cpp"
    "include/Xenoide/GUI/Qt5/FindReplaceDialogQt.hpp"
    "src//FindReplaceDialogQt.cpp"
    "include/Xenoide/GUI/Qt5/IDEFrameQt.hpp"
    "src//IDEFrameQt.cpp"
    "include/Xenoide/GUI/Qt5/DialogManagerQt.hpp"
    "src//DialogManagerQt.cpp"
    "include/Xenoide/GUI/Qt5/FolderBrowserQt.hpp"
    "src//FolderBrowserQt.cpp"
    "include/Xenoide/GUI/Qt5/FileSearchDialogQt.hpp"
    "src//FileSearchDialogQt.cpp"
    "include/Xenoide/GUI/Qt5/FileSearchDialogItemWidgetQt.hpp"
    "src//FileSearchDialogItemWidgetQt.cpp"
    "include/Xenoide/GUI/Qt5/UtilitiesQt.hpp"
    "src//UtilitiesQt.cpp"
    "include/Xenoide/GUI/Qt5/DocumentManagerMdiQt.hpp"
    "src//DocumentManagerMdiQt.cpp"
    "include/Xenoide/GUI/Qt5/DocumentMdiSubWindowQt.hpp"
    "src//DocumentMdiSubWindowQt.cpp"
)

add_definitions (-DXENOIDE_TARGET_NAME=${target})
add_library(${target} ${sources})

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
        Xenoide.GUI
    )
else()
    target_link_libraries (
        ${target} 
        Qt5::Widgets
        qscintilla2_qt5
        Xenoide.Core
        Xenoide.GUI
    )
endif()

install (TARGETS ${target} DESTINATION "lib")

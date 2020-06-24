set (target "felide.gui.qt5")

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_library(QScintilla REQUIRED)

include_directories("${Qt5_DIR}/../../../include")
link_directories("${Qt5_DIR}/../../")

set (src_felide "felide/main.cpp")

set (src_felide_ui_qt5
    "felide/gui/qt5/QMainFrame.hpp"
    "felide/gui/qt5/QMainFrame.cpp"

    "felide/gui/qt5/FindReplaceDialogQt.hpp"
    "felide/gui/qt5/FindReplaceDialogQt.cpp"
    "felide/gui/qt5/DocumentQt.hpp"
    "felide/gui/qt5/DocumentQt.cpp"
    "felide/gui/qt5/IDEFrameQt.hpp"
    "felide/gui/qt5/IDEFrameQt.cpp"
    "felide/gui/qt5/DocumentManagerQt.hpp"
    "felide/gui/qt5/DocumentManagerQt.cpp"
    "felide/gui/qt5/DialogManagerQt.hpp"
    "felide/gui/qt5/DialogManagerQt.cpp"
    "felide/gui/qt5/FolderBrowserQt.hpp"
    "felide/gui/qt5/FolderBrowserQt.cpp"
    "felide/gui/qt5/FileSearchDialogQt.hpp"
    "felide/gui/qt5/FileSearchDialogQt.cpp"
    "felide/gui/qt5/FileSearchDialogItemWidgetQt.hpp"
    "felide/gui/qt5/FileSearchDialogItemWidgetQt.cpp"
    "felide/gui/qt5/UtilitiesQt.hpp"
    "felide/gui/qt5/UtilitiesQt.cpp"
    "felide/gui/qt5/QMdiDocumentManager.hpp"
    "felide/gui/qt5/QMdiDocumentManager.cpp"
    "felide/gui/qt5/QMdiSubWindowDocument.hpp"
    "felide/gui/qt5/QMdiSubWindowDocument.cpp"
)

set (sources
    ${src_felide}
    ${src_felide_ui_qt5}
)

add_definitions (-DFELIDE_TARGET_NAME=${target})
add_executable(${target} ${sources})

source_group ("felide" FILES ${src_felide})
source_group ("felide\\ui\\qt5" FILES ${src_felide_ui_qt5})

# TODO: Determine if wee need a static linking library for QScintilla
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
		gui-mvp
    )
else()
    target_link_libraries (
        ${target} 
        Qt5::Widgets
        qscintilla2_qt5
        felide.core
        felide.gui
		gui-mvp
    )
endif()

install (TARGETS ${target} DESTINATION "lib")

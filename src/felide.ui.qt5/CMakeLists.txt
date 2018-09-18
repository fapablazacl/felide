
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_library(QScintilla REQUIRED)

include_directories(${QSCINTILLA_INCLUDE_DIR})
link_directories(${QSCINTILLA_LIBRARY_DIR})

set (target "felide.ui.qt5")

set (src_felide_ui_qt5
    "felide/ui/qt5/Editor.hpp"
    "felide/ui/qt5/Editor.cpp"
    "felide/ui/qt5/MainWindow.hpp"
    "felide/ui/qt5/MainWindow.cpp"
    "felide/ui/qt5/EditorManager.hpp"
    "felide/ui/qt5/EditorManager.cpp"
    "felide/ui/qt5/DialogManager.hpp"
    "felide/ui/qt5/DialogManager.cpp"
    "felide/ui/qt5/FolderBrowser.hpp"
    "felide/ui/qt5/FolderBrowser.cpp"
)

add_library(${target} SHARED
    ${src_felide_ui_qt5}
)

target_link_libraries (
    ${target} 
    Qt5::Widgets
    qscintilla2_qt5
    felide.core
)

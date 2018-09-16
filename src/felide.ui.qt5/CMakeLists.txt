
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_library(QScintilla REQUIRED)

include_directories(${QSCINTILLA_INCLUDE_DIR})
link_directories(${QSCINTILLA_LIBRARY_DIR})

set (target "felide.ui.qt5")

set (src_felide_ui_qt5
    "felide/ui/qt5/MainWindow/EditorModel.hpp"
    "felide/ui/qt5/MainWindow/EditorModel.cpp"
    "felide/ui/qt5/MainWindow/MainWindow.hpp"
    "felide/ui/qt5/MainWindow/MainWindow.cpp"
    "felide/ui/qt5/MainWindow/MainWindowModel.hpp"
    "felide/ui/qt5/MainWindow/MainWindowModel.cpp"
    "felide/ui/qt5/MainWindow/MainWindowPresenter.hpp"
    "felide/ui/qt5/MainWindow/MainWindowPresenter.cpp"
    "felide/ui/qt5/MainWindow/MainWindowView.hpp"
    "felide/ui/qt5/MainWindow/MainWindowView.cpp"
    "felide/ui/qt5/MainWindow/Menu.hpp"
    "felide/ui/qt5/MainWindow/Menu.cpp"

    "felide/ui/qt5/TabbedEditorManager/Editor.hpp"
    "felide/ui/qt5/TabbedEditorManager/Editor.cpp"
    "felide/ui/qt5/TabbedEditorManager/EditorView.hpp"
    "felide/ui/qt5/TabbedEditorManager/EditorView.cpp"
    "felide/ui/qt5/TabbedEditorManager/EditorManagerView.hpp"
    "felide/ui/qt5/TabbedEditorManager/EditorManagerView.cpp"
    "felide/ui/qt5/TabbedEditorManager/TabbedEditorManager.hpp"
    "felide/ui/qt5/TabbedEditorManager/TabbedEditorManager.cpp"

    "Main.cpp"
)

add_executable(${target} WIN32
    ${src_felide_ui_qt5}
)

target_link_libraries (
    ${target} 
    Qt5::Widgets
    qscintilla2_qt5
    felide.core
)

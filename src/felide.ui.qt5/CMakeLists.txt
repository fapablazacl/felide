
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_library(QScintilla REQUIRED)

include_directories(${QSCINTILLA_INCLUDE_DIR})
link_directories(${QSCINTILLA_LIBRARY_DIR})

set (target "felide.ui.qt5")

set (src_felide_ui_qt5
    "Main.cpp"

    "felide/ui/EditorModel.hpp"
    "felide/ui/EditorModel.cpp"
    "felide/ui/MainWindowModel.hpp"
    "felide/ui/MainWindowModel.cpp"
    "felide/ui/MainWindowPresenter.hpp"
    "felide/ui/MainWindowPresenter.cpp"
    "felide/ui/MainWindowView.hpp"
    "felide/ui/MainWindowView.cpp"
    "felide/ui/Menu.hpp"
    "felide/ui/Menu.cpp"
    "felide/ui/EditorView.hpp"
    "felide/ui/EditorView.cpp"
    "felide/ui/EditorManagerView.hpp"
    "felide/ui/EditorManagerView.cpp"
    "felide/ui/DialogManagerView.hpp"
    "felide/ui/DialogManagerView.cpp"

    "felide/ui/qt5/Editor.hpp"
    "felide/ui/qt5/Editor.cpp"
    "felide/ui/qt5/MainWindow.hpp"
    "felide/ui/qt5/MainWindow.cpp"
    "felide/ui/qt5/EditorManager.hpp"
    "felide/ui/qt5/EditorManager.cpp"
    "felide/ui/DialogManager.hpp"
    "felide/ui/DialogManager.cpp"
    "felide/ui/qt5/ProjectBrowser.hpp"
    "felide/ui/qt5/ProjectBrowser.cpp"
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

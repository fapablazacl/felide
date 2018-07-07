
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)

set (target "felide.ui.qt5")

set (src_felide_ui_qt5
    "felide/MainWindow.hpp"
    "felide/MainWindow.cpp"
    "Main.cpp"
)

add_executable(${target} WIN32
    ${src_felide_ui_qt5}
)

target_link_libraries (
    ${target} 
    Qt5::Widgets
)

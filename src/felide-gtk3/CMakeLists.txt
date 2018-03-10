
find_package (PkgConfig)
pkg_check_modules (GTKMM gtkmm-3.0 gtksourceviewmm-3.0 gdlmm-3.0)

link_directories (${GTKMM_LIBRARY_DIRS})
include_directories (${GTKMM_INCLUDE_DIRS})

set (target "felide-gtk3")

set (sources 
    "Main.cpp" 
    "MainWindow.hpp" 
    "MainWindow.cpp"
    "MainApplication.hpp"
    "MainApplication.cpp"
    "ProjectExplorer.hpp"
    "ProjectExplorer.cpp"
    "Editor.hpp"
    "Editor.cpp"
    "EditorPanel.hpp"
    "EditorPanel.cpp"
)

add_executable (${target} ${sources})

target_link_libraries (${target} ${GTKMM_LIBRARIES} felide-core stdc++fs)


find_package (PkgConfig)
pkg_check_modules (GTKMM gtkmm-3.0 gtksourceviewmm-3.0 gdlmm-3.0)

include_directories(.)

link_directories (${GTKMM_LIBRARY_DIRS})
include_directories (${GTKMM_INCLUDE_DIRS})

set (target "Felide.UI.GTK3")

set (src
    "Main.cpp" 
)

set (felide_ui_gtk3_src
    "Felide/UI/GTK3/MainWindow.hpp" 
    "Felide/UI/GTK3/MainWindow.cpp"
    "Felide/UI/GTK3/MainApplication.hpp"
    "Felide/UI/GTK3/MainApplication.cpp"
    "Felide/UI/GTK3/ProjectExplorer.hpp"
    "Felide/UI/GTK3/ProjectExplorer.cpp"
    "Felide/UI/GTK3/Editor.hpp"
    "Felide/UI/GTK3/Editor.cpp"
    "Felide/UI/GTK3/EditorManager.hpp"
    "Felide/UI/GTK3/EditorManager.cpp"
)

source_group ("\\" FILES ${src})
source_group ("\\Felide\\UI\\GTK3" FILES ${felide_ui_gtk3_src})

add_executable (${target} ${src} ${felide_ui_gtk3_src})
target_link_libraries (${target} ${GTKMM_LIBRARIES} Felide.Core stdc++fs)


find_package (PkgConfig)
# pkg_check_modules (GTKMM gtkmm-3.0 gtksourceviewmm-3.0 gdlmm-3.0)
pkg_check_modules (GTKMM gtkmm-3.0 gtksourceviewmm-3.0)

include_directories(.)

link_directories (${GTKMM_LIBRARY_DIRS})
include_directories (${GTKMM_INCLUDE_DIRS})

set (target "felide.ui.gtk3")

set (src
    "Main.cpp" 
)

set (felide_ui_gtk3_src
    "felide/ui/gtk3/MainApplication.hpp"
    "felide/ui/gtk3/MainApplication.cpp"
    "felide/ui/gtk3/IDEFrameGtk.hpp" 
    "felide/ui/gtk3/IDEFrameGtk.cpp"
    "felide/ui/gtk3/DialogManagerGtk.hpp" 
    "felide/ui/gtk3/DialogManagerGtk.cpp"
    "felide/ui/gtk3/FolderBrowserGtk.hpp"
    "felide/ui/gtk3/FolderBrowserGtk.cpp"
    "felide/ui/gtk3/EditorManager/Editor.hpp"
    "felide/ui/gtk3/EditorManager/Editor.cpp"
    "felide/ui/gtk3/EditorManager/EditorManager.hpp"
    "felide/ui/gtk3/EditorManager/EditorManager.cpp"
    "felide/ui/gtk3/EditorManager/EditorHeader.hpp"
    "felide/ui/gtk3/EditorManager/EditorHeader.cpp"
)

add_executable (${target} ${src} ${felide_ui_gtk3_src})
target_link_libraries (${target} ${GTKMM_LIBRARIES} felide.core stdc++fs)

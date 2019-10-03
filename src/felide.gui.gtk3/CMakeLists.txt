
find_package (PkgConfig)
pkg_check_modules (GTKMM gtkmm-3.0 gtksourceviewmm-3.0 gdlmm-3.0)

include_directories(.)

link_directories (${GTKMM_LIBRARY_DIRS})
include_directories (${GTKMM_INCLUDE_DIRS})

set (target "felide.gui.gtk3")

set (src
    "Main.cpp" 
)

set (felide_ui_gtk3_src
    "felide/gui/gtk3/MainApplication.hpp"
    "felide/gui/gtk3/MainApplication.cpp"
    "felide/gui/gtk3/IDEFrameGtk.hpp" 
    "felide/gui/gtk3/IDEFrameGtk.cpp"
    "felide/gui/gtk3/DialogManagerGtk.hpp" 
    "felide/gui/gtk3/DialogManagerGtk.cpp"
    "felide/gui/gtk3/FolderBrowserGtk.hpp"
    "felide/gui/gtk3/FolderBrowserGtk.cpp"
    "felide/gui/gtk3/DocumentGtk.hpp"
    "felide/gui/gtk3/DocumentGtk.cpp"
    "felide/gui/gtk3/DocumentManagerGtk.hpp"
    "felide/gui/gtk3/DocumentManagerGtk.cpp"
    "felide/gui/gtk3/DocumentHeader.hpp"
    "felide/gui/gtk3/DocumentHeader.cpp"
)

add_executable (${target} ${src} ${felide_ui_gtk3_src})

target_link_libraries (${target} ${GTKMM_LIBRARIES} felide.core felide.gui stdc++fs)


# depends on GTKmm 3
find_package (PkgConfig)
pkg_check_modules (GTKMM gtkmm-3.0 gtksourceviewmm-3.0 gdlmm-3.0)
link_directories (${GTKMM_LIBRARY_DIRS})
include_directories (${GTKMM_INCLUDE_DIRS})

# target definition
set (target "Xenoide.Gui.Gtk3")

set (sources
    "include/Xenoide/Gui/Gtk3/MainApplication.hpp"
    "include/Xenoide/Gui/Gtk3/IDEFrameGtk.hpp"
    "include/Xenoide/Gui/Gtk3/DialogManagerGtk.hpp"
    "include/Xenoide/Gui/Gtk3/FolderBrowserGtk.hpp"
    "include/Xenoide/Gui/Gtk3/DocumentGtk.hpp"
    "include/Xenoide/Gui/Gtk3/DocumentManagerGtk.hpp"
    "include/Xenoide/Gui/Gtk3/DocumentHeader.hpp"

    "src/MainApplication.cpp"
    "src/IDEFrameGtk.cpp"
    "src/DialogManagerGtk.cpp"
    "src/FolderBrowserGtk.cpp"
    "src/DocumentGtk.cpp"
    "src/DocumentManagerGtk.cpp"
    "src/DocumentHeader.cpp"
    "src/Main.cpp"
)

add_executable (${target} ${sources})
target_include_directories (${target} PUBLIC "include")
target_link_libraries (${target} ${GTKMM_LIBRARIES} Xenoide.Core Xenoide.GUI stdc++fs)

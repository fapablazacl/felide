
set (target felide.gui.wtl)

set (src
    "Main.cpp"
)

set (felide_ui_wtl_src
    "felide/gui/wtl/CEditor.hpp"
    "felide/gui/wtl/CEditor.cpp"
    "felide/gui/wtl/CMainFrame.hpp"
    "felide/gui/wtl/CMainFrame.cpp"
)

source_group ("\\" FILES ${src})
source_group ("\\felide\\gui\\wtl" FILES ${felide_ui_wtl_src})

add_executable (${target} WIN32
    ${src} 
    ${felide_ui_wtl_src}
)

target_link_libraries (${target} felide.core felide.gui)


set (target felide.gui.wtl)

set (src
    "Main.cpp"
)

set (felide_ui_wtl_src
    "felide/ui/wtl/CEditor.hpp"
    "felide/ui/wtl/CEditor.cpp"
    "felide/ui/wtl/CMainFrame.hpp"
    "felide/ui/wtl/CMainFrame.cpp"
)

source_group ("\\" FILES ${src})
source_group ("\\felide\\gui\\wtl" FILES ${felide_ui_wtl_src})

add_library (${target} WIN32
    ${src} 
    ${felide_ui_wtl_src}
)

target_link_libraries (${target} Felide.Core)

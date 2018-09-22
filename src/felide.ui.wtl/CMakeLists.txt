
set (target felide.ui.wtl)

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
source_group ("\\Felide\\UI\\WTL" FILES ${felide_ui_wtl_src})

add_executable (${target} WIN32
    ${src} 
    ${felide_ui_wtl_src}
)

target_link_libraries (${target} Felide.Core)

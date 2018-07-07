
set (target Felide.UI.WTL)

set (src
    "Main.cpp"
)

set (felide_ui_wtl_src
    "felide/UI/WTL/CEditor.hpp"
    "felide/UI/WTL/CEditor.cpp"
    "felide/UI/WTL/CMainFrame.hpp"
    "felide/UI/WTL/CMainFrame.cpp"
)

source_group ("\\" FILES ${src})
source_group ("\\Felide\\UI\\WTL" FILES ${felide_ui_wtl_src})

add_executable (${target} WIN32
    ${src} 
    ${felide_ui_wtl_src}
)

target_link_libraries (${target} Felide.Core)


set (target Felide.UI.WTL)

set (src
    "Main.cpp"
)

set (felide_ui_wtl_src
    "Felide/UI/WTL/CEditor.hpp"
    "Felide/UI/WTL/CEditor.cpp"
    "Felide/UI/WTL/CMainFrame.hpp"
    "Felide/UI/WTL/CMainFrame.cpp"
)

source_group ("\\" FILES ${src})
source_group ("\\Felide\\UI\\WTL" FILES ${felide_ui_wtl_src})

add_executable (${target} WIN32
    ${src} 
    ${felide_ui_wtl_src}
)

target_link_libraries (${target} Felide.Core)

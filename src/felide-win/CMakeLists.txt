
set (target felide-win)

set (sources 
    "Main.cpp"
)

set (sources_view_win 
    "view/win/CEditor.hpp"
    "view/win/CEditor.cpp"
    "view/win/CMainFrame.hpp"
    "view/win/CMainFrame.cpp"
)

source_group ("\\" FILES ${sources})
source_group ("\\view\\win" FILES ${sources_view_win})

add_executable (${target} WIN32
    ${sources} 
    ${sources_view_win}
)

target_link_libraries (${target} felide-core)

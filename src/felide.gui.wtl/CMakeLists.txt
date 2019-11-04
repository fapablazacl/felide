
set (target felide.gui.wtl)

set (src
    "Main.cpp"
	"Resource.rc"
	"resource.h"
)

set (felide_ui_wtl_src
	"felide/gui/wtl/CIdeDocumentManager.hpp"
    "felide/gui/wtl/CIdeDocumentManager.cpp"
    "felide/gui/wtl/CIdeDocument.hpp"
    "felide/gui/wtl/CIdeDocument.cpp"
    "felide/gui/wtl/CIdeMainFrame.hpp"
    "felide/gui/wtl/CIdeMainFrame.cpp"
)

source_group ("\\" FILES ${src})
source_group ("\\felide\\gui\\wtl" FILES ${felide_ui_wtl_src})

add_executable (${target} WIN32
    ${src} 
    ${felide_ui_wtl_src}
)

target_link_libraries (${target} felide.core felide.gui)

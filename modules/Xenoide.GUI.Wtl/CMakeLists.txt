
set (target felide.gui.wtl)

set (src
    "Main.cpp"
	"Resource.rc"
	"resource.h"
)

set (felide_ui_wtl_src
	"felide/gui/wtl/CDocumentManager.hpp"
    "felide/gui/wtl/CDocumentManager.cpp"
    "felide/gui/wtl/CDocument.hpp"
    "felide/gui/wtl/CDocument.cpp"
    "felide/gui/wtl/CIdeFrame.hpp"
    "felide/gui/wtl/CIdeFrame.cpp"
	"felide/gui/wtl/CClassView.hpp"
    "felide/gui/wtl/CClassView.cpp"
	"felide/gui/wtl/CFolderBrowser.hpp"
    "felide/gui/wtl/CFolderBrowser.cpp"
	"felide/gui/wtl/CDialogManager.hpp"
    "felide/gui/wtl/CDialogManager.cpp"
)

source_group ("\\" FILES ${src})
source_group ("\\felide\\gui\\wtl" FILES ${felide_ui_wtl_src})

add_executable (${target} WIN32
    ${src} 
    ${felide_ui_wtl_src}
)

target_link_libraries (${target} felide.core felide.gui)

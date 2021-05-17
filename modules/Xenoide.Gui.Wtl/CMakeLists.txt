
set (target Xenoide.Gui.Wtl)

set (sources
	"include/Xenoide/Gui/Wtl/CDocumentManager.hpp"
    "include/Xenoide/Gui/Wtl/CDocument.hpp"
    "include/Xenoide/Gui/Wtl/CIdeFrame.hpp"
	"include/Xenoide/Gui/Wtl/CClassView.hpp"
	"include/Xenoide/Gui/Wtl/CFolderBrowser.hpp"
	"include/Xenoide/Gui/Wtl/CDialogManager.hpp"

	"src/CDocumentManager.cpp"
	"src/CDocument.cpp"
	"src/CIdeFrame.cpp"
	"src/CClassView.cpp"
	"src/CFolderBrowser.cpp"
    "src/CDialogManager.cpp"
	"src/Main.cpp"

	"res/Resource.rc"
	"res/resource.h"
)

add_executable (${target} WIN32 ${sources})

target_include_directories(${target} PUBLIC "include")
target_link_libraries (${target} Xenoide.Core Xenoide.Gui)

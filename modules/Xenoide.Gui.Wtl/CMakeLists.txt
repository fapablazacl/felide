
set (XENOIDE_WTL_INCLUDE_DIR "" CACHE PATH "")

if (NOT EXISTS ${XENOIDE_WTL_INCLUDE_DIR})
	message (SEND_ERROR "The supplied path in the variable XENOIDE_WTL_INCLUDE_DIR doesn't exists. (${XENOIDE_WTL_INCLUDE_DIR}).")
endif ()

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

# target_compile_definitions (${target} PUBLIC _UNICODE)
target_include_directories (${target} PUBLIC "include")
target_include_directories (${target} PUBLIC "res")
target_include_directories (${target} PUBLIC ${XENOIDE_WTL_INCLUDE_DIR})
target_link_libraries (${target} Xenoide.Core Xenoide.Gui)

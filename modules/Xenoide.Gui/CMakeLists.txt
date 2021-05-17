
set (target Xenoide.Gui)

set (sources
    "include/Xenoide/Gui/WindowsUtils.hpp"
    "include/Xenoide/Gui/FindReplaceDialog.hpp"
    "include/Xenoide/Gui/Document.hpp"
    "include/Xenoide/Gui/DocumentManager.hpp"
    "include/Xenoide/Gui/FolderBrowser.hpp"
    "include/Xenoide/Gui/IDEFrame.hpp"
    "include/Xenoide/Gui/FileSearchDialog.hpp"
    "include/Xenoide/Gui/DialogManager.hpp"
    "include/Xenoide/Gui/Menu.hpp"
    "include/Xenoide/Gui/MenuPanel.hpp"
    "include/Xenoide/Gui/FileFilter.hpp"

    "src/WindowsUtils.cpp"
    "src/FindReplaceDialog.cpp"
    "src/Document.cpp"
    "src/DocumentManager.cpp"
    "src/FolderBrowser.cpp"
    "src/IDEFrame.cpp"
    "src/FileSearchDialog.cpp"
    "src/DialogManager.cpp"
    "src/Menu.cpp"
    "src/MenuPanel.cpp"
    "src/FileFilter.cpp"
)

add_library (${target} ${sources})

target_include_directories (${target} PUBLIC "include/")
target_compile_definitions (${target} PRIVATE "XENOIDE_BUILD")

if (UNIX)
    set (DL_LIBRARY dl)
endif ()

target_link_libraries (
    ${target} 
    ${DL_LIBRARY}
    ${Boost_LIBRARIES}
    Xenoide.Core
)

install(TARGETS ${target} DESTINATION "lib")

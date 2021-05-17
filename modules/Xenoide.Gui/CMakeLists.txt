
set (target Xenoide.Gui)

set (sources
    "include/Xenoide/Gui/WindowsUtils.hpp"
    "include/Xenoide/Gui/FindReplaceDialog.hpp"
    "include/Xenoide/Gui/FindReplaceDialogPresenter.hpp"
    "include/Xenoide/Gui/Document.hpp"
    "include/Xenoide/Gui/DocumentModel.hpp"
    "include/Xenoide/Gui/DocumentPresenter.hpp"
    "include/Xenoide/Gui/DocumentManager.hpp"
    "include/Xenoide/Gui/DocumentManagerModel.hpp"
    "include/Xenoide/Gui/DocumentManagerPresenter.hpp"
    "include/Xenoide/Gui/FolderBrowser.hpp"
    "include/Xenoide/Gui/FolderBrowserPresenter.hpp"
    "include/Xenoide/Gui/FolderBrowserModel.hpp"
    "include/Xenoide/Gui/IDEFrameModel.hpp"
    "include/Xenoide/Gui/IDEFramePresenter.hpp"
    "include/Xenoide/Gui/IDEFrame.hpp"
    "include/Xenoide/Gui/FileSearchDialogModel.hpp"
    "include/Xenoide/Gui/FileSearchDialogPresenter.hpp"
    "include/Xenoide/Gui/FileSearchDialog.hpp"
    "include/Xenoide/Gui/DialogManager.hpp"
    "include/Xenoide/Gui/Menu.hpp"
    "include/Xenoide/Gui/MenuPanel.hpp"
    "include/Xenoide/Gui/FileFilter.hpp"

    "src/WindowsUtils.cpp"
    "src/FindReplaceDialog.cpp"
    "src/FindReplaceDialogPresenter.cpp"
    "src/Document.cpp"
    "src/DocumentModel.cpp"
    "src/DocumentPresenter.cpp"
    "src/DocumentManager.cpp"
    "src/DocumentManagerModel.cpp"
    "src/DocumentManagerPresenter.cpp"
    "src/FolderBrowser.cpp"
    "src/FolderBrowserPresenter.cpp"
    "src/FolderBrowserModel.cpp"
    "src/IDEFrameModel.cpp"
    "src/IDEFramePresenter.cpp"
    "src/IDEFrame.cpp"
    "src/FileSearchDialogModel.cpp"
    "src/FileSearchDialogPresenter.cpp"
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

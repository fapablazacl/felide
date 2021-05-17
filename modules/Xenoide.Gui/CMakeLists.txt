
set (target Xenoide.Gui)

set (sources
    "include/Xenoide/Gui/WindowsUtils.hpp"
    "src/WindowsUtils.cpp"
    "include/Xenoide/Gui/FindReplaceDialog.hpp"
    "src/FindReplaceDialog.cpp"
    "include/Xenoide/Gui/FindReplaceDialogPresenter.hpp"
    "src/FindReplaceDialogPresenter.cpp"

    "include/Xenoide/Gui/Document.hpp"
    "src/Document.cpp"
    "include/Xenoide/Gui/DocumentModel.hpp"
    "src/DocumentModel.cpp"
    "include/Xenoide/Gui/DocumentPresenter.hpp"
    "src/DocumentPresenter.cpp"

    "include/Xenoide/Gui/DocumentManager.hpp"
    "src/DocumentManager.cpp"
    "include/Xenoide/Gui/DocumentManagerModel.hpp"
    "src/DocumentManagerModel.cpp"
    "include/Xenoide/Gui/DocumentManagerPresenter.hpp"
    "src/DocumentManagerPresenter.cpp"

    "include/Xenoide/Gui/FolderBrowser.hpp"
    "src/FolderBrowser.cpp"
    "include/Xenoide/Gui/FolderBrowserPresenter.hpp"
    "src/FolderBrowserPresenter.cpp"
    "include/Xenoide/Gui/FolderBrowserModel.hpp"
    "src/FolderBrowserModel.cpp"

    "include/Xenoide/Gui/IDEFrameModel.hpp"
    "src/IDEFrameModel.cpp"
    "include/Xenoide/Gui/IDEFramePresenter.hpp"
    "src/IDEFramePresenter.cpp"
    "include/Xenoide/Gui/IDEFrame.hpp"
    "src/IDEFrame.cpp"

    "include/Xenoide/Gui/FileSearchDialogModel.hpp"
    "src/FileSearchDialogModel.cpp"
    "include/Xenoide/Gui/FileSearchDialogPresenter.hpp"
    "src/FileSearchDialogPresenter.cpp"
    "include/Xenoide/Gui/FileSearchDialog.hpp"
    "src/FileSearchDialog.cpp"

    "include/Xenoide/Gui/DialogManager.hpp"
    "src/DialogManager.cpp"
    "include/Xenoide/Gui/Menu.hpp"
    "src/Menu.cpp"
    "include/Xenoide/Gui/MenuPanel.hpp"
    "src/MenuPanel.cpp"
    "include/Xenoide/Gui/FileFilter.hpp"
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

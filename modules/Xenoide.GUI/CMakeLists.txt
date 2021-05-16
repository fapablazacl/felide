
set (target Xenoide.GUI)

set (sources
    "include/Xenoide/GUI/WindowsUtils.hpp"
    "src/WindowsUtils.cpp"
    "include/Xenoide/GUI/FindReplaceDialog.hpp"
    "src/FindReplaceDialog.cpp"
    "include/Xenoide/GUI/FindReplaceDialogPresenter.hpp"
    "src/FindReplaceDialogPresenter.cpp"

    "include/Xenoide/GUI/Document.hpp"
    "src/Document.cpp"
    "include/Xenoide/GUI/DocumentModel.hpp"
    "src/DocumentModel.cpp"
    "include/Xenoide/GUI/DocumentPresenter.hpp"
    "src/DocumentPresenter.cpp"

    "include/Xenoide/GUI/DocumentManager.hpp"
    "src/DocumentManager.cpp"
    "include/Xenoide/GUI/DocumentManagerModel.hpp"
    "src/DocumentManagerModel.cpp"
    "include/Xenoide/GUI/DocumentManagerPresenter.hpp"
    "src/DocumentManagerPresenter.cpp"

    "include/Xenoide/GUI/FolderBrowser.hpp"
    "src/FolderBrowser.cpp"
    "include/Xenoide/GUI/FolderBrowserPresenter.hpp"
    "src/FolderBrowserPresenter.cpp"
    "include/Xenoide/GUI/FolderBrowserModel.hpp"
    "src/FolderBrowserModel.cpp"

    "include/Xenoide/GUI/IDEFrameModel.hpp"
    "src/IDEFrameModel.cpp"
    "include/Xenoide/GUI/IDEFramePresenter.hpp"
    "src/IDEFramePresenter.cpp"
    "include/Xenoide/GUI/IDEFrame.hpp"
    "src/IDEFrame.cpp"

    "include/Xenoide/GUI/FileSearchDialogModel.hpp"
    "src/FileSearchDialogModel.cpp"
    "include/Xenoide/GUI/FileSearchDialogPresenter.hpp"
    "src/FileSearchDialogPresenter.cpp"
    "include/Xenoide/GUI/FileSearchDialog.hpp"
    "src/FileSearchDialog.cpp"

    "include/Xenoide/GUI/DialogManager.hpp"
    "src/DialogManager.cpp"
    "include/Xenoide/GUI/Menu.hpp"
    "src/Menu.cpp"
    "include/Xenoide/GUI/MenuPanel.hpp"
    "src/MenuPanel.cpp"
    "include/Xenoide/GUI/FileFilter.hpp"
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

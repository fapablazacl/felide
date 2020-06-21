
set (target felide.gui)

set (sources
    "felide/gui/find-replace-dialog/WindowsUtils.hpp"
    "felide/gui/find-replace-dialog/WindowsUtils.cpp"
    "felide/gui/find-replace-dialog/FindReplaceDialog.hpp"
    "felide/gui/find-replace-dialog/FindReplaceDialog.cpp"
    "felide/gui/find-replace-dialog/FindReplaceDialogPresenter.hpp"
    "felide/gui/find-replace-dialog/FindReplaceDialogPresenter.cpp"

    "felide/gui/document/Document.hpp"
    "felide/gui/document/Document.cpp"
    "felide/gui/document/DocumentModel.hpp"
    "felide/gui/document/DocumentModel.cpp"
    "felide/gui/document/DocumentPresenter.hpp"
    "felide/gui/document/DocumentPresenter.cpp"

    "felide/gui/document-manager/DocumentManager.hpp"
    "felide/gui/document-manager/DocumentManager.cpp"
    "felide/gui/document-manager/DocumentManagerModel.hpp"
    "felide/gui/document-manager/DocumentManagerModel.cpp"
    "felide/gui/document-manager/DocumentManagerPresenter.hpp"
    "felide/gui/document-manager/DocumentManagerPresenter.cpp"

    "felide/gui/folder-browser/FolderBrowser.hpp"
    "felide/gui/folder-browser/FolderBrowser.cpp"
    "felide/gui/folder-browser/FolderBrowserPresenter.hpp"
    "felide/gui/folder-browser/FolderBrowserPresenter.cpp"
    "felide/gui/folder-browser/FolderBrowserModel.hpp"
    "felide/gui/folder-browser/FolderBrowserModel.cpp"

    "felide/gui/ide-frame/IDEFrameModel.hpp"
    "felide/gui/ide-frame/IDEFrameModel.cpp"
    "felide/gui/ide-frame/IDEFramePresenter.hpp"
    "felide/gui/ide-frame/IDEFramePresenter.cpp"
    "felide/gui/ide-frame/IDEFrame.hpp"
    "felide/gui/ide-frame/IDEFrame.cpp"

    "felide/gui/file-search-dialog/FileSearchDialogModel.hpp"
    "felide/gui/file-search-dialog/FileSearchDialogModel.cpp"
    "felide/gui/file-search-dialog/FileSearchDialogPresenter.hpp"
    "felide/gui/file-search-dialog/FileSearchDialogPresenter.cpp"
    "felide/gui/file-search-dialog/FileSearchDialog.hpp"
    "felide/gui/file-search-dialog/FileSearchDialog.cpp"

    "felide/gui/DialogManager.hpp"
    "felide/gui/DialogManager.cpp"
    "felide/gui/Menu.hpp"
    "felide/gui/Menu.cpp"
    "felide/gui/MenuPanel.hpp"
    "felide/gui/MenuPanel.cpp"
    "felide/gui/FileFilter.hpp"
    "felide/gui/FileFilter.cpp"
    "felide/gui/UIToolkit.hpp"
    "felide/gui/UIToolkit.cpp"

    "felide/gui/mvp/MainFrame.hpp"
    "felide/gui/mvp/MainFrame.cpp"
)

add_library (${target} ${sources})

target_compile_definitions (${target} PRIVATE "FELIDE_BUILD")

if (UNIX)
    set (DL_LIBRARY dl)
endif ()

target_link_libraries (
    ${target} 
    ${DL_LIBRARY}
    ${Boost_LIBRARIES}
    felide.core
)

install(TARGETS ${target} DESTINATION "lib")

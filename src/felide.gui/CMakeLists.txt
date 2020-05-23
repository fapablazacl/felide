
set (target felide.gui)

set (sources_felide_ui_document
    "felide/gui/document/Document.hpp"
    "felide/gui/document/Document.cpp"
    "felide/gui/document/DocumentModel.hpp"
    "felide/gui/document/DocumentModel.cpp"
    "felide/gui/document/DocumentPresenter.hpp"
    "felide/gui/document/DocumentPresenter.cpp"
)

set (sources_felide_ui_documentmanager
    "felide/gui/document-manager/DocumentManager.hpp"
    "felide/gui/document-manager/DocumentManager.cpp"
    "felide/gui/document-manager/DocumentManagerModel.hpp"
    "felide/gui/document-manager/DocumentManagerModel.cpp"
    "felide/gui/document-manager/DocumentManagerPresenter.hpp"
    "felide/gui/document-manager/DocumentManagerPresenter.cpp"
)

set (sources_felide_ui_folderbrowser
    "felide/gui/folder-browser/FolderBrowser.hpp"
    "felide/gui/folder-browser/FolderBrowser.cpp"
    "felide/gui/folder-browser/FolderBrowserPresenter.hpp"
    "felide/gui/folder-browser/FolderBrowserPresenter.cpp"
    "felide/gui/folder-browser/FolderBrowserModel.hpp"
    "felide/gui/folder-browser/FolderBrowserModel.cpp"
)

set (sources_felide_ui_ideframe
    "felide/gui/ide-frame/IDEFrameModel.hpp"
    "felide/gui/ide-frame/IDEFrameModel.cpp"
    "felide/gui/ide-frame/IDEFramePresenter.hpp"
    "felide/gui/ide-frame/IDEFramePresenter.cpp"
    "felide/gui/ide-frame/IDEFrame.hpp"
    "felide/gui/ide-frame/IDEFrame.cpp"
)

set (sources_felide_ui_filesearchdialog
    "felide/gui/file-search-dialog/FileSearchDialogModel.hpp"
    "felide/gui/file-search-dialog/FileSearchDialogModel.cpp"
    "felide/gui/file-search-dialog/FileSearchDialogPresenter.hpp"
    "felide/gui/file-search-dialog/FileSearchDialogPresenter.cpp"
    "felide/gui/file-search-dialog/FileSearchDialog.hpp"
    "felide/gui/file-search-dialog/FileSearchDialog.cpp"
)

set (sources_felide_ui
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
)

set (sources
    ${sources_felide_ui}
    ${sources_felide_ui_document}
    ${sources_felide_ui_documentmanager}
    ${sources_felide_ui_folderbrowser}
    ${sources_felide_ui_filesearchdialog}
    ${sources_felide_ui_ideframe}
)

source_group ("felide\\gui"                      FILES ${sources_felide_ui})
source_group ("felide\\gui\\document"            FILES ${sources_felide_ui_document})
source_group ("felide\\gui\\document-manager"    FILES ${sources_felide_ui_documentmanager})
source_group ("felide\\gui\\folder-browser"      FILES ${sources_felide_ui_folderbrowser})
source_group ("felide\\gui\\ide-frame"           FILES ${sources_felide_ui_ideframe})
source_group ("felide\\gui\\file-search-dialog"  FILES ${sources_felide_ui_filesearchdialog})

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

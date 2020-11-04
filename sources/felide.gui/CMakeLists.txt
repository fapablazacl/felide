
set (target felide.gui)

set (sources
    "include/felide/gui/WindowsUtils.hpp"
    "src/WindowsUtils.cpp"
    "include/felide/gui/FindReplaceDialog.hpp"
    "src/FindReplaceDialog.cpp"
    "include/felide/gui/FindReplaceDialogPresenter.hpp"
    "src/FindReplaceDialogPresenter.cpp"

    "include/felide/gui/Document.hpp"
    "src/Document.cpp"
    "include/felide/gui/DocumentModel.hpp"
    "src/DocumentModel.cpp"
    "include/felide/gui/DocumentPresenter.hpp"
    "src/DocumentPresenter.cpp"

    "include/felide/gui/DocumentManager.hpp"
    "src/DocumentManager.cpp"
    "include/felide/gui/DocumentManagerModel.hpp"
    "src/DocumentManagerModel.cpp"
    "include/felide/gui/DocumentManagerPresenter.hpp"
    "src/DocumentManagerPresenter.cpp"

    "include/felide/gui/FolderBrowser.hpp"
    "src/FolderBrowser.cpp"
    "include/felide/gui/FolderBrowserPresenter.hpp"
    "src/FolderBrowserPresenter.cpp"
    "include/felide/gui/FolderBrowserModel.hpp"
    "src/FolderBrowserModel.cpp"

    "include/felide/gui/IDEFrameModel.hpp"
    "src/IDEFrameModel.cpp"
    "include/felide/gui/IDEFramePresenter.hpp"
    "src/IDEFramePresenter.cpp"
    "include/felide/gui/IDEFrame.hpp"
    "src/IDEFrame.cpp"

    "include/felide/gui/FileSearchDialogModel.hpp"
    "src/FileSearchDialogModel.cpp"
    "include/felide/gui/FileSearchDialogPresenter.hpp"
    "src/FileSearchDialogPresenter.cpp"
    "include/felide/gui/FileSearchDialog.hpp"
    "src/FileSearchDialog.cpp"

    "include/felide/gui/DialogManager.hpp"
    "src/DialogManager.cpp"
    "include/felide/gui/Menu.hpp"
    "src/Menu.cpp"
    "include/felide/gui/MenuPanel.hpp"
    "src/MenuPanel.cpp"
    "include/felide/gui/FileFilter.hpp"
    "src/FileFilter.cpp"
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


#include "IDEFramePresenter.hpp"
#include "IDEFrame.hpp"
#include "IDEFrameModel.hpp"

#include <boost/filesystem.hpp>
#include <felide/gui/MenuPanel.hpp>
#include <felide/gui/folder-browser/FolderBrowserPresenter.hpp>
#include <felide/gui/folder-browser/FolderBrowserModel.hpp>
#include <felide/util/FileUtil.hpp>

#include <iostream>
#include <cassert>

namespace felide {
    IDEFramePresenter::IDEFramePresenter(IDEFrameModel *model) {
        this->model = model;

        // initialize child presenters
        documentManagerPresenter = std::make_unique<DocumentManagerPresenter>(model->getDocumentManagerModel());
        folderBrowserPresenter = std::make_unique<FolderBrowserPresenter>(model->getFolderBrowserModel(), this);
    }

    IDEFramePresenter::~IDEFramePresenter() {}

    void IDEFramePresenter::onInitialized(IDEFrame *view, DialogManager *dialogView, MenuPanel *menuView) {
        assert(view);
        
        this->view = view;
        this->dialogView = dialogView;
        this->menuView = menuView;

        const auto menu = Menu{Menu::menuBar({
            Menu::menu("&File", {
                Menu::action([this] () { this->onFileNew(); }, "&New", {Modifier::Ctrl, Key::N}),
                Menu::separator(),
                Menu::action([this] () { this->onFileOpen(); }, "&Open ...", {Modifier::Ctrl, Key::O}),
                Menu::action([this] () { this->onFileOpenFolder(); }, "Open &Folder ...", {Modifier::CtrlShift, Key::O}),
                Menu::separator(),
                Menu::action([this] () { this->onFileSave(); }, "&Save", {Modifier::Ctrl, Key::S}),
                Menu::action([this] () { this->onFileSaveAs(); }, "Sa&ve As ..."),
                Menu::action([this] () { this->onFileSaveAll(); }, "Save &All"),
                Menu::separator(),
                Menu::action([this] () { this->onFileClose(); }, "&Close"),
                Menu::separator(),
                Menu::action([this] () { this->onFileExit(); }, "&Exit")
            }),
            Menu::menu("&Edit", {
                Menu::action([this] () { this->onEditUndo(); }, "&Undo", {Modifier::Ctrl, Key::Z}),
                Menu::action([this] () { this->onEditRedo(); }, "&Redo", {Modifier::CtrlShift, Key::Z}),
                Menu::separator(),
                Menu::action([this] () { this->onEditCut(); }, "&Cut", {Modifier::Ctrl, Key::X}),
                Menu::action([this] () { this->onEditCopy(); }, "C&opy", {Modifier::Ctrl, Key::C}),
                Menu::action([this] () { this->onEditPaste(); }, "&Paste", {Modifier::Ctrl, Key::V}),
                Menu::separator(),
                Menu::action([] () {}, "Find ..."),
                Menu::action([] () {}, "Replace ..."),
            }),
            Menu::menu("&View", {
                Menu::action([this] () { this->onViewFolderBrowser(); }, "&Folder Browser")
            }),
            Menu::menu("&Tools", {
                Menu::action([this] () { this->onToolsFileSearch(); }, "File &Search ...", {Modifier::CtrlShift, Key::P})
            }),
            Menu::menu("&Build", {
                Menu::action([] () {}, "&Clean"),
                Menu::action([] () {}, "&Execute")
            }),
            Menu::menu("&Help", {
                Menu::action([] () {}, "&About", {Key::F1})
            }),
        })};

        this->menuView->setupMenuBar(menu);
    }

    void IDEFramePresenter::onFileNew() {
        documentManagerPresenter->onNewDocument();
    }

    void IDEFramePresenter::onFileOpen() {
        auto fileDialog = FileDialogData{};
        fileDialog.title = "Open File";
        fileDialog.filters = model->getFileFilters();
        fileDialog.type = FileDialogType::OpenFile;

        if (auto filePath = dialogView->showFileDialog(fileDialog)) {
            documentManagerPresenter->onOpenDocument(filePath.get());
        }
    }
    
    void IDEFramePresenter::onFileOpen(const std::string &filePath) {
        documentManagerPresenter->onOpenDocument(filePath);
    }

    void IDEFramePresenter::onFileOpenFolder() {
        auto folderDialog = FolderDialogData{};
        folderDialog.title = "Open Folder";

        if (auto folderPath = dialogView->showFolderDialog(folderDialog)) {
            folderBrowserPresenter->onDisplayFolder(folderPath.get());
            model->setWorkspaceFolder(folderPath.get());
        }
    }

    void IDEFramePresenter::onToolsFileSearch() {
        if (auto workspaceFolder = model->getWorkspaceFolder()) {
            auto fileSearchDialog = FileSearchDialogData{};

            fileSearchDialog.title = "File Search";
            fileSearchDialog.defaultPath = workspaceFolder.get();

            if (auto filePath = dialogView->showFileSearchDialog(fileSearchDialog)) {
                documentManagerPresenter->onOpenDocument(filePath.get());
            }
        }
    }

    void IDEFramePresenter::onFileSave() {
        documentManagerPresenter->onSaveDocument();
    }

    void IDEFramePresenter::onFileSaveAs() {
        documentManagerPresenter->onSaveAsDocument();
    }
    
    void IDEFramePresenter::onFileSaveAll() {
        documentManagerPresenter->onSaveAllDocuments();
    }

    void IDEFramePresenter::onEditUndo() {
        // TODO: Add implementation
    }

    void IDEFramePresenter::onEditRedo() {
        // TODO: Add implementation
    }

    void IDEFramePresenter::onEditCut() {
        // TODO: Add implementation
    }

    void IDEFramePresenter::onEditCopy() {
        // TODO: Add implementation
    }

    void IDEFramePresenter::onEditPaste() {
        // TODO: Add implementation
    }

    void IDEFramePresenter::onFileClose() {
        documentManagerPresenter->onCloseCurrentDocument();
    }

    void IDEFramePresenter::onFileExit() {
        view->close();
    }

    bool IDEFramePresenter::onCloseRequested() {
        assert(this);
        assert(view->getDialogManager());

        auto messageDialog = MessageDialogData {};
        messageDialog.title = "felide";
        messageDialog.message = "Exit?";
        messageDialog.icon = DialogIcon::Question;
        messageDialog.buttons = DialogButton::YesNo;

        const DialogButton button = dialogView->showMessageDialog(messageDialog);
        
        return button == DialogButton::Yes;
    }
    
    void IDEFramePresenter::onViewFolderBrowser() {
        // TODO: Add implementation
    }

    void IDEFramePresenter::openFolder(const std::string &fullPath) {
        view->getFolderBrowser()->displayFolder(fullPath);
    }

    DocumentManagerPresenter*  IDEFramePresenter::getDocumentManagerPresenter() {
        return documentManagerPresenter.get();
    }

    FolderBrowserPresenter* IDEFramePresenter::getFolderBrowserPresenter() {
        return folderBrowserPresenter.get();
    }
}

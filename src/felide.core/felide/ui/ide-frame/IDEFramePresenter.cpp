
#include "IDEFramePresenter.hpp"
#include "IDEFrame.hpp"
#include "IDEFrameModel.hpp"

#include <boost/filesystem.hpp>
#include <felide/ui/folder-browser/FolderBrowserPresenter.hpp>
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

    void IDEFramePresenter::onInitialized(IDEFrame *view, DialogManager *dialogView) {
        assert(view);
        
        this->view = view;
        this->dialogView = dialogView;
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
        // TODO: Add implementation
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

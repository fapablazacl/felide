
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
        const IDEFrame::FileOperationViewData viewData = {
           "Open File",
           model->getFileFilters(),
           ""
        };

        if (auto filePath = view->showFileOpenDialog(viewData); filePath) {
            documentManagerPresenter->onOpenDocument(filePath.get());
        }
    }
    
    void IDEFramePresenter::onFileOpen(const std::string &filePath) {
        documentManagerPresenter->onOpenDocument(filePath);
    }

    void IDEFramePresenter::onFileOpenFolder() {
        const IDEFrame::FolderOpenViewData viewData = {
            "Open Folder", 
            boost::filesystem::current_path()
        };

        if (auto folderPath = view->showFolderOpenDialog(viewData); folderPath) {
            folderBrowserPresenter->onDisplayFolder(folderPath.get());
        }
    }

    void IDEFramePresenter::onFileSave() {
        documentManagerPresenter->onSaveDocument();

        /*
        using boost::filesystem::path;
        
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        auto editorModel = this->getDocumentModel(editor);

        if (editorModel->hasFilePath()) {
            this->editorSave(editor, editorModel);
        } else {
            this->editorSaveAs(editor);
        }
        */
    }

    void IDEFramePresenter::onFileSaveAs() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        this->editorSaveAs(editor);
    }

    void IDEFramePresenter::onEditUndo() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->undo();
    }

    void IDEFramePresenter::onEditRedo() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->redo();
    }

    void IDEFramePresenter::onEditCut() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->cut();
    }

    void IDEFramePresenter::onEditCopy() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->copy();
    }

    void IDEFramePresenter::onEditPaste() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->paste();
    }

    void IDEFramePresenter::onFileSaveAll() {
        std::cout << "IDEFramePresenter::fileSaveAll()" << std::endl;
    }

    void IDEFramePresenter::onFileClose() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        this->onDocumentCloseRequested(editor);
    }

    void IDEFramePresenter::onFileExit() {
        view->close();
    }

    void IDEFramePresenter::onDocumentContentModified(Document *editor) {
        /*
        auto editorModel = this->getDocumentModel(editor);

        editorModel->modify();
        // editor->setTitle(mapDocumentTitle(editorModel));
        */
    }
    
    void IDEFramePresenter::onDocumentCloseRequested(Document *editor) {
        /*
        bool closeDocument = true;
        
        auto model = this->getDocumentModel(editor);
        
        if (model->getModifiedFlag()) {
            DialogButton button = view->getDialogManager()->showMessageDialog("felide", "Save Changes?", DialogIcon::Question, DialogButton::YesNoCancel);
            
            switch (button) {
                case DialogButton::Yes:
                    this->editorSave(editor, model);
                    closeDocument = true;
                    break;
                    
                case DialogButton::No:
                    closeDocument = true;
                    break;

                default:
                    return;
            }
        }
        
        if (closeDocument) {
            editorModels.erase(editor);
            view->getDocumentManager()->closeDocument(editor);
        }
        */
    }
    
    bool IDEFramePresenter::onCloseRequested() {
        assert(this);
        assert(view->getDialogManager());
        DialogButton button = view->getDialogManager()->showMessageDialog("felide", "Exit?", DialogIcon::Question, DialogButton::YesNo);
        
        return button == DialogButton::Yes;
    }
    
    void IDEFramePresenter::editorSave(Document *editor, DocumentModel *editorModel) {
        editorModel->setContent(editor->getContent());
        
        const std::string fileName = editorModel->getFilePath();
        const std::string content = editorModel->getContent();
        
        FileUtil::save(fileName, content);
        
        editorModel->setFilePath(fileName);
        editorModel->setModifiedFlag(false);
        // editor->setTitle(mapDocumentTitle(editorModel));
    }
    
    void IDEFramePresenter::editorSaveAs(Document *editor) {
        auto editorModel = this->getDocumentModel(editor);
        
        const IDEFrame::FileOperationViewData viewData = {
           "Save File",
            model->getFileFilters(),
            ""
        };

        if (auto filePath = view->showFileSaveDialog(viewData); filePath) {
            const std::string content = editor->getContent();
        
            editorModel->setFilePath(filePath.get().string());
            editorModel->setContent(content);
        
            this->editorSave(editor, editorModel);
        }
    }

    void IDEFramePresenter::onViewFolderBrowser() {
        // TODO: Add implementation
    }

    DocumentModel* IDEFramePresenter::createDocumentModel(const Document *view, const int tag) {
        return nullptr;

        /*
        auto editorModel = DocumentModel::create(tag);
        auto editorModelPtr = editorModel.get();

        editorModels[view] = std::move(editorModel);

        return editorModelPtr;
        */
    }

    DocumentModel* IDEFramePresenter::createDocumentModel(const Document *view, const std::string &fileName) {
        return nullptr;

        /*
        auto editorModel = DocumentModel::create(fileName);
        auto editorModelPtr = editorModel.get();
        
        editorModels[view] = std::move(editorModel);

        return editorModelPtr;
        */
    }

    DocumentModel* IDEFramePresenter::getDocumentModel(const Document *view) {
        return nullptr;

        /*
        auto editorModel = editorModels[view].get();

        assert(editorModel);

        return editorModel;
        */
    }
    
    Document* IDEFramePresenter::getDocument(const DocumentModel *model) {
        return nullptr;
        /*
        assert(model);
        Document* view = nullptr;
        
        for (auto &pair : editorModels) {
            if (pair.second.get() == model) {
                // TODO: Refactor in order to prevent removal of the constness
                view = const_cast<Document*>(pair.first);
                break;
            }
        }
        
        return view;
        */
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

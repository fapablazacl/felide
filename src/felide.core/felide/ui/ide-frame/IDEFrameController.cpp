
#include "IDEFrameController.hpp"
#include "IDEFrame.hpp"
#include "IDEFrameModel.hpp"

#include <boost/filesystem.hpp>
#include <felide/util/FileUtil.hpp>

#include <iostream>
#include <cassert>

namespace felide {
    static std::string mapDocumentTitle(const DocumentModel *model) {
        std::string title;

        if (model->hasFilePath()) {
            using boost::filesystem::path;

            title = path(model->getFilePath()).filename().string();
        } else {
            title = "Untitled " + std::to_string(model->getTag());
        }
        
        title = (model->getModifiedFlag() ? "[*]" : "") + title;

        return title;
    }

    IDEFrameController::IDEFrameController() {}

    IDEFrameController::~IDEFrameController() {}

    void IDEFrameController::attachView(IDEFrame *view) {
        assert(view);
        
        this->view = view;
    }

    void IDEFrameController::detachView() {
        view = nullptr;
    }

    void IDEFrameController::onFileNew() {
        int tag = model.increaseDocumentCount();

        auto editor = view->getDocumentManager()->appendDocument();
        auto editorModel = this->createDocumentModel(editor, tag);

        editor->setConfig(DocumentConfig::Default());
        editor->setTitle(mapDocumentTitle(editorModel));
    }

    void IDEFrameController::onFileOpen() {
        const IDEFrame::FileOperationViewData viewData = {
           "Open File",
           model.getFileFilters(),
           ""
        };

        if (auto filePath = view->showFileOpenDialog(viewData); filePath) {
            this->onDocumentShow(filePath.get().string());
        }
    }
    
    void IDEFrameController::onFileOpenFolder() {
        const IDEFrame::FolderOpenViewData viewData = {
            "Open Folder", 
            boost::filesystem::current_path()
        };

        if (auto folder = view->showFolderOpenDialog(viewData); folder) {
            this->openFolder(folder.get().string());
        }
    }

    void IDEFrameController::onFileSave() {
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
    }

    void IDEFrameController::onFileSaveAs() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        this->editorSaveAs(editor);
    }

    void IDEFrameController::onEditUndo() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->undo();
    }

    void IDEFrameController::onEditRedo() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->redo();
    }

    void IDEFrameController::onEditCut() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->cut();
    }

    void IDEFrameController::onEditCopy() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->copy();
    }

    void IDEFrameController::onEditPaste() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        editor->paste();
    }

    void IDEFrameController::onFileSaveAll() {
        std::cout << "IDEFrameController::fileSaveAll()" << std::endl;
    }

    void IDEFrameController::onFileClose() {
        auto editor = view->getDocumentManager()->getCurrentDocument();
        
        if (!editor) {
            return;
        }

        view->getDocumentManager()->closeDocument(editor);
    }

    void IDEFrameController::onFileExit() {
        view->close();
    }

    void IDEFrameController::onDocumentContentModified(Document *editor) {
        auto editorModel = this->getDocumentModel(editor);

        editorModel->modify();
        editor->setTitle(mapDocumentTitle(editorModel));
    }
    
    void IDEFrameController::onDocumentCloseRequested(Document *editor) {
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
    }
    
    bool IDEFrameController::onCloseRequested() {
        assert(this);
        assert(view->getDialogManager());
        DialogButton button = view->getDialogManager()->showMessageDialog("felide", "Exit?", DialogIcon::Question, DialogButton::YesNo);
        
        return button == DialogButton::Yes;
    }
    
    void IDEFrameController::editorSave(Document *editor, DocumentModel *editorModel) {
        editorModel->setContent(editor->getContent());
        
        const std::string fileName = editorModel->getFilePath();
        const std::string content = editorModel->getContent();
        
        FileUtil::save(fileName, content);
        
        editorModel->setFilePath(fileName);
        editorModel->setModifiedFlag(false);
        editor->setTitle(mapDocumentTitle(editorModel));
    }
    
    void IDEFrameController::editorSaveAs(Document *editor) {
        auto editorModel = this->getDocumentModel(editor);
        
        const IDEFrame::FileOperationViewData viewData = {
           "Save File",
            model.getFileFilters(),
            ""
        };

        if (auto filePath = view->showFileSaveDialog(viewData); filePath) {
            const std::string content = editor->getContent();
        
            editorModel->setFilePath(filePath.get().string());
            editorModel->setContent(content);
        
            this->editorSave(editor, editorModel);
        }
    }

    void IDEFrameController::onDocumentShow(const std::string &filePath) {
		if (boost::filesystem::is_directory(filePath)) {
			return;
		}

        auto &viewModels = editorModels;

        auto viewModelIt = std::find_if(viewModels.begin(), viewModels.end(), [filePath](const auto &pair) {
            const auto &editorModel = pair.second;

            return editorModel->hasFilePath() && editorModel->getFilePath() == filePath;
        });

        if (viewModelIt != viewModels.end()) {
            view->getDocumentManager()->showDocument(const_cast<Document*>(viewModelIt->first));
        } else {
            const std::string content = FileUtil::load(filePath);

            auto editor = view->getDocumentManager()->appendDocument();
            auto editorModel = this->createDocumentModel(editor, filePath);
            
            editor->setConfig(DocumentConfig::Default());
            editor->setContent(content);
            editorModel->setModifiedFlag(false);
            editorModel->setContent(content);
            editor->setTitle(mapDocumentTitle(editorModel));
        }
    }

    void IDEFrameController::onViewFolderBrowser() {
        // TODO: Add implementation
    }

    DocumentModel* IDEFrameController::createDocumentModel(const Document *view, const int tag) {
        auto editorModel = new DocumentModel(tag);

        editorModels[view] = std::unique_ptr<DocumentModel>(editorModel);

        return editorModel;
    }

    DocumentModel* IDEFrameController::createDocumentModel(const Document *view, const std::string &fileName) {
        auto editorModel = new DocumentModel(fileName);
        
        editorModels[view] = std::unique_ptr<DocumentModel>(editorModel);

        return editorModel;
    }

    DocumentModel* IDEFrameController::getDocumentModel(const Document *view) {
        auto editorModel = editorModels[view].get();

        assert(editorModel);

        return editorModel;
    }
    
    Document* IDEFrameController::getDocument(const DocumentModel *model) {
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
    }

    void IDEFrameController::openFolder(const std::string &fullPath) {
        view->getFolderBrowser()->displayFolder(fullPath);
    }
}

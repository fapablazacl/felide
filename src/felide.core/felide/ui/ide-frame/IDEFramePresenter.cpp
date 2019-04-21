
#include "IDEFramePresenter.hpp"
#include "IDEFrame.hpp"
#include "IDEFrameModel.hpp"

#include <boost/filesystem.hpp>
#include <felide/util/FileUtil.hpp>

#include <iostream>
#include <cassert>

namespace felide {
    static std::string mapEditorTitle(const EditorModel *model) {
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

    IDEFramePresenter::IDEFramePresenter() {}

    IDEFramePresenter::~IDEFramePresenter() {}

    void IDEFramePresenter::attachView(IDEFrame *view) {
        assert(view);
        
        this->view = view;
        editorManager = view->getEditorManager();
        dialogManager = view->getDialogManager();
        
        assert(editorManager);
        assert(dialogManager);
    }

    void IDEFramePresenter::detachView() {
        view = nullptr;
    }

    void IDEFramePresenter::onFileNew() {
        int tag = model.increaseDocumentCount();

        assert(editorManager);
        auto editor = editorManager->appendEditor();
        auto editorModel = this->createEditorModel(editor, tag);

        editor->setConfig(EditorConfig::Default());
        editor->setTitle(mapEditorTitle(editorModel));
    }

    static const std::vector<FileFilter> filters = {
        {"All Files", {"*.*"}},
        {"C/C++ Files", {"*.hpp", "*.cpp", "*.hh", "*.cc", "*.h", "*.c"}},
    };
    
    void IDEFramePresenter::onFileOpen() {
        using boost::filesystem::path;
        
        const auto filePathOptional = dialogManager->showFileDialog({
           "Open File",
           FileDialogType::OpenFile,
           filters,
           ""
        });

        if (!filePathOptional) {
            return;
        }

        const std::string filePath = *filePathOptional;

        this->onEditorShow(filePath);
    }
    
    void IDEFramePresenter::onFileOpenFolder() {
        auto folderOptional = dialogManager->showFolderDialog("Open Folder ...");
        
        if (!folderOptional) {
            return;
        }
        
        this->openFolder(*folderOptional);
    }

    void IDEFramePresenter::onFileSave() {
        using boost::filesystem::path;
        
        auto editor = editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        auto editorModel = this->getEditorModel(editor);

        if (editorModel->hasFilePath()) {
            this->editorSave(editor, editorModel);
        } else {
            this->editorSaveAs(editor);
        }
    }

    void IDEFramePresenter::onFileSaveAs() {
        auto editor = editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        this->editorSaveAs(editor);
    }

    void IDEFramePresenter::onEditUndo() {
        auto editor = editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->undo();
    }

    void IDEFramePresenter::onEditRedo() {
        auto editor = editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->redo();
    }

    void IDEFramePresenter::onEditCut() {
        auto editor = editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->cut();
    }

    void IDEFramePresenter::onEditCopy() {
        auto editor = editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->copy();
    }

    void IDEFramePresenter::onEditPaste() {
        auto editor = editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->paste();
    }

    void IDEFramePresenter::onFileSaveAll() {
        std::cout << "IDEFramePresenter::fileSaveAll()" << std::endl;
    }

    void IDEFramePresenter::onFileClose() {
        auto editor = editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editorManager->closeEditor(editor);
    }

    void IDEFramePresenter::onFileExit() {
        view->close();
    }

    void IDEFramePresenter::onEditorContentModified(Editor *editor) {
        auto editorModel = this->getEditorModel(editor);

        editorModel->modify();
        editor->setTitle(mapEditorTitle(editorModel));
    }
    
    void IDEFramePresenter::onEditorCloseRequested(Editor *editor) {
        bool closeEditor = true;
        
        auto model = this->getEditorModel(editor);
        
        if (model->getModifiedFlag()) {
            DialogButton button = dialogManager->showMessageDialog("felide", "Save Changes?", DialogIcon::Question, DialogButton::YesNoCancel);
            
            switch (button) {
                case DialogButton::Yes:
                    this->editorSave(editor, model);
                    closeEditor = true;
                    break;
                    
                case DialogButton::No:
                    closeEditor = true;
                    break;

                default:
                    return;
            }
        }
        
        if (closeEditor) {
            editorModels.erase(editor);
            editorManager->closeEditor(editor);
        }
    }
    
    bool IDEFramePresenter::onCloseRequested() {
        assert(this);
        assert(dialogManager);
        DialogButton button = dialogManager->showMessageDialog("felide", "Exit?", DialogIcon::Question, DialogButton::YesNo);
        
        return button == DialogButton::Yes;
    }
    
    void IDEFramePresenter::editorSave(Editor *editor, EditorModel *editorModel) {
        editorModel->setContent(editor->getContent());
        
        const std::string fileName = editorModel->getFilePath();
        const std::string content = editorModel->getContent();
        
        FileUtil::save(fileName, content);
        
        editorModel->setFilePath(fileName);
        editorModel->setModifiedFlag(false);
        editor->setTitle(mapEditorTitle(editorModel));
    }
    
    void IDEFramePresenter::editorSaveAs(Editor *editor) {
        auto editorModel = this->getEditorModel(editor);
        
        const boost::optional<std::string> filePathOptional = dialogManager->showFileDialog({
            "Save File",
            FileDialogType::SaveFile,
            filters,
            ""
        });
        
        if (!filePathOptional) {
            return;
        }
        
        const std::string filePath = *filePathOptional;
        const std::string content = editor->getContent();
        
        editorModel->setFilePath(filePath);
        editorModel->setContent(content);
        
        this->editorSave(editor, editorModel);
    }

    void IDEFramePresenter::onEditorShow(const std::string &filePath) {
		if (boost::filesystem::is_directory(filePath)) {
			return;
		}

        auto &viewModels = editorModels;

        auto viewModelIt = std::find_if(viewModels.begin(), viewModels.end(), [filePath](const auto &pair) {
            const auto &editorModel = pair.second;

            return editorModel->hasFilePath() && editorModel->getFilePath() == filePath;
        });

        if (viewModelIt != viewModels.end()) {
            editorManager->showEditor(const_cast<Editor*>(viewModelIt->first));
        } else {
            const std::string content = FileUtil::load(filePath);

            auto editor = editorManager->appendEditor();
            auto editorModel = this->createEditorModel(editor, filePath);
            
            editor->setConfig(EditorConfig::Default());
            editor->setContent(content);
            editorModel->setModifiedFlag(false);
            editorModel->setContent(content);
            editor->setTitle(mapEditorTitle(editorModel));
        }
    }

    void IDEFramePresenter::onViewFolderBrowser() {
        // TODO: Add implementation
    }

    EditorModel* IDEFramePresenter::createEditorModel(const Editor *view, const int tag) {
        auto editorModel = new EditorModel(tag);

        editorModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    EditorModel* IDEFramePresenter::createEditorModel(const Editor *view, const std::string &fileName) {
        auto editorModel = new EditorModel(fileName);
        
        editorModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    EditorModel* IDEFramePresenter::getEditorModel(const Editor *view) {
        auto editorModel = editorModels[view].get();

        assert(editorModel);

        return editorModel;
    }
    
    Editor* IDEFramePresenter::getEditor(const EditorModel *model) {
        assert(model);
        Editor* view = nullptr;
        
        for (auto &pair : editorModels) {
            if (pair.second.get() == model) {
                // TODO: Refactor in order to prevent removal of the constness
                view = const_cast<Editor*>(pair.first);
                break;
            }
        }
        
        return view;
    }

    void IDEFramePresenter::openFolder(const std::string &fullPath) {
        view->getFolderBrowser()->displayFolder(fullPath);
    }
}

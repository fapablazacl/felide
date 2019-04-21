
#include "IDEFramePresenter.hpp"
#include "IDEFrame.hpp"
#include "IDEFrameModel.hpp"

#include "Editor.hpp"
#include "EditorModel.hpp"
#include "EditorManager.hpp"
#include "DialogManager.hpp"
#include "FolderBrowser.hpp"

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

    struct IDEFramePresenter::Private {
        IDEFrame *view = nullptr;
        IDEFrameModel model;

        EditorManager *editorManager = nullptr;
        DialogManager *dialogManager = nullptr;
        
        std::map<const Editor*, std::unique_ptr<EditorModel>> editorModels;
    };

    IDEFramePresenter::IDEFramePresenter() {
        m_impl = new IDEFramePresenter::Private();
    }

    IDEFramePresenter::~IDEFramePresenter() {
        delete m_impl;
    }

    void IDEFramePresenter::attachView(IDEFrame *view) {
        assert(view);
        
        m_impl->view = view;
        m_impl->editorManager = view->getEditorManager();
        m_impl->dialogManager = view->getDialogManager();
        
        assert(m_impl->editorManager);
        assert(m_impl->dialogManager);
    }

    void IDEFramePresenter::detachView() {
        m_impl->view = nullptr;
    }

    void IDEFramePresenter::fileNewTriggered() {
        int tag = m_impl->model.increaseDocumentCount();

        assert(m_impl->editorManager);
        auto editor = m_impl->editorManager->appendEditor();
        auto editorModel = this->createEditorModel(editor, tag);

        editor->setConfig(EditorConfig::Default());
        editor->setTitle(mapEditorTitle(editorModel));
    }

    static const std::vector<FileFilter> filters = {
        {"All Files", {"*.*"}},
        {"C/C++ Files", {"*.hpp", "*.cpp", "*.hh", "*.cc", "*.h", "*.c"}},
    };
    
    void IDEFramePresenter::fileOpenTriggered() {
        using boost::filesystem::path;
        
        const auto filePathOptional = m_impl->dialogManager->showFileDialog({
           "Open File",
           FileDialogType::OpenFile,
           filters,
           ""
        });

        if (!filePathOptional) {
            return;
        }

        const std::string filePath = *filePathOptional;

        this->editorShow(filePath);
    }
    
    void IDEFramePresenter::fileOpenFolderTriggered() {
        auto folderOptional = m_impl->dialogManager->showFolderDialog("Open Folder ...");
        
        if (!folderOptional) {
            return;
        }
        
        this->openFolder(*folderOptional);
    }

    void IDEFramePresenter::fileSaveTriggered() {
        using boost::filesystem::path;
        
        auto editor = m_impl->editorManager->getCurrentEditor();
        
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

    void IDEFramePresenter::fileSaveAsTriggered() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        this->editorSaveAs(editor);
    }

    void IDEFramePresenter::editUndo() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->undo();
    }

    void IDEFramePresenter::editRedo() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->redo();
    }

    void IDEFramePresenter::editCut() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->cut();
    }

    void IDEFramePresenter::editCopy() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->copy();
    }

    void IDEFramePresenter::editPaste() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->paste();
    }

    void IDEFramePresenter::fileSaveAllTriggered() {
        std::cout << "IDEFramePresenter::fileSaveAll()" << std::endl;
    }

    void IDEFramePresenter::fileCloseTriggered() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        m_impl->editorManager->closeEditor(editor);
    }

    void IDEFramePresenter::fileExitTriggered() {
        m_impl->view->close();
    }

    void IDEFramePresenter::editorContentModified(Editor *editor) {
        auto editorModel = this->getEditorModel(editor);

        editorModel->modify();
        editor->setTitle(mapEditorTitle(editorModel));
    }
    
    void IDEFramePresenter::editorCloseRequested(Editor *editor) {
        bool closeEditor = true;
        
        auto model = this->getEditorModel(editor);
        
        if (model->getModifiedFlag()) {
            DialogButton button = m_impl->dialogManager->showMessageDialog("felide", "Save Changes?", DialogIcon::Question, DialogButton::YesNoCancel);
            
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
            m_impl->editorModels.erase(editor);
            m_impl->editorManager->closeEditor(editor);
        }
    }
    
    bool IDEFramePresenter::closeRequested() {
        assert(this);
        assert(m_impl);
        assert(m_impl->dialogManager);
        DialogButton button = m_impl->dialogManager->showMessageDialog("felide", "Exit?", DialogIcon::Question, DialogButton::YesNo);
        
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
        
        const boost::optional<std::string> filePathOptional = m_impl->dialogManager->showFileDialog({
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

    void IDEFramePresenter::editorShow(const std::string &filePath) {
		if (boost::filesystem::is_directory(filePath)) {
			return;
		}

        auto &viewModels = m_impl->editorModels;

        auto viewModelIt = std::find_if(viewModels.begin(), viewModels.end(), [filePath](const auto &pair) {
            const auto &editorModel = pair.second;

            return editorModel->hasFilePath() && editorModel->getFilePath() == filePath;
        });

        if (viewModelIt != viewModels.end()) {
            m_impl->editorManager->showEditor(const_cast<Editor*>(viewModelIt->first));
        } else {
            const std::string content = FileUtil::load(filePath);

            auto editor = m_impl->editorManager->appendEditor();
            auto editorModel = this->createEditorModel(editor, filePath);
            
            editor->setConfig(EditorConfig::Default());
            editor->setContent(content);
            editorModel->setModifiedFlag(false);
            editorModel->setContent(content);
            editor->setTitle(mapEditorTitle(editorModel));
        }
    }

    void IDEFramePresenter::viewFolderBrowserToggle() {
        // TODO: Add implementation
    }

    EditorModel* IDEFramePresenter::createEditorModel(const Editor *view, const int tag) {
        auto editorModel = new EditorModel(tag);

        m_impl->editorModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    EditorModel* IDEFramePresenter::createEditorModel(const Editor *view, const std::string &fileName) {
        auto editorModel = new EditorModel(fileName);
        
        m_impl->editorModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    EditorModel* IDEFramePresenter::getEditorModel(const Editor *view) {
        auto editorModel = m_impl->editorModels[view].get();

        assert(editorModel);

        return editorModel;
    }
    
    Editor* IDEFramePresenter::getEditor(const EditorModel *model) {
        assert(model);
        Editor* view = nullptr;
        
        for (auto &pair : m_impl->editorModels) {
            if (pair.second.get() == model) {
                // TODO: Refactor in order to prevent removal of the constness
                view = const_cast<Editor*>(pair.first);
                break;
            }
        }
        
        return view;
    }

    void IDEFramePresenter::openFolder(const std::string &fullPath) {
        m_impl->view->getFolderBrowser()->displayFolder(fullPath);
    }
}

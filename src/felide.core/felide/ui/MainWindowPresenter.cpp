
#include "MainWindowPresenter.hpp"
#include "MainWindow.hpp"

#include "Editor.hpp"
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

    struct MainWindowPresenter::Private {
        MainWindow *view = nullptr;
        EditorManager *editorManager = nullptr;
        DialogManager *dialogManager = nullptr;
        MainWindowModel model;

        std::map<const Editor*, std::unique_ptr<EditorModel>> editorModels;
    };

    MainWindowPresenter::MainWindowPresenter() {
        m_impl = new MainWindowPresenter::Private();
    }

    MainWindowPresenter::~MainWindowPresenter() {
        delete m_impl;
    }

    void MainWindowPresenter::attachView(MainWindow *view) {
        assert(view);
        
        m_impl->view = view;
        m_impl->editorManager = view->getEditorManager();
        m_impl->dialogManager = view->getDialogManager();
        
        assert(m_impl->editorManager);
        assert(m_impl->dialogManager);
    }

    void MainWindowPresenter::detachView() {
        m_impl->view = nullptr;
    }

    void MainWindowPresenter::fileNewTriggered() {
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
    
    void MainWindowPresenter::fileOpenTriggered() {
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
    
    void MainWindowPresenter::fileOpenFolderTriggered() {
        auto folderOptional = m_impl->dialogManager->showFolderDialog("This is a tedst");
        
        if (!folderOptional) {
            return;
        }
        
        m_impl->view->getFolderBrowser()->displayFolder(*folderOptional);
    }

    void MainWindowPresenter::fileSaveTriggered() {
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

    void MainWindowPresenter::fileSaveAsTriggered() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        this->editorSaveAs(editor);
    }

    void MainWindowPresenter::editUndo() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->undo();
    }

    void MainWindowPresenter::editRedo() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->redo();
    }

    void MainWindowPresenter::editCut() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->cut();
    }

    void MainWindowPresenter::editCopy() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->copy();
    }

    void MainWindowPresenter::editPaste() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        editor->paste();
    }

    void MainWindowPresenter::fileSaveAllTriggered() {
        std::cout << "MainWindowPresenter::fileSaveAll()" << std::endl;
    }

    void MainWindowPresenter::fileCloseTriggered() {
        auto editor = m_impl->editorManager->getCurrentEditor();
        
        if (!editor) {
            return;
        }

        m_impl->editorManager->closeEditor(editor);
    }

    void MainWindowPresenter::fileExitTriggered() {
        m_impl->view->close();
    }

    void MainWindowPresenter::editorContentModified(Editor *editor) {
        auto editorModel = this->getEditorModel(editor);

        editorModel->modify();
        editor->setTitle(mapEditorTitle(editorModel));
    }
    
    void MainWindowPresenter::editorCloseRequested(Editor *editor) {
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
            m_impl->editorManager->closeEditor(editor);
        }
    }
    
    bool MainWindowPresenter::closeRequested() {
        assert(this);
        assert(m_impl);
        assert(m_impl->dialogManager);
        DialogButton button = m_impl->dialogManager->showMessageDialog("felide", "Exit?", DialogIcon::Question, DialogButton::YesNo);
        
        return button == DialogButton::Yes;
    }
    
    void MainWindowPresenter::editorSave(Editor *editor, EditorModel *editorModel) {
        editorModel->setContent(editor->getContent());
        
        const std::string fileName = editorModel->getFilePath();
        const std::string content = editorModel->getContent();
        
        FileUtil::save(fileName, content);
        
        editorModel->setFilePath(fileName);
        editorModel->setModifiedFlag(false);
        editor->setTitle(mapEditorTitle(editorModel));
    }
    
    void MainWindowPresenter::editorSaveAs(Editor *editor) {
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

    void MainWindowPresenter::editorShow(const std::string &filePath) {
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

    EditorModel* MainWindowPresenter::createEditorModel(const Editor *view, const int tag) {
        auto editorModel = new EditorModel(tag);

        m_impl->editorModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    EditorModel* MainWindowPresenter::createEditorModel(const Editor *view, const std::string &fileName) {
        auto editorModel = new EditorModel(fileName);
        
        m_impl->editorModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    EditorModel* MainWindowPresenter::getEditorModel(const Editor *view) {
        auto editorModel = m_impl->editorModels[view].get();

        assert(editorModel);

        return editorModel;
    }
    
    Editor* MainWindowPresenter::getEditor(const EditorModel *model) {
        assert(model);
        Editor* view = nullptr;
        
        for (auto &pair : m_impl->editorModels) {
            if (pair.second.get() == model) {
                // TODO: Refactor in order to prevent remove the constness of the keys
                view = const_cast<Editor*>(pair.first);
                break;
            }
        }
        
        return view;
    }
}

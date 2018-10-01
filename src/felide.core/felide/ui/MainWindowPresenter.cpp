
#include "MainWindowPresenter.hpp"
#include "MainWindowView.hpp"

#include "EditorView.hpp"
#include "EditorManagerView.hpp"
#include "DialogManagerView.hpp"
#include "FolderBrowserView.hpp"

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
        MainWindowView *view = nullptr;
        EditorManagerView *editorManager = nullptr;
        DialogManagerView *dialogManager = nullptr;
        MainWindowModel model;

        std::map<const EditorView*, std::unique_ptr<EditorModel>> editorViewModels;
    };

    MainWindowPresenter::MainWindowPresenter() {
        m_impl = new MainWindowPresenter::Private();
    }

    MainWindowPresenter::~MainWindowPresenter() {
        delete m_impl;
    }

    void MainWindowPresenter::attachView(MainWindowView *view) {
        assert(view);
        
        m_impl->view = view;
        m_impl->editorManager = view->getEditorManagerView();
        m_impl->dialogManager = view->getDialogManagerView();
        
        assert(m_impl->editorManager);
        assert(m_impl->dialogManager);
    }

    void MainWindowPresenter::detachView() {
        m_impl->view = nullptr;
    }

    void MainWindowPresenter::fileNewTriggered() {
        int tag = m_impl->model.increaseDocumentCount();

        assert(m_impl->editorManager);
        auto editorView = m_impl->editorManager->appendEditor();
        auto editorModel = this->createEditorModel(editorView, tag);

        editorView->setConfig(EditorConfig::Default());
        editorView->setTitle(mapEditorTitle(editorModel));
    }

    static const std::vector<FileFilter> filters = {
        {"All Files", {"*.*"}},
        {"C/C++ Files", {"*.hpp", "*.cpp", "*.hh", "*.cc", "*.h", "*.c"}},
    };
    
    void MainWindowPresenter::fileOpenTriggered() {
        using boost::filesystem::path;
        
        const auto filePathOptional = m_impl->dialogManager->showFileDialog(
           "Open File",
           FileDialogType::OpenFile,
           filters
        );

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
        
        m_impl->view->getFolderBrowserView()->displayFolder(*folderOptional);
    }

    void MainWindowPresenter::fileSaveTriggered() {
        using boost::filesystem::path;
        
        auto editorView = m_impl->editorManager->getCurrentEditor();
        
        if (!editorView) {
            return;
        }

        auto editorModel = this->getEditorModel(editorView);

        if (editorModel->hasFilePath()) {
            this->editorSave(editorView, editorModel);
        } else {
            this->editorSaveAs(editorView);
        }
    }

    void MainWindowPresenter::fileSaveAsTriggered() {
        auto editorView = m_impl->editorManager->getCurrentEditor();
        
        if (!editorView) {
            return;
        }

        this->editorSaveAs(editorView);
    }

    void MainWindowPresenter::editUndo() {
        std::cout << "MainWindowPresenter::editUndo()" << std::endl;

        auto editorView = m_impl->editorManager->getCurrentEditor();
        
        if (!editorView) {
            return;
        }

        editorView->undo();
    }

    void MainWindowPresenter::editRedo() {
        std::cout << "MainWindowPresenter::editRedo()" << std::endl;

        auto editorView = m_impl->editorManager->getCurrentEditor();
        
        if (!editorView) {
            return;
        }

        editorView->redo();
    }

    void MainWindowPresenter::editCut() {
        std::cout << "MainWindowPresenter::editCut()" << std::endl;

        auto editorView = m_impl->editorManager->getCurrentEditor();
        
        if (!editorView) {
            return;
        }

        editorView->cut();
    }

    void MainWindowPresenter::editCopy() {
        std::cout << "MainWindowPresenter::editCopy()" << std::endl;

        auto editorView = m_impl->editorManager->getCurrentEditor();
        
        if (!editorView) {
            return;
        }

        editorView->copy();
    }

    void MainWindowPresenter::editPaste() {
        std::cout << "MainWindowPresenter::editPaste()" << std::endl;

        auto editorView = m_impl->editorManager->getCurrentEditor();
        
        if (!editorView) {
            return;
        }

        editorView->paste();
    }

    void MainWindowPresenter::fileSaveAllTriggered() {
        std::cout << "MainWindowPresenter::fileSaveAll()" << std::endl;
    }

    void MainWindowPresenter::fileCloseTriggered() {
        std::cout << "MainWindowPresenter::fileClose()" << std::endl;
    }

    void MainWindowPresenter::fileExitTriggered() {
        m_impl->view->close();
    }

    void MainWindowPresenter::editorContentModified(EditorView *editorView) {
        auto editorModel = this->getEditorModel(editorView);

        editorModel->modify();
        editorView->setTitle(mapEditorTitle(editorModel));
    }
    
    void MainWindowPresenter::editorCloseRequested(EditorView *editorView) {
        bool closeEditor = true;
        
        auto model = this->getEditorModel(editorView);
        
        if (model->getModifiedFlag()) {
            DialogButton button = m_impl->dialogManager->showMessageDialog("felide", "Save Changes?", DialogIcon::Question, DialogButton::YesNoCancel);
            
            switch (button) {
                case DialogButton::Yes:
                    this->editorSave(editorView, model);
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
            m_impl->editorManager->closeEditor(editorView);
        }
    }
    
    bool MainWindowPresenter::closeRequested() {
        DialogButton button = m_impl->dialogManager->showMessageDialog("felide", "Exit?", DialogIcon::Question, DialogButton::YesNo);
        
        return button == DialogButton::Yes;
    }
    
    void MainWindowPresenter::editorSave(EditorView *editorView, EditorModel *editorModel) {
        editorModel->setContent(editorView->getContent());
        
        const std::string fileName = editorModel->getFilePath();
        const std::string content = editorModel->getContent();
        
        FileUtil::save(fileName, content);
        
        editorModel->setFilePath(fileName);
        editorModel->setModifiedFlag(false);
        editorView->setTitle(mapEditorTitle(editorModel));
    }
    
    void MainWindowPresenter::editorSaveAs(EditorView *editorView) {
        auto editorModel = this->getEditorModel(editorView);
        
        const boost::optional<std::string> filePathOptional = m_impl->dialogManager->showFileDialog(
            "Save File",
            FileDialogType::SaveFile,
            filters
        );
        
        if (!filePathOptional) {
            return;
        }
        
        const std::string filePath = *filePathOptional;
        const std::string content = editorView->getContent();
        
        editorModel->setFilePath(filePath);
        editorModel->setContent(content);
        
        this->editorSave(editorView, editorModel);
    }

    void MainWindowPresenter::editorShow(const std::string &filePath) {
        auto &viewModels = m_impl->editorViewModels;

        auto viewModelIt = std::find_if(viewModels.begin(), viewModels.end(), [filePath](const auto &pair) {
            const auto &editorModel = pair.second;

            return editorModel->hasFilePath() && editorModel->getFilePath() == filePath;
        });

        if (viewModelIt != viewModels.end()) {
            m_impl->editorManager->showEditor(const_cast<EditorView*>(viewModelIt->first));
        } else {
            const std::string content = FileUtil::load(filePath);

            auto editorView = m_impl->editorManager->appendEditor();
            auto editorModel = this->createEditorModel(editorView, filePath);
            
            editorView->setConfig(EditorConfig::Default());
            editorView->setContent(content);
            editorModel->setModifiedFlag(false);
            editorModel->setContent(content);
            editorView->setTitle(mapEditorTitle(editorModel));
        }
    }

    EditorModel* MainWindowPresenter::createEditorModel(const EditorView *view, const int tag) {
        auto editorModel = new EditorModel(tag);

        m_impl->editorViewModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    EditorModel* MainWindowPresenter::createEditorModel(const EditorView *view, const std::string &fileName) {
        auto editorModel = new EditorModel(fileName);
        
        m_impl->editorViewModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    EditorModel* MainWindowPresenter::getEditorModel(const EditorView *view) {
        auto editorModel = m_impl->editorViewModels[view].get();

        assert(editorModel);

        return editorModel;
    }
    
    EditorView* MainWindowPresenter::getEditorView(const EditorModel *model) {
        assert(model);
        EditorView* view = nullptr;
        
        for (auto &pair : m_impl->editorViewModels) {
            if (pair.second.get() == model) {
                // TODO: Refactor in order to prevent remove the constness of the keys
                view = const_cast<EditorView*>(pair.first);
                break;
            }
        }
        
        return view;
    }
}

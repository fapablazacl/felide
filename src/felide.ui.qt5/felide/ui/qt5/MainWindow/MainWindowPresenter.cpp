
#include "MainWindowPresenter.hpp"
#include "MainWindowView.hpp"

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

    MainWindowPresenter::MainWindowPresenter() {}

    MainWindowPresenter::~MainWindowPresenter() {}

    void MainWindowPresenter::attachView(MainWindowView *view) {
        m_view = view;
        m_editorManager = view->getEditorManagerView();
        assert(m_editorManager);
    }

    void MainWindowPresenter::detachView() {
        m_view = nullptr;
    }

    void MainWindowPresenter::fileNew() {
        int tag = m_model.increaseDocumentCount();

        auto editorView = m_editorManager->appendEditor();
        auto editorModel = this->createEditorModel(editorView, tag);

        editorView->setConfig(EditorConfig::Default());
        editorView->setTitle(mapEditorTitle(editorModel));
    }

    static const std::vector<DialogViewData::FileFilter> filters = {
        {"All Files", {"*.*"}},
        {"C/C++ Files", {"*.hpp", "*.cpp", "*.hh", "*.cc"}},
    };
    
    void MainWindowPresenter::fileOpen() {
        using boost::filesystem::path;
        
        DialogViewData dialogData = {
            DialogType::OpenFile,
            "Open File",
            filters
        };
        
        auto fileNameOpt = m_view->showDialogModal(dialogData);
        if (!fileNameOpt) {
            return;
        }

        const std::string fileName = *fileNameOpt;
        const std::string content = FileUtil::load(fileName);

        auto editorView = m_editorManager->appendEditor();
        auto editorModel = this->createEditorModel(editorView, fileName);
        
        editorModel->setContent(content);
        editorModel->setModifiedFlag(false);

        editorView->setConfig(EditorConfig::Default());
        editorView->setTitle(mapEditorTitle(editorModel));
        editorView->setContent(content);
    }

    void MainWindowPresenter::fileSave() {
        using boost::filesystem::path;
        
        auto editorView = m_editorManager->getCurrentEditor();
        
        if (!editorView) {
            return;
        }

        auto editorModel = this->getEditorModel(editorView);

        if (editorModel->hasFilePath()) {
            this->saveFile(editorView, editorModel);
        } else {
            this->handleSaveAs(editorView);
        }
    }

    void MainWindowPresenter::fileSaveAs() {
        using boost::filesystem::path;
        
        auto editorView = m_editorManager->getCurrentEditor();
        
        if (!editorView) {
            return;
        }

        this->handleSaveAs(editorView);
    }

    void MainWindowPresenter::fileSaveAll() {
        std::cout << "MainWindowPresenter::fileSaveAll()" << std::endl;
    }

    void MainWindowPresenter::fileClose() {
        std::cout << "MainWindowPresenter::fileClose()" << std::endl;
    }

    void MainWindowPresenter::fileExit() {
        std::cout << "MainWindowPresenter::fileExit()" << std::endl;
    }

    void MainWindowPresenter::editorContentModified(EditorView *editorView) {
        auto editorModel = this->getEditorModel(editorView);

        editorModel->modify();
        editorView->setTitle(mapEditorTitle(editorModel));
    }

    EditorModel* MainWindowPresenter::createEditorModel(const EditorView *view, const int tag) {
        auto editorModel = new EditorModel(tag);

        editorViewModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    EditorModel* MainWindowPresenter::createEditorModel(const EditorView *view, const std::string &fileName) {
        auto editorModel = new EditorModel(fileName);
        
        editorViewModels[view] = std::unique_ptr<EditorModel>(editorModel);

        return editorModel;
    }

    void MainWindowPresenter::handleSaveAs(EditorView *editorView) {
        auto editorModel = this->getEditorModel(editorView);
        
        DialogViewData dialogData = {
            DialogType::SaveFile,
            "Save File",
            filters
        };
        
        auto fileNameOpt = m_view->showDialogModal(dialogData);
        if (!fileNameOpt) {
            return;
        }
        
        const std::string fileName = *fileNameOpt;
        const std::string content = editorView->getContent();

        editorModel->setFilePath(fileName);
        editorModel->setContent(content);

        this->saveFile(editorView, editorModel);
    }

    EditorModel* MainWindowPresenter::getEditorModel(const EditorView *view) {
        auto editorModel = editorViewModels[view].get();

        assert(editorModel);

        return editorModel;
    }

    void MainWindowPresenter::saveFile(EditorView *editorView, EditorModel *editorModel) {
        const std::string fileName = editorModel->getFilePath();
        const std::string content = editorModel->getContent();

        FileUtil::save(fileName, content);
        
        editorModel->setFilePath(fileName);
        editorModel->setContent(content);
        
        editorModel->setModifiedFlag(false);
        editorView->setContent(content);
        editorView->setTitle(mapEditorTitle(editorModel));
    }
}

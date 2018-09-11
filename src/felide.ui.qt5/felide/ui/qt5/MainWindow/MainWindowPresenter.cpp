
#include "MainWindowPresenter.hpp"
#include "MainWindowView.hpp"

#include <boost/filesystem.hpp>
#include <felide/util/FileUtil.hpp>

#include <iostream>

namespace felide {
    static std::string mapEditorTitle(const EditorModel *model) {
        std::string title;

        if (model->hasFilePath()) {
            using boost::filesystem::path;

            title = path(model->getFilePath()).filename().string();
        } else {
            title = "Untitled" + std::to_string(model->getTag());
        }

        title = model->getModifiedFlag() ? "[*]" : "" + title;

        return title;
    }

    MainWindowPresenter::MainWindowPresenter() {}

    MainWindowPresenter::~MainWindowPresenter() {}

    void MainWindowPresenter::attachView(MainWindowView *view) {
        m_view = view;
    }

    void MainWindowPresenter::detachView() {
        m_view = nullptr;
    }

    void MainWindowPresenter::fileNew() {
        int tag = m_model.increaseDocumentCount();

        auto editorManager = m_view->getEditorManagerView();
        auto editorView = editorManager->appendEditor();
        auto editorModel = this->createEditorModel(editorView, tag);

        editorView->setConfig(EditorConfig::Default());
        editorView->setTitle(mapEditorTitle(editorModel));
    }

    void MainWindowPresenter::fileOpen() {
        using boost::filesystem::path;

        DialogViewData dialogData = {
            DialogType::OpenFile,
            "Open File",
            {
                {"All Files", {"*.*"}},
                {"C/C++ Files", {"*.hpp", "*.cpp", "*.hh", "*.cc"}},
            }
        };

        auto fileNameOpt = m_view->showDialogModal(dialogData);
        if (!fileNameOpt) {
            return;
        }

        const std::string fileName = *fileNameOpt;
        const std::string content = FileUtil::load(fileName);

        auto editorManager = m_view->getEditorManagerView();
        auto editorView = editorManager->appendEditor();
        auto editorModel = this->createEditorModel(editorView, fileName);

        editorView->setConfig(EditorConfig::Default());
        editorView->setTitle(mapEditorTitle(editorModel));
        editorView->setContent(content);
    }

    void MainWindowPresenter::fileSave() {
        std::cout << "MainWindowPresenter::fileSave()" << std::endl;

        /*
        EditorView *editor = view->getCurrentEditor();

        if (!editor) {
            return;
        }
        */
    }

    void MainWindowPresenter::fileSaveAs() {
        std::cout << "MainWindowPresenter::fileSaveAs()" << std::endl;

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
        auto editorModel = editorViewModels[editorView].get();

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
}

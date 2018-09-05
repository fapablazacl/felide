
#include "MainWindowPresenter.hpp"
#include "MainWindowView.hpp"

#include <felide/util/FileUtil.hpp>

#include <iostream>

namespace felide {
    MainWindowPresenter::MainWindowPresenter() {}

    void MainWindowPresenter::attachView(MainWindowView *view) {
        m_view = view;
    }

    void MainWindowPresenter::detachView() {
        m_view = nullptr;
    }

    void MainWindowPresenter::fileNew() {
        std::cout << "MainWindowPresenter::fileNew()" << std::endl;

        auto editorManager = m_view->getEditorManagerView();
        auto editor = editorManager->appendEditor();

        const int documentCount = m_model.increaseDocumentCount();

        editor->setTitle("Untitled " + std::to_string(documentCount));
    }

    void MainWindowPresenter::fileOpen() {
        FileDialogViewData dialogData = {
            "Open File",
            {
                {"All Files", {"*.*"}},
                {"C/C++ Files", {"*.hpp", "*.cpp", "*.hh", "*.cc"}},
            }
        };

        auto fileNameOpt = m_view->openFileDialog(dialogData);
        if (!fileNameOpt) {
            return;
        }

        const std::string fileName = *fileNameOpt;
        const std::string content = FileUtil::load(fileName);

        auto editorManager = m_view->getEditorManagerView();
        auto editor = editorManager->appendEditor();

        editor->setConfig(EditorConfig::Default());
        editor->setTitle(fileName);
        editor->setContent(content);
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
}

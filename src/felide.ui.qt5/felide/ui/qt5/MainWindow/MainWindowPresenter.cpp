
#include "MainWindowPresenter.hpp"
#include "MainWindowView.hpp"

#include <iostream>

namespace felide {
    MainWindowPresenter::MainWindowPresenter() {}

    void MainWindowPresenter::attachView(MainWindowView *view) {
        this->view = view;
    }

    void MainWindowPresenter::detachView() {
        view = nullptr;
    }

    void MainWindowPresenter::fileNew() {
        std::cout << "MainWindowPresenter::fileNew()" << std::endl;

        /*
        const int documentCount = model.increaseDocumentCount();

        EditorView *editorView = view->appendEditor();

        editorView->setTitle("Untitled " + std::to_string(documentCount));
        */
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

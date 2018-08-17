
#include "MainWindowPresenter.hpp"
#include "MainWindowView.hpp"

namespace felide {
    MainWindowPresenter::MainWindowPresenter(MainWindowView *view) {
        this->view = view;
    }

    void MainWindowPresenter::fileNew() {
        const int documentCount = model.increaseDocumentCount();

        EditorView *editorView = view->appendEditor();

        editorView->setTitle("Untitled " + documentCount);
    }

    void MainWindowPresenter::fileSave() {
        EditorView *editor = view->getCurrentEditor();

        if (!editor) {
            return;
        }

        if (editor->isDirty()) {
            // TODO: Add concrete file-saving option
        }

        if (editor->)
    }

    void MainWindowPresenter::fileSaveAs() {

    }

    void MainWindowPresenter::fileSaveAll() {

    }

    void MainWindowPresenter::fileClose() {

    }

    void MainWindowPresenter::fileExit() {

    }
}

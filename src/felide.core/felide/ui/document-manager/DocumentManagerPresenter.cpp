
#include "DocumentManagerPresenter.hpp"
#include "DocumentManager.hpp"

namespace felide {
    DocumentManagerPresenter::DocumentManagerPresenter(DocumentManagerModel *model) {
        this->model = model;
    }

    void DocumentManagerPresenter::attachView(DocumentManager *view) {
        this->view = view;
    }

    void DocumentManagerPresenter::onCloseDocument(Document *editor) {
        view->closeDocument(editor);
    }

    void DocumentManagerPresenter::onCloseOthers(Document *editor) {
        auto editors = view->enumerateDocuments();
        
        for (auto current : editors) {
            if (current != editor) {
                view->closeDocument(current);
            }
        }
    }

    void DocumentManagerPresenter::onCloseToTheRight(Document *editor) {
        bool close = false;

        auto editors = view->enumerateDocuments();

        for (auto current : editors) {
            if (close == true) {
                view->closeDocument(current);
            }

            if (current == editor) {
                close = true;
            }
        }
    }

    void DocumentManagerPresenter::onCloseAll() {
        auto editors = view->enumerateDocuments();

        for (auto editor : editors) {
            view->closeDocument(editor);
        }
    }
}


#include "DocumentManagerPresenter.hpp"
#include "DocumentManager.hpp"

namespace felide {
    DocumentManagerPresenter::DocumentManagerPresenter(DocumentManagerModel *model) {
        this->model = model;
    }

    void DocumentManagerPresenter::attachView(DocumentManager *view) {
        this->view = view;
    }

    void DocumentManagerPresenter::onCloseDocument(Document *document) {
        view->closeDocument(document);
    }

    void DocumentManagerPresenter::onCloseOthers(Document *document) {
        auto documents = view->enumerateDocuments();
        
        for (auto current : documents) {
            if (current != document) {
                view->closeDocument(current);
            }
        }
    }

    void DocumentManagerPresenter::onCloseToTheRight(Document *document) {
        bool close = false;

        auto documents = view->enumerateDocuments();

        for (auto current : documents) {
            if (close == true) {
                view->closeDocument(current);
            }

            if (current == document) {
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

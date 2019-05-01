
#include "DocumentManagerController.hpp"
#include "DocumentManager.hpp"

namespace felide {
    DocumentManagerPresenter::DocumentManagerPresenter(DocumentManagerModel *model) {
        m_model = model;
    }

    void DocumentManagerPresenter::attachView(DocumentManager *view) {
        m_view = view;
    }

    void DocumentManagerPresenter::onCloseDocument(Document *editor) {
        m_view->closeDocument(editor);
    }

    void DocumentManagerPresenter::onCloseOthers(Document *editor) {
        auto editors = m_view->enumerateDocuments();
        
        for (auto current : editors) {
            if (current != editor) {
                m_view->closeDocument(current);
            }
        }
    }

    void DocumentManagerPresenter::onCloseToTheRight(Document *editor) {
        bool close = false;

        auto editors = m_view->enumerateDocuments();

        for (auto current : editors) {
            if (close == true) {
                m_view->closeDocument(current);
            }

            if (current == editor) {
                close = true;
            }
        }
    }

    void DocumentManagerPresenter::onCloseAll() {
        auto editors = m_view->enumerateDocuments();

        for (auto editor : editors) {
            m_view->closeDocument(editor);
        }
    }
}

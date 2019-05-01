
#include "DocumentManagerController.hpp"
#include "DocumentManager.hpp"

namespace felide {
    DocumentManagerController::DocumentManagerController(DocumentManagerModel *model) {
        m_model = model;
    }

    void DocumentManagerController::attachView(DocumentManager *view) {
        m_view = view;
    }

    void DocumentManagerController::onCloseDocument(Document *editor) {
        m_view->closeDocument(editor);
    }

    void DocumentManagerController::onCloseOthers(Document *editor) {
        auto editors = m_view->enumerateDocuments();
        
        for (auto current : editors) {
            if (current != editor) {
                m_view->closeDocument(current);
            }
        }
    }

    void DocumentManagerController::onCloseToTheRight(Document *editor) {
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

    void DocumentManagerController::onCloseAll() {
        auto editors = m_view->enumerateDocuments();

        for (auto editor : editors) {
            m_view->closeDocument(editor);
        }
    }
}

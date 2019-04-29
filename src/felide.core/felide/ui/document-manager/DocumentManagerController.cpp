
#include "EditorManagerController.hpp"
#include "EditorManager.hpp"

namespace felide {
    DocumentManagerController::DocumentManagerController(DocumentManagerModel *model) {
        m_model = model;
    }

    void DocumentManagerController::attachView(DocumentManager *view) {
        m_view = view;
    }

    void DocumentManagerController::onCloseEditor(Document *editor) {
        m_view->closeEditor(editor);
    }

    void DocumentManagerController::onCloseOthers(Document *editor) {
        auto editors = m_view->getEditors();
        
        for (auto current : editors) {
            if (current != editor) {
                m_view->closeEditor(current);
            }
        }
    }

    void DocumentManagerController::onCloseToTheRight(Document *editor) {
        bool close = false;

        auto editors = m_view->getEditors();

        for (auto current : editors) {
            if (close == true) {
                m_view->closeEditor(current);
            }

            if (current == editor) {
                close = true;
            }
        }
    }

    void DocumentManagerController::onCloseAll() {
        auto editors = m_view->getEditors();

        for (auto editor : editors) {
            m_view->closeEditor(editor);
        }
    }
}

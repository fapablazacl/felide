
#include "EditorManagerController.hpp"
#include "EditorManager.hpp"

namespace felide {
    EditorManagerController::EditorManagerController(EditorManagerModel *model) {
        m_model = model;
    }

    void EditorManagerController::attachView(EditorManager *view) {
        m_view = view;
    }

    void EditorManagerController::onCloseEditor(Editor *editor) {
        m_view->closeEditor(editor);
    }

    void EditorManagerController::onCloseOthers(Editor *editor) {
        auto editors = m_view->getEditors();
        
        for (auto current : editors) {
            if (current != editor) {
                m_view->closeEditor(current);
            }
        }
    }

    void EditorManagerController::onCloseToTheRight(Editor *editor) {
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

    void EditorManagerController::onCloseAll() {
        auto editors = m_view->getEditors();

        for (auto editor : editors) {
            m_view->closeEditor(editor);
        }
    }
}

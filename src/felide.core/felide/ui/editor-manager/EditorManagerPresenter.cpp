
#include "EditorManagerPresenter.hpp"
#include "EditorManager.hpp"

namespace felide {
    EditorManagerPresenter::EditorManagerPresenter(EditorManagerModel *model) {
        m_model = model;
    }

    void EditorManagerPresenter::attachView(EditorManager *view) {
        m_view = view;
    }

    void EditorManagerPresenter::onCloseEditor(Editor *editor) {
        m_view->closeEditor(editor);
    }

    void EditorManagerPresenter::onCloseOthers(Editor *editor) {
        auto editors = m_view->getEditors();
        
        for (auto current : editors) {
            if (current != editor) {
                m_view->closeEditor(current);
            }
        }
    }

    void EditorManagerPresenter::onCloseToTheRight(Editor *editor) {
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

    void EditorManagerPresenter::onCloseAll() {
        auto editors = m_view->getEditors();

        for (auto editor : editors) {
            m_view->closeEditor(editor);
        }
    }
}

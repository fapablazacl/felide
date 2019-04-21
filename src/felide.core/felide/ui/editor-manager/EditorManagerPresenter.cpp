
#include "EditorManagerPresenter.hpp"
#include "EditorManager.hpp"

namespace felide {
    EditorManagerPresenter::EditorManagerPresenter(EditorManagerModel *model) {
        m_model = model;
    }

    void EditorManagerPresenter::attachView(EditorManager *view) {
        m_view = view;
    }

    void EditorManagerPresenter::closeEditor(Editor *editor) {
        m_view->closeEditor(editor);
    }

    void EditorManagerPresenter::closeOthers(Editor *editor) {
        auto editors = m_view->getEditors();
        
        for (auto current : editors) {
            if (current != editor) {
                m_view->closeEditor(current);
            }
        }
    }

    void EditorManagerPresenter::closeToTheRight(Editor *editor) {
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

    void EditorManagerPresenter::closeAll() {
        auto editors = m_view->getEditors();

        for (auto editor : editors) {
            m_view->closeEditor(editor);
        }
    }
}

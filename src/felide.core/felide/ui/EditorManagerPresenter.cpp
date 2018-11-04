
#include "EditorManagerPresenter.hpp"
#include "EditorManager.hpp"

namespace felide {
    void EditorManagerPresenter::attachView(EditorManager *view) {
        m_view = view;
    }

    void EditorManagerPresenter::closeEditor(Editor *editor) {
        m_view->closeEditor(editor);
    }

    void EditorManagerPresenter::closeOthers(Editor *editor) {
        for (int i=0; i<m_view->getEditorCount(); i++) {
            Editor *current = m_view->getEditor(i);

            if (current != editor) {
                m_view->closeEditor(current);
            }
        }
    }

    void EditorManagerPresenter::closeToTheRight(Editor *editor) {
        bool close = false;

        for (int i=0; i<m_view->getEditorCount(); i++) {
            Editor *current = m_view->getEditor(i);

            if (close == true) {
                m_view->closeEditor(current);
            }

            if (current == editor) {
                close = true;
            }
        }
    }

    void EditorManagerPresenter::closeAll() {
        for (int i=0; i<m_view->getEditorCount(); i++) {
            m_view->closeEditor(m_view->getEditor(i));
        }
    }
}

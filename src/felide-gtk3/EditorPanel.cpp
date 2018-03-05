
#include "EditorPanel.hpp"
#include "Editor.hpp"

namespace Felide::GTK3 {
    EditorPanel::EditorPanel() {
        add(m_notebook);
        m_notebook.show();
    }

    void EditorPanel::OpenEditor(const std::string &key, const std::string &title, const std::string &content) {
        auto it = m_editors.find(key);

        Editor *editor = nullptr;

        if (it == m_editors.end()) {
            editor = new Editor();

            editor->set_text(content);
            editor->show();

            m_notebook.append_page(*editor, title);
            m_editors[key] = editor;
        } else {
            editor = it->second;
        }

        const int pageIndex = m_notebook.page_num(*editor);
        m_notebook.set_current_page(pageIndex);
    }

    Editor* EditorPanel::GetCurrentEditor() const {
        return nullptr;
    }
}

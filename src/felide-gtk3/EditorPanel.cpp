
#include "EditorPanel.hpp"
#include "Editor.hpp"

namespace Felide::GTK3 {
    EditorPanel::EditorPanel() {
        add(m_notebook);
        m_notebook.show();
    }

    void EditorPanel::OpenEditor(const std::string &title, const std::string &content) {
        Editor *editor = new Editor();

        editor->set_text(content);
        editor->show();

        m_notebook.append_page(*editor, title);
    }

    Editor* EditorPanel::GetCurrentEditor() const {
        return nullptr;
    }
}

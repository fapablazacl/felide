
#include "Editor.hpp"

namespace Felide::GTK3 {
    Editor::Editor() {
        add(m_scrolled);

        m_scrolled.set_border_width(5);
        m_scrolled.add(m_textView);
        m_scrolled.show();
        m_textView.show();
    }

    void Editor::set_text(const std::string &text) {
        m_textView.get_buffer()->set_text(text);
    }

    std::string Editor::get_text() const {
        return m_textView.get_buffer()->get_text();
    }
}

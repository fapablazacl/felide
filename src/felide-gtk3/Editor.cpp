
#include "Editor.hpp"

namespace Felide::GTK3 {
    Editor::Editor(const std::string &key) {
        add(m_scrolled);

        m_scrolled.set_border_width(5);
        m_scrolled.add(m_textView);
        m_scrolled.show();
        m_textView.show();

        m_key = key;
    }

    void Editor::set_text(const std::string &text) {
        m_textView.get_buffer()->set_text(text);
    }

    std::string Editor::get_text() const {
        return m_textView.get_buffer()->get_text();
    }

    std::string Editor::get_key() const {
        return m_key;
    }

    void Editor::set_stored_flag(const bool flag) {
        m_stored_flag = flag;
    }

    bool Editor::get_stored_flag() const {
        return m_stored_flag;
    }

    void Editor::set_dirty_flag(const bool flag) {
        m_dirty_flag = flag;
    }

    bool Editor::get_dirty_flag() const {
        return m_dirty_flag;
    }
}

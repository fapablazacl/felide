
#include "Editor.hpp"

#include <iostream>

namespace Felide::GTK3 {
    Editor::Editor(const std::string &key) {
        add(m_scrolled);

        m_scrolled.set_border_width(5);
        m_scrolled.add(m_textView);
        m_scrolled.show();
        m_textView.show();

        m_key = key;

        // TODO: Refactor out into configuration settings
        m_textView.set_show_line_numbers(true);
        m_textView.set_highlight_current_line(true);
        m_textView.set_tab_width(4);
        m_textView.set_monospace(true);
        m_textView.get_buffer()->signal_changed().connect(sigc::mem_fun(*this, &Editor::on_text_buffer_changed));
    }

    void Editor::on_text_buffer_changed() {
        set_dirty_flag(true);
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

    void Editor::set_dirty_flag(const bool flag) {
        if (m_dirty_flag != flag) {
            m_dirty_flag = flag;
            m_signal_editor_dirty_changed();
        }
    }

    bool Editor::get_dirty_flag() const {
        return m_dirty_flag;
    }
}


#include "Editor.hpp"

#include <iostream>
#include <gtksourceviewmm.h>

namespace felide::gtk3 {
    class EditorImpl : public Editor {
    public:
        explicit EditorImpl(const std::string &key) {
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
            m_textView.get_buffer()->signal_changed().connect(sigc::mem_fun(*this, &EditorImpl::on_text_buffer_changed));
        }

        virtual ~EditorImpl() {}

        virtual void set_text(const std::string &text) override {
            m_textView.get_buffer()->set_text(text);
        }

        virtual std::string get_text() const override {
            return m_textView.get_buffer()->get_text();
        }

        virtual std::string get_key() const override {
            return m_key;
        }

        virtual void set_dirty_flag(const bool flag) override {
            if (m_dirty_flag != flag) {
                m_dirty_flag = flag;
                m_signal_editor_dirty_changed();
            }
        }

        virtual bool get_dirty_flag() const override {
            return m_dirty_flag;
        }

        virtual signal_editor_dirty_changed_t signal_editor_dirty_changed() override {
            return m_signal_editor_dirty_changed;
        }

    private:
        void on_text_buffer_changed() {
            set_dirty_flag(true);
        }

    private:
        std::string m_key;
        mutable bool m_dirty_flag = false;
        Gtk::ScrolledWindow m_scrolled;
        Gsv::View m_textView;

        signal_editor_dirty_changed_t m_signal_editor_dirty_changed;
    };

    Glib::RefPtr<Editor> Editor::create(const std::string &key) {
        return Glib::RefPtr<Editor>(new EditorImpl(key));
    }
}

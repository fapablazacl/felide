
#ifndef __FELIDE_GTK3_EDITOR_HPP__
#define __FELIDE_GTK3_EDITOR_HPP__

#include <string>
#include <gtkmm.h>
#include <gtksourceviewmm.h>

namespace Felide::GTK3 {
    /**
     * @brief A Simple Text Editor control with scrollbars
     */
    class Editor : public Gtk::Bin {
    public:
        typedef sigc::signal<void> signal_editor_dirty_changed_t;

        signal_editor_dirty_changed_t& signal_editor_dirty_changed() {
            return m_signal_editor_dirty_changed;
        }

    public:
        explicit Editor(const std::string &key);

        void set_text(const std::string &text);

        std::string get_text() const;

        std::string get_key() const;

        void set_dirty_flag(const bool flag);

        bool get_dirty_flag() const;

    private:
        void on_text_buffer_changed();
        
    private:
        //! The Item identifier
        std::string m_key;
        mutable bool m_dirty_flag = false;
        Gtk::ScrolledWindow m_scrolled;
        Gsv::View m_textView;

        signal_editor_dirty_changed_t m_signal_editor_dirty_changed;
    };
}

#endif

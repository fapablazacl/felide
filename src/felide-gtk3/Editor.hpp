
#ifndef __FELIDE_GTK3_EDITOR_HPP__
#define __FELIDE_GTK3_EDITOR_HPP__

#include <string>
#include <gtkmm.h>

namespace Felide::GTK3 {
    /**
     * @brief A Simple Text Editor control with scrollbars
     */
    class Editor : public Gtk::Bin {
    public:
        explicit Editor(const std::string &key);

        void set_text(const std::string &text);

        std::string get_text() const;

        std::string get_key() const;

        void set_stored_flag(const bool flag);

        bool get_stored_flag() const;

        void set_dirty_flag(const bool flag);

        bool get_dirty_flag() const;

    private:
        std::string m_key;
        mutable bool m_stored_flag = false;
        mutable bool m_dirty_flag = false;
        Gtk::ScrolledWindow m_scrolled;
        Gtk::TextView m_textView;
    };
}

#endif

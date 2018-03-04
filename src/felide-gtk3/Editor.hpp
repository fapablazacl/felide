
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
        Editor();

        void set_text(const std::string &text);

        std::string get_text() const;

    private:
        Gtk::ScrolledWindow m_scrolled;
        Gtk::TextView m_textView;
    };
}

#endif

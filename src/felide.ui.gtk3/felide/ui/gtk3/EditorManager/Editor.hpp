
#ifndef __FELIDE_GTK3_EDITOR_HPP__
#define __FELIDE_GTK3_EDITOR_HPP__

#include <string>
#include <gtkmm.h>

namespace felide::gtk3 {
    /**
     * @brief A Simple Text Editor control with scrollbars
     */
    class Editor : public Gtk::Bin {
    public:
        static Glib::RefPtr<Editor> create(const std::string &key);

        virtual ~Editor() {}

        virtual void set_text(const std::string &text) = 0;

        virtual std::string get_text() const = 0;

        virtual std::string get_key() const = 0;

        virtual void set_dirty_flag(const bool flag) = 0;

        virtual bool get_dirty_flag() const = 0;

    public:
        typedef sigc::signal<void> signal_editor_dirty_changed_t;
        virtual signal_editor_dirty_changed_t signal_editor_dirty_changed() = 0;
    };
}

#endif

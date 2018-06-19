
#ifndef __FELIDE_GTK3_EDITORHEADER_HPP__
#define __FELIDE_GTK3_EDITORHEADER_HPP__

#include <gtkmm.h>
#include <string>

namespace Felide::GTK3 {
    class Editor;
    class EditorHeader : public Gtk::HBox {
    public:
        static Glib::RefPtr<EditorHeader> create(Editor &editor, const std::string &title);

        virtual ~EditorHeader() {}

        virtual void update_title_label() = 0;

        virtual Gtk::Button* get_close_button() = 0;
    };
}

#endif

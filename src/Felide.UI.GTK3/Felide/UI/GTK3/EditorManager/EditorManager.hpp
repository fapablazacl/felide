
#ifndef __FELIDE_GTK3_EDITORMANAGER_HPP__
#define __FELIDE_GTK3_EDITORMANAGER_HPP__

#include <gtkmm.h>

namespace Felide::GTK3 {
    class Editor;
    class EditorManager : public Gtk::Bin {
    public:
        static Glib::RefPtr<EditorManager> create();

        virtual ~EditorManager() {}

        virtual void open_editor(const std::string &key, const std::string &title, const std::string &content) = 0;

        virtual Editor* get_current_editor() = 0;

        virtual void close_editor(Editor *editor) = 0;

    public:
        typedef sigc::signal<bool, Editor*> signal_editor_closed_t;

        virtual signal_editor_closed_t signal_editor_closed() = 0;
    };
}

#endif

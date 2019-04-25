
#ifndef __FELIDE_GTK3_EDITORMANAGER_HPP__
#define __FELIDE_GTK3_EDITORMANAGER_HPP__

#include <gtkmm.h>

namespace felide::gtk3 {
    class Editor;

    typedef sigc::signal<bool, Editor*> signal_editor_closed_t;

    class EditorManager : public Gtk::Bin {
    public:
        EditorManager();

        virtual ~EditorManager();

        void open_editor(const std::string &key, const std::string &title, const std::string &content);

        Editor& get_current_editor();

        void close_editor(Editor &editor);

    public:
        signal_editor_closed_t signal_editor_closed();

    private:
        Gtk::Notebook m_notebook;
        std::map<std::string, Editor*> m_editors;
        signal_editor_closed_t m_signal_editor_closed;
    };
}

#endif

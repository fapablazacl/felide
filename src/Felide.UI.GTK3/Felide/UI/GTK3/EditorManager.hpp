
#ifndef __FELIDE_GTK3_EDITORMANAGER_HPP__
#define __FELIDE_GTK3_EDITORMANAGER_HPP__

#include <gtkmm.h>
#include <map>

namespace Felide::GTK3 {
    class Editor;
    class EditorManager : public Gtk::Bin {
    public:
        typedef sigc::signal<void, Editor*> signal_editor_closed_t;

        signal_editor_closed_t signal_editor_closed() {
            return m_signal_editor_closed;
        }

    public:
        EditorManager();

        void open_editor(const std::string &key, const std::string &title, const std::string &content);

        Editor* get_current_editor();

        void close_editor(Editor *editor);

    private:
        Gtk::Notebook m_notebook;
        std::map<std::string, Editor*> m_editors;
        signal_editor_closed_t m_signal_editor_closed;
    };
}

#endif

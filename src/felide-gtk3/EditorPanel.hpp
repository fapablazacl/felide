
#ifndef __FELIDE_GTK3_EDITORPANEL_HPP__
#define __FELIDE_GTK3_EDITORPANEL_HPP__

#include <gtkmm.h>
#include <map>

namespace Felide::GTK3 {
    class Editor;
    class EditorPanel : public Gtk::Bin {
    public:
        typedef sigc::signal<void, Editor*> signal_editor_closed_t;

        signal_editor_closed_t signal_editor_closed() {
            return m_signal_editor_closed;
        }

    public:
        EditorPanel();

        void OpenEditor(const std::string &key, const std::string &title, const std::string &content);

        Editor* GetCurrentEditor();

        void close_editor(Editor *editor);

    private:
        Gtk::Notebook m_notebook;
        std::map<std::string, Editor*> m_editors;
        signal_editor_closed_t m_signal_editor_closed;
    };
}

#endif

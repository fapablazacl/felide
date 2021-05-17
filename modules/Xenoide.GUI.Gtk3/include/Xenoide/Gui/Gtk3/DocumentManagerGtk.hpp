
#ifndef __FELIDE_GTK3_EDITORMANAGER_HPP__
#define __FELIDE_GTK3_EDITORMANAGER_HPP__

#include <gtkmm.h>

namespace felide::gtk3 {
    class DocumentGtk;

    typedef sigc::signal<bool, DocumentGtk*> signal_editor_closed_t;

    class DocumentManagerGtk : public Gtk::Bin {
    public:
        DocumentManagerGtk();

        virtual ~DocumentManagerGtk();

    public:
        void open_editor(const std::string &key, const std::string &title, const std::string &content);

        DocumentGtk& get_current_editor();

        void close_editor(DocumentGtk &editor);

    public:
        signal_editor_closed_t signal_editor_closed();

    private:
        Gtk::Notebook m_notebook;
        std::map<std::string, DocumentGtk*> m_editors;
        signal_editor_closed_t m_signal_editor_closed;
    };
}

#endif


#ifndef __FELIDE_GTK3_EDITORPANEL_HPP__
#define __FELIDE_GTK3_EDITORPANEL_HPP__

#include <gtkmm.h>

namespace Felide::GTK3 {
    class Editor;
    class EditorPanel : public Gtk::Bin {
    public:
        EditorPanel();

        void OpenEditor(const std::string &title, const std::string &content);

        Editor* GetCurrentEditor() const;

    private:
        Gtk::Notebook m_notebook;
    };
}

#endif


#ifndef __FELIDE_GTK3_EDITORHEADER_HPP__
#define __FELIDE_GTK3_EDITORHEADER_HPP__

#include <gtkmm.h>
#include <string>

namespace felide::gtk3 {
    class Editor;
    class EditorHeader : public Gtk::HBox {
    public:
        EditorHeader(Editor &editor, const std::string &title);

        ~EditorHeader();

        void update_title_label();

        Gtk::Button* get_close_button();

    private:
        Editor &m_editor;
        std::string m_title;
        Gtk::Image m_closeImage;
        Gtk::Label m_titleLabel;
        Gtk::Button m_closeButton;
    };
}

#endif

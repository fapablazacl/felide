
#include "EditorHeader.hpp"
#include "Editor.hpp"

namespace Felide::GTK3 {
    class EditorHeaderImpl : public EditorHeader {
    public:
        explicit EditorHeaderImpl(Editor &editor, const std::string &title) 
                : m_editor(editor), m_closeImage(Gtk::Stock::CLOSE, Gtk::IconSize(Gtk::ICON_SIZE_MENU)) {
            m_title = title;

            update_title_label();
            
            m_closeButton.set_image(m_closeImage);
            m_closeButton.set_relief(Gtk::RELIEF_NONE);

            pack_start(m_titleLabel, true, 0);
            pack_end(m_closeButton);
            show_all();
        }

        virtual ~EditorHeaderImpl() {}

        virtual void update_title_label() override {
            std::string title = m_title;
            if (m_editor->get_dirty_flag()) {
                title += " *";
            }

            m_titleLabel.set_text(title);
        }

        virtual Gtk::Button* get_close_button() override {
            return &m_closeButton;
        }

    private:
        Editor &m_editor;
        std::string m_title;
        Gtk::Image m_closeImage;
        Gtk::Label m_titleLabel;
        Gtk::Button m_closeButton;
    };

    Glib::RefPtr<EditorHeader> EditorHeader::create(Editor &editor, const std::string &title) {
        return Glib::RefPtr<EditorHeader>(new EditorHeaderImpl(editor, title));
    }
}

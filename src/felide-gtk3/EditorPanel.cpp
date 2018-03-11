
#include "EditorPanel.hpp"
#include "Editor.hpp"

namespace Felide::GTK3 {
    class EditorHeader : public Gtk::HBox {
    public:
        explicit EditorHeader(EditorPanel *editorPanel, Editor *editor, const std::string &title) 
                : m_closeImage(Gtk::Stock::CLOSE, Gtk::IconSize(Gtk::ICON_SIZE_MENU)) {
            m_editorPanel = editorPanel;
            m_editor = editor;

            m_titleLabel.set_text(title);
            m_closeButton.set_image(m_closeImage);
            m_closeButton.set_relief(Gtk::RELIEF_NONE);

            m_closeButton.signal_clicked().connect(sigc::mem_fun(*this, &EditorHeader::on_button_close));

            pack_start(m_titleLabel, true, 0);
            pack_end(m_closeButton);
            show_all();
        }

    private:
        void on_button_close() {
            m_editorPanel->close_editor(m_editor);
        }

    private:
        EditorPanel *m_editorPanel;
        Editor *m_editor;
        Gtk::Image m_closeImage;
        Gtk::Label m_titleLabel;
        Gtk::Button m_closeButton;
    };

    EditorPanel::EditorPanel() {
        add(m_notebook);
        m_notebook.show();
    }

    void EditorPanel::OpenEditor(const std::string &key, const std::string &title, const std::string &content) {
        auto it = m_editors.find(key);

        Editor *editor = nullptr;

        if (it == m_editors.end()) {
            editor = new Editor(key);
            editor->set_text(content);
            editor->show();

            // TODO: Find a way to not dynamically instance the editor header
            m_notebook.append_page(*editor, *(new EditorHeader(this, editor, title)));
            m_editors[key] = editor;
        } else {
            editor = it->second;
        }

        const int pageIndex = m_notebook.page_num(*editor);
        m_notebook.set_current_page(pageIndex);
    }

    Editor* EditorPanel::GetCurrentEditor() {
        const int pageIndex = m_notebook.get_current_page();

        if (pageIndex == -1) {
            return nullptr;
        }

        return static_cast<Editor*>(m_notebook.get_nth_page(pageIndex));
    }

    void EditorPanel::close_editor(Editor *editor) {
        if (!editor) {
            return;
        }

        int pageIndex = -1;

        for (int i=0; i<m_notebook.get_n_pages(); i++) {
            if (editor == m_notebook.get_nth_page(i)) {
                pageIndex = i;
                break;
            }
        }

        if (pageIndex > -1) {
            m_notebook.remove_page(pageIndex);
        }

        m_editors.erase(editor->get_key());
    }
}

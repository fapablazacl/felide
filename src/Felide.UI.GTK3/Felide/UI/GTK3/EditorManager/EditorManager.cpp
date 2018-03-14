
#include "EditorManager.hpp"
#include "Editor.hpp"

#include <map>
#include <iostream>

namespace Felide::GTK3 {
    class EditorManagerImpl : public EditorManager {
    public:
        EditorManagerImpl() {
            add(m_notebook);
            m_notebook.show();
        }

        virtual ~EditorManagerImpl() {}

        virtual void open_editor(const std::string &key, const std::string &title, const std::string &content) override {
            auto it = m_editors.find(key);

            Glib::RefPtr<Editor> editor;

            if (it == m_editors.end()) {
                editor = Editor::create(key);
                editor->set_text(content);
                editor->set_dirty_flag(false);
                editor->show();

                auto header = EditorHeader::create(editor, title);
                editor->signal_editor_dirty_changed().connect(sigc::mem_fun(*header, &EditorHeader::update_title_label));

                // TODO: Find a way to not dynamically instance the editor header
                m_notebook.append_page(ref(editor), ref(header));
                m_editors[key] = editor;
            } else {
                editor = it->second;
            }

            const int pageIndex = m_notebook.page_num(*editor);
            m_notebook.set_current_page(pageIndex);
        }

        virtual Editor* get_current_editor() override {
            const int pageIndex = m_notebook.get_current_page();

            if (pageIndex == -1) {
                return nullptr;
            }

            return static_cast<Editor*>(m_notebook.get_nth_page(pageIndex));
        }

        virtual void close_editor(Editor *editor) override {
            if (!editor) {
                return;
            }

            // remove from UI
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

            // remove from local cache
            m_editors.erase(editor->get_key());
        }

        virtual signal_editor_closed_t signal_editor_closed() override {
            return m_signal_editor_closed;
        }

    private:
        Gtk::Notebook m_notebook;
        std::map<std::string, Editor*> m_editors;
        signal_editor_closed_t m_signal_editor_closed;
    };

    Glib::RefPtr<EditorManager> EditorManager::create() {
        return Glib::RefPtr<EditorManager>(new EditorManagerImpl());
    }
}

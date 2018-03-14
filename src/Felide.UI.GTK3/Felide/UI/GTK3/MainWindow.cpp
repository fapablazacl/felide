
#include "MainWindow.hpp"

#include <cassert>
#include <experimental/filesystem>
#include <Felide/FileUtil.hpp>
#include <Felide/UI/GTK3/Helper.hpp>
#include <Felide/UI/GTK3/EditorManager/Editor.hpp>

namespace fs = std::experimental::filesystem;

namespace Felide::GTK3 {
    class MainWindowImpl : public MainWindow {
    public:
        MainWindowImpl() {
            m_projectExplorer = ProjectExplorer::create();
            m_editorManager = EditorManager::create();

            // setup supported actions
            add_action("file_new", sigc::mem_fun(*this, &MainWindowImpl::on_action_file_new));
            add_action("file_open", sigc::mem_fun(*this, &MainWindowImpl::on_action_file_open));
            add_action("file_open_project", sigc::mem_fun(*this, &MainWindowImpl::on_action_file_open_project));
            add_action("file_save", sigc::mem_fun(*this, &MainWindowImpl::on_action_file_save));
            add_action("file_save_as", sigc::mem_fun(*this, &MainWindowImpl::on_action_file_save_as));
            add_action("file_exit", sigc::mem_fun(*this, &MainWindowImpl::on_action_file_exit));

            // setup client area
            set_border_width(10);

            m_paned.add1(ref(m_projectExplorer));
            m_projectExplorer->show();
            m_projectExplorer->signal_item_activated().connect(sigc::mem_fun(*this, &MainWindowImpl::on_item_activated));

            m_paned.add2(ref(m_editorManager));
            m_editorManager->show();

            add(m_paned);
            m_paned.show();

            maximize();
        }

        virtual ~MainWindowImpl() {}

    private:
        void on_action_file_new() {
            m_title = "Untitled";
            m_path = "";
        }

        void on_action_file_open_project() {
            Gtk::FileChooserDialog dialog("Please choose a Folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
            dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
            dialog.add_button("_Open", Gtk::RESPONSE_OK);
            dialog.set_transient_for(*this);

            int result = dialog.run();

            if (result == Gtk::RESPONSE_OK) {
                const std::string folderPath = dialog.get_filename();
                m_projectExplorer->LoadProject(folderPath);
            }
        }

        void on_action_file_save() {
            Editor* editor = m_editorManager->get_current_editor();

            if (!editor) {
                return;
            }

            // TODO: Don't always assume that a Key is a Path
            std::string path = editor->get_key();
            std::string text = editor->get_text();

            felide::FileUtil::save(path, text);

            editor->set_dirty_flag(false);
        }

        void on_action_file_close() {
            Editor *editor = m_editorManager->get_current_editor();
            m_editorManager->close_editor(editor);
        }

        void on_action_file_open() {
            auto fileFilter = Gtk::FileFilter::create();
            fileFilter->set_name("Text files");
            fileFilter->add_mime_type("text/plain");

            Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
            dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
            dialog.add_button("_Open", Gtk::RESPONSE_OK);
            dialog.set_transient_for(*this);
            dialog.add_filter(fileFilter);

            int result = dialog.run();

            if (result == Gtk::RESPONSE_OK) {            
                const std::string path = dialog.get_filename();
                const std::string name = fs::path(path).filename().string();
                const std::string content = felide::FileUtil::load(path);

                m_editorManager->open_editor(path, name, content);
            }
        }

        void on_action_file_save_as() {
            // trigger dialog
            auto fileFilter = Gtk::FileFilter::create();
            fileFilter->set_name("Text files");
            fileFilter->add_mime_type("text/plain");

            Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_SAVE);
            dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
            dialog.add_button("_Open", Gtk::RESPONSE_OK);
            dialog.set_transient_for(*this);
            dialog.add_filter(fileFilter);

            int result = dialog.run();

            if (result == Gtk::RESPONSE_OK) {
                const std::string filePath = dialog.get_filename();
            }
        }

        void on_action_file_exit() {
            hide();
        }

        void on_item_activated(std::string path) {
            if (fs::is_directory(path)) {
                return;
            }

            const std::string name = fs::path(path).filename().string();
            const std::string content = felide::FileUtil::load(path);

            m_editorManager->open_editor(path, name, content);
        }

    private:
        std::string m_title;
        std::string m_path;

        Glib::RefPtr<EditorManager> m_editorManager;
        Glib::RefPtr<ProjectExplorer> m_projectExplorer;
        Glib::RefPtr<Gio::Menu> m_mainMenu;

        // AKA Splitter
        Gtk::Paned m_paned;
    };

    MainWindow* MainWindow::create_raw() {
        return new MainWindowImpl();
    }
}

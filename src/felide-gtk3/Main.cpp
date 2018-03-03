
#include <gtkmm.h>
#include <iostream>

#include <felide/FileUtil.hpp>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class Editor : public Gtk::Bin {
public:
    Editor() {
        add(m_scrolled);

        m_scrolled.set_border_width(5);
        m_scrolled.add(m_textView);
        m_scrolled.show();
        m_textView.show();
    }

    void set_text(const std::string &text) {
        m_textView.get_buffer()->set_text(text);
    }

    std::string get_text() const {
        return "TODO!";
    }

private:
    Gtk::ScrolledWindow m_scrolled;
    Gtk::TextView m_textView;
};

class EditorPanel : public Gtk::Bin {
public:
    EditorPanel() {
        add(m_notebook);
        m_notebook.show();
    }

    void OpenEditor(const std::string &title, const std::string &content) {
        Editor *editor = new Editor();

        editor->set_text(content);
        editor->show();

        m_notebook.append_page(*editor, title);
    }

    Editor* GetCurrentEditor() const {
        return nullptr;
    }

private:
    Gtk::Notebook m_notebook;
};

/**
 * @brief ProjectExplorer thats open a "vanilla" project style (it just open a folder and shows it contents)
 */ 
class ProjectExplorer : public Gtk::Bin {
public:
    explicit ProjectExplorer() {
        add(m_scrolled);

        m_refTreeStore = Gtk::TreeStore::create(m_treeModel);
        m_treeView.set_model(m_refTreeStore);
        m_treeView.append_column("Name", m_treeModel.m_itemName);

        m_treeView.set_headers_visible(false);

        m_scrolled.set_border_width(5);
        m_scrolled.add(m_treeView);
        m_scrolled.show();
        m_treeView.show();

        show_all_children();
    }

    void LoadProject(const std::string &projectPath) {
        // internal variable cleanup
        m_projectPath = projectPath;
        m_refTreeStore->clear();

        // populate the model
        fs::path path(projectPath);
        Gtk::TreeModel::iterator treeIterator = m_refTreeStore->append();
        Gtk::TreeModel::Row row = *treeIterator;
        row[m_treeModel.m_itemName] = this->GetPathName(path);

        this->PopulateTreeNode(path, treeIterator);
    }

private:
    std::string GetPathName(const fs::path &path) {
        return path.filename();
    }

    void PopulateTreeNode(fs::path path, Gtk::TreeModel::iterator treeIterator) {
        if (fs::is_directory(path)) {
            fs::directory_iterator subPathIterator(path);
            fs::directory_iterator end;

            while (subPathIterator != end) {
                fs::path subPath = subPathIterator->path();

                Gtk::TreeModel::iterator childIterator = m_refTreeStore->append(treeIterator->children());
                Gtk::TreeModel::Row childRow = *childIterator;

                childRow[m_treeModel.m_itemName] = this->GetPathName(subPath);

                this->PopulateTreeNode(subPath, childIterator);

                subPathIterator++;
            }
        }
    }

private:
    class ProjectItemModel : public Gtk::TreeModel::ColumnRecord {
    public:
        ProjectItemModel() {
            add(m_itemName);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_itemName;
    };

    std::string m_projectPath;
    Gtk::ScrolledWindow m_scrolled;

    ProjectItemModel m_treeModel;
    Gtk::TreeView m_treeView;
    Glib::RefPtr<Gtk::TreeStore> m_refTreeStore;
};

class HelloWorldWindow : public Gtk::ApplicationWindow {
public:
    HelloWorldWindow() {
        // setup supported actions
        add_action("file_new", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_new));
        add_action("file_open", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_open));
        add_action("file_open_project", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_open_project));
        add_action("file_save", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_save));
        add_action("file_save_as", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_save_as));
        add_action("file_exit", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_exit));

        // setup client area
        set_border_width(10);

        m_paned.add1(m_projectExplorer);
        m_projectExplorer.show();

        m_paned.add2(m_editorPanel);
        m_editorPanel.show();

        add(m_paned);
        m_paned.show();
    }

    virtual ~HelloWorldWindow() {}

private:
    void on_action_file_new() {
        m_title = "Untitled";
        m_path = "";
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
            const std::string filePath = dialog.get_filename();
            const std::string fileContent = felide::FileUtil::load(filePath);

            // set_title(filePath);
            m_editorPanel.OpenEditor(filePath, fileContent);
        }
    }

    void on_action_file_open_project() {
        Gtk::FileChooserDialog dialog("Please choose a Folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);
        dialog.set_transient_for(*this);

        int result = dialog.run();

        if (result == Gtk::RESPONSE_OK) {
            const std::string folderPath = dialog.get_filename();

            m_projectExplorer.LoadProject(folderPath);
        }
    }

    void on_action_file_save() {
        
    }

    void on_action_file_save_as() {
        
    }

    void on_action_file_exit() {
        hide();
    }

private:
    std::string m_title;
    std::string m_path;

    EditorPanel m_editorPanel;
    ProjectExplorer m_projectExplorer;

    Glib::RefPtr<Gio::Menu> m_mainMenu;

    Gtk::Paned m_paned;   // AKA Splitter
};

class HelloWorldApplication : public Gtk::Application {
public:
    HelloWorldApplication(int argc, char* argv[], const char *name) 
        : Gtk::Application(argc, argv, name) {}

    static Glib::RefPtr<HelloWorldApplication> create(int argc, char* argv[], const char *name) {
        return Glib::RefPtr<HelloWorldApplication>(new HelloWorldApplication(argc, argv, name) );
    }

public:
    virtual void on_startup() override {
        Gtk::Application::on_startup();

        // application menu
        Glib::RefPtr<Gio::Menu> fileMenu = Gio::Menu::create();
        fileMenu->append("_New", "win.file_new");
        fileMenu->append("_Open File", "win.file_open");
        fileMenu->append("_Open Project", "win.file_open_project");
        fileMenu->append("_Save", "win.file_save");
        fileMenu->append("Save _As", "win.file_save_as");
        fileMenu->append("_Exit", "win.file_exit");

        Glib::RefPtr<Gio::Menu> mainMenu = Gio::Menu::create();
        mainMenu->append_submenu("_File", fileMenu);

        set_menubar(mainMenu);
    }
};

int main(int argc, char* argv[]) {
    auto app = HelloWorldApplication::create(argc, argv, "org.devwarecl.felide");

    HelloWorldWindow window;
    return app->run(window);
}


#include <gtkmm.h>
#include <iostream>

#include <felide/FileUtil.hpp>

class HelloWorldWindow : public Gtk::ApplicationWindow {
public:
    HelloWorldWindow() {
        // setup supported actions
        add_action("file_new", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_new));
        add_action("file_open", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_open));
        add_action("file_save", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_save));
        add_action("file_save_as", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_save_as));
        add_action("file_exit", sigc::mem_fun(*this, &HelloWorldWindow::on_action_file_exit));

        // setup client area
        set_border_width(10);
        add(m_scrolledWindow);

        m_scrolledWindow.set_border_width(5);
        m_scrolledWindow.add(m_textView);
        m_scrolledWindow.show();
        m_textView.show();
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

            set_title(filePath);
            m_textView.get_buffer()->set_text(fileContent);
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

    Gtk::ScrolledWindow m_scrolledWindow;
    Gtk::TextView m_textView;
    Glib::RefPtr<Gio::Menu> m_mainMenu;
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
        fileMenu->append("_Open", "win.file_open");
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

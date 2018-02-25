
#include <gtkmm.h>
#include <iostream>

class HelloWorldWindow : public Gtk::ApplicationWindow {
public:
    HelloWorldWindow() : m_button("Hello, World") {
        // setup supported actions
        add_action("notify", sigc::mem_fun(*this, &HelloWorldWindow::on_action_notify));
        add_action("exit", sigc::mem_fun(*this, &HelloWorldWindow::on_action_exit));
        
        // setup client area
        set_border_width(10);
        m_button.signal_clicked().connect(sigc::mem_fun(*this, &HelloWorldWindow::on_button_clicked));
        add(m_button);

        m_button.show();
    }

    virtual ~HelloWorldWindow() {}

private:
    void on_button_clicked() {
        std::cout << "Hello, World!" << std::endl;
    }

    void on_action_exit() {
        hide();
    }

    void on_action_notify() {
        std::cout << "Notify!" << std::endl;

        auto note = Gio::Notification::create("Felide Message!");
        note->set_body("Notification from" + Glib::get_application_name());
        // note->add_button("Print", "app.print", Glib::ustring("Hello World"));
        note->add_button("Greet App", "app.greet");
        get_application()->send_notification("note", note);
    }

private:
    Gtk::Button m_button;
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

        add_action("greet", sigc::mem_fun(*this, &HelloWorldApplication::on_action_greet));

        // application menu
        Glib::RefPtr<Gio::Menu> fileMenu = Gio::Menu::create();
        fileMenu->append("_Notify", "win.notify");
        fileMenu->append("_Exit", "win.exit");

        Glib::RefPtr<Gio::Menu> mainMenu = Gio::Menu::create();
        mainMenu->append_submenu("_File", fileMenu);

        set_menubar(mainMenu);
    }

private:
    void on_action_greet() {
        std::cout << "Application::on_action_greet" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    Glib::RefPtr<HelloWorldApplication> app 
        = HelloWorldApplication::create(argc, argv, "org.devwarecl.felide");

    HelloWorldWindow window;

    return app->run(window);
}

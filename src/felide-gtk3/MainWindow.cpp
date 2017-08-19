
#include "MainWindow.hpp"
#include <iostream>

namespace felide {

    MainWindow::MainWindow() : 
    Gtk::ApplicationWindow(),
    m_Box(Gtk::ORIENTATION_VERTICAL) {
        set_title("Main menu example");
        set_default_size(300, 100);

        // ExampleApplication displays the menubar. Other stuff, such as a toolbar,
        // is put into the box.
        add(m_Box);

        // Create actions for menus and toolbars.
        // We can use add_action() because Gtk::ApplicationWindow derives from Gio::ActionMap.
        // This Action Map uses a "win." prefix for the actions.
        // Therefore, for instance, "win.copy", is used in ExampleApplication::on_startup()
        // to layout the menu.

        //Edit menu:
        add_action("copy", sigc::mem_fun(*this, &MainWindow::on_menu_others));
        add_action("paste", sigc::mem_fun(*this, &MainWindow::on_menu_others));
        add_action("something", sigc::mem_fun(*this, &MainWindow::on_menu_others));

        //Choices menus, to demonstrate Radio items,
        //using our convenience methods for string and int radio values:
        m_refChoice = add_action_radio_string("choice",
        sigc::mem_fun(*this, &MainWindow::on_menu_choices), "a");

        m_refChoiceOther = add_action_radio_integer("choiceother",
        sigc::mem_fun(*this, &MainWindow::on_menu_choices_other), 1);

        m_refToggle = add_action_bool("sometoggle",
        sigc::mem_fun(*this, &MainWindow::on_menu_toggle), false);

        //Help menu:
        add_action("about", sigc::mem_fun(*this, &MainWindow::on_menu_others));

        //Create the toolbar and add it to a container widget:

        m_refBuilder = Gtk::Builder::create();

        Glib::ustring ui_info =
        "<!-- Generated with glade 3.18.3 -->"
        "<interface>"
        "  <requires lib='gtk+' version='3.4'/>"
        "  <object class='GtkToolbar' id='toolbar'>"
        "    <property name='visible'>True</property>"
        "    <property name='can_focus'>False</property>"
        "    <child>"
        "      <object class='GtkToolButton' id='toolbutton_new'>"
        "        <property name='visible'>True</property>"
        "        <property name='can_focus'>False</property>"
        "        <property name='tooltip_text' translatable='yes'>New Standard</property>"
        "        <property name='action_name'>app.newstandard</property>"
        "        <property name='icon_name'>document-new</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>True</property>"
        "      </packing>"
        "    </child>"
        "    <child>"
        "      <object class='GtkToolButton' id='toolbutton_quit'>"
        "        <property name='visible'>True</property>"
        "        <property name='can_focus'>False</property>"
        "        <property name='tooltip_text' translatable='yes'>Quit</property>"
        "        <property name='action_name'>app.quit</property>"
        "        <property name='icon_name'>application-exit</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>True</property>"
        "      </packing>"
        "    </child>"
        "  </object>"
        "</interface>";

        try {
            m_refBuilder->add_from_string(ui_info);
        } catch (const Glib::Error& ex) {
            std::cerr << "Building toolbar failed: " <<  ex.what();
        }

        Gtk::Toolbar* toolbar = nullptr;
        m_refBuilder->get_widget("toolbar", toolbar);

        if (!toolbar) {
            g_warning("GtkToolbar not found");
        } else {
            m_Box.pack_start(*toolbar, Gtk::PACK_SHRINK);
        }
    }
    
    MainWindow::~MainWindow() {}
    
    void MainWindow::on_menu_others() {
        std::cout << "A menu item was selected." << std::endl;
    }
    
    void MainWindow::on_menu_choices(const Glib::ustring& parameter) {
        //The radio action's state does not change automatically:
        m_refChoice->change_state(parameter);

        Glib::ustring message;
        if (parameter == "a") {
        message = "Choice a was selected.";
        } else {
        message = "Choice b was selected.";
        }

        std::cout << message << std::endl;
    }
    
    void MainWindow::on_menu_choices_other(int parameter) {
        //The radio action's state does not change automatically:
        m_refChoiceOther->change_state(parameter);

        Glib::ustring message;
        if (parameter == 1) {
            message = "Choice 1 was selected.";
        } else {
            message = "Choice 2 was selected.";
        }

        std::cout << message << std::endl;
    }
    
    void MainWindow::on_menu_toggle() {
        bool active = false;
        m_refToggle->get_state(active);

        //The toggle action's state does not change automatically:
        active = !active;
        m_refToggle->change_state(active);

        Glib::ustring message;
        if (active) {
            message = "Toggle is active.";
        } else {
            message = "Toggle is not active.";
        }

        std::cout << message << std::endl;
    }

    /*
    MainWindow::MainWindow() {
        m_sourceView.get_buffer()->set_text("This is a test!");
        m_sourceView.show();

        m_notebook.append_page(m_sourceView);
        this->set_border_width(10);
        this->set_default_size(640, 400);
        
        // m_button.signal_clicked().connect(
        //     sigc::mem_fun(
        //         *this, 
        //         &MainWindow::OnButtonClicked
        //     )
        // );
        
        this->add(m_notebook);

        m_notebook.show();

        this->initMenuBar();
    }

    void MainWindow::initMenuBar(Gtk::Application *app) {
        // create three simple actions
        m_refActionGroup = Gio::SimpleActionGroup::create();

        m_refActionGroup->add_action("new", sigc::mem_fun(*this, &MainWindow::on_action_file_new));
        m_refActionGroup->add_action("open", sigc::mem_fun(*this, &MainWindow::on_action_file_open));
        m_refActionGroup->add_action("quit", sigc::mem_fun(*this, &MainWindow::on_action_file_quit));

        insert_action_group("example", m_refActionGroup);

        // create the builder
        m_refBuilder = Gtk::Builder::create();

        app->set_accel_for_action("example.new", "<Primary>n");
        app->set_accel_for_action("example.quit", "<Primary>q");
        app->set_accel_for_action("example.copy", "<Primary>c");
        app->set_accel_for_action("example.paste", "<Primary>v");
    }

    void MainWindow::setupSourceView() {
        m_sourceView.set_tab_width(4);
    }

    MainWindow::~MainWindow() {}

    void MainWindow::onButtonClicked() {
        std::cout << "Hello, World!" << std::endl;
    }

    void MainWindow::on_action_file_new() {
        std::cout << "MainWindow::on_action_file_new()" << std::endl;
    }

    void MainWindow::on_action_file_open() {
        std::cout << "MainWindow::on_action_file_open()" << std::endl;
    }

    void MainWindow::on_action_file_quit() {
        std::cout << "MainWindow::on_action_file_quit()" << std::endl;
    }
    */
}

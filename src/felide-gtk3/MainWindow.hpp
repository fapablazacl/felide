
#ifndef __FELIDE_GTK3_MAINWINDOW_HPP__
#define __FELIDE_GTK3_MAINWINDOW_HPP__

#include <gtkmm/notebook.h>
#include <gtkmm/window.h>
#include <giomm/simpleactiongroup.h>
#include <gtkmm/applicationwindow.h> 
#include <gtkmm.h> 
#include <gtksourceviewmm.h>

namespace felide {
    class MainWindow : public Gtk::ApplicationWindow {
    public:
        MainWindow();
        virtual ~MainWindow();
    
    protected:
        //Signal handlers:
        void on_menu_others();

        void on_menu_choices(const Glib::ustring& parameter);
        void on_menu_choices_other(int parameter);
        void on_menu_toggle();

        //Child widgets:
        Gtk::Box m_Box;

        Glib::RefPtr<Gtk::Builder> m_refBuilder;

        //Two sets of choices:
        Glib::RefPtr<Gio::SimpleAction> m_refChoice;
        Glib::RefPtr<Gio::SimpleAction> m_refChoiceOther;

        Glib::RefPtr<Gio::SimpleAction> m_refToggle;
    };
    
    /*
    class MainWindow : public Gtk::Window {
    public:
        MainWindow();

        virtual ~MainWindow();

    public:
        void onButtonClicked();

        void setupSourceView();

        void initMenuBar(Gtk::Application *app);

    private:
        void on_action_file_new();
        void on_action_file_open();
        void on_action_file_quit();
        
    private:
        Gtk::Notebook m_notebook;
        Gsv::View m_sourceView;

        Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;
        Glib::RefPtr<Gtk::Builder> m_refBuilder
    };
    */
}

#endif

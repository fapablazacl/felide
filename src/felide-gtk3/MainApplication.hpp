
#ifndef GTKMM_EXAMPLEAPPLICATION_H
#define GTKMM_EXAMPLEAPPLICATION_H

#include <gtkmm.h>

namespace felide {
    class MainApplication : public Gtk::Application {
    protected:
        MainApplication();

    public:
        static Glib::RefPtr<MainApplication> create();

    protected:
        void on_startup() override;
        void on_activate() override;

    private:
        void create_window();

        void on_window_hide(Gtk::Window* window);
        void on_menu_file_new_generic();
        void on_menu_file_quit();
        void on_menu_help_about();

        Glib::RefPtr<Gtk::Builder> m_refBuilder;
    };
}

#endif

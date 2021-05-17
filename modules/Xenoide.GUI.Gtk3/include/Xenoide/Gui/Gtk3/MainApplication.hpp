
#ifndef __FELIDE_GTK3_MAINAPPLICATION_HPP__
#define __FELIDE_GTK3_MAINAPPLICATION_HPP__

#include <gtkmm.h>

namespace felide::gtk3 {
    class MainApplication : public Gtk::Application {
    public:
        MainApplication(int argc, char* argv[], const char *name);

        static Glib::RefPtr<MainApplication> create(int argc, char* argv[], const char *name);

    public:
        virtual void on_startup() override;
    };
}

#endif

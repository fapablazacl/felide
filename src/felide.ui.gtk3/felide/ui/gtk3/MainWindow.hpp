
#ifndef __FELIDE_GTK3_MAINWINDOW_HPP__
#define __FELIDE_GTK3_MAINWINDOW_HPP__

#include <gtkmm.h>
#include <string>

#include <felide/UI/GTK3/EditorManager/EditorManager.hpp>
#include "ProjectExplorer.hpp"

namespace felide::gtk3 {
    class MainWindow : public Gtk::ApplicationWindow {
    public:
        static MainWindow* create_raw();
        virtual ~MainWindow() {}
    };
}

#endif

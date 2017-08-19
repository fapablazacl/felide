
#ifndef __FELIDE_GTK3_MAINWINDOW_HPP__
#define __FELIDE_GTK3_MAINWINDOW_HPP__

#include <gtkmm/button.h>
#include <gtkmm/window.h>

namespace felide {
    class MainWindow : public Gtk::Window {
    public:
        MainWindow();

        virtual ~MainWindow();

    private:
        void OnButtonClicked();

    private:
        Gtk::Button m_button;
    };
}

#endif

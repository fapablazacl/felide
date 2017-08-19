
#ifndef __FELIDE_GTK3_MAINWINDOW_HPP__
#define __FELIDE_GTK3_MAINWINDOW_HPP__

#include <gtkmm/notebook.h>
#include <gtkmm/window.h>
#include <gtksourceviewmm.h>

namespace felide {
    class MainWindow : public Gtk::Window {
    public:
        MainWindow();

        virtual ~MainWindow();

    private:
        void OnButtonClicked();

    private:
        Gtk::Notebook m_notebook;
        Gsv::View m_sourceView;
    };
}

#endif

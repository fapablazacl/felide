
#ifndef __FELIDE_GTK3_MAINWINDOW_HPP__
#define __FELIDE_GTK3_MAINWINDOW_HPP__

#include <gtkmm.h>
#include <string>

#include <felide/ui/gtk3/EditorManager/EditorManager.hpp>
#include "FolderBrowserGtk.hpp"

namespace felide::gtk3 {
    class MainWindow : public Gtk::ApplicationWindow {
    public:
        MainWindow();

        virtual ~MainWindow();

    private:
        void on_action_file_new();

        void on_action_file_open_project();

        void on_action_file_save();

        void on_action_file_close();

        void on_action_file_open();

        void on_action_file_save_as();

        void on_action_file_exit();

        void on_item_activated(std::string path);

    private:
        std::string m_title;
        std::string m_path;

        EditorManager m_editorManager;
        ProjectExplorer m_projectExplorer;
        Glib::RefPtr<Gio::Menu> m_mainMenu;

        // AKA Splitter
        Gtk::Paned m_paned;
    };
}

#endif

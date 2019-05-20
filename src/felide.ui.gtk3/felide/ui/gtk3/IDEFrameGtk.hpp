
#ifndef __FELIDE_GTK3_MAINWINDOW_HPP__
#define __FELIDE_GTK3_MAINWINDOW_HPP__

#include <gtkmm.h>
#include <string>

#include <felide/ui/ide-frame/IDEFrame.hpp>
#include <felide/ui/gtk3/DocumentManagerGtk.hpp>
#include "FolderBrowserGtk.hpp"
#include "DialogManagerGtk.hpp"

namespace felide::gtk3 {
    class IDEFrameGtk : public Gtk::ApplicationWindow, public IDEFrame {
    public:
        IDEFrameGtk(IDEFramePresenter *presenter);

        virtual ~IDEFrameGtk();

        virtual DocumentManager* getDocumentManager() override;

        virtual DialogManager* getDialogManager() override;

        virtual FolderBrowser* getFolderBrowser() override;

        virtual void close() override;

        virtual void show() override;

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

        DialogManagerGtk dialogManager;
        DocumentManagerGtk m_editorManager;
        FolderBrowserGtk m_projectExplorer;
        Glib::RefPtr<Gio::Menu> m_mainMenu;

        // AKA Splitter
        Gtk::Paned m_paned;
    };
}

#endif

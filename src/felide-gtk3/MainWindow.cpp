
#include "MainWindow.hpp"

#include <cassert>
#include <iostream>
#include <felide/FileUtil.hpp>
#include "Editor.hpp"

namespace Felide::GTK3 {
    MainWindow::MainWindow() {
        // setup supported actions
        add_action("file_new", sigc::mem_fun(*this, &MainWindow::on_action_file_new));
        add_action("file_open", sigc::mem_fun(*this, &MainWindow::on_action_file_open));
        add_action("file_open_project", sigc::mem_fun(*this, &MainWindow::on_action_file_open_project));
        add_action("file_save", sigc::mem_fun(*this, &MainWindow::on_action_file_save));
        add_action("file_save_as", sigc::mem_fun(*this, &MainWindow::on_action_file_save_as));
        add_action("file_exit", sigc::mem_fun(*this, &MainWindow::on_action_file_exit));

        // setup client area
        set_border_width(10);

        m_paned.add1(m_projectExplorer);
        m_projectExplorer.show();

        m_projectExplorer.signal_item_activated().connect(sigc::mem_fun(*this, &MainWindow::on_item_activated));

        m_paned.add2(m_editorPanel);
        m_editorPanel.show();

        add(m_paned);
        m_paned.show();

        maximize();
    }

    MainWindow::~MainWindow() {}

    void MainWindow::on_action_file_new() {
        m_title = "Untitled";
        m_path = "";
    }

    void MainWindow::on_action_file_open_project() {
        Gtk::FileChooserDialog dialog("Please choose a Folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);
        dialog.set_transient_for(*this);

        int result = dialog.run();

        if (result == Gtk::RESPONSE_OK) {
            const std::string folderPath = dialog.get_filename();
            m_projectExplorer.LoadProject(folderPath);
        }
    }

    void MainWindow::on_action_file_save() {
        // TODO: Add implementation
    }

    void MainWindow::on_action_file_open() {
        auto fileFilter = Gtk::FileFilter::create();
        fileFilter->set_name("Text files");
        fileFilter->add_mime_type("text/plain");

        Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);
        dialog.set_transient_for(*this);
        dialog.add_filter(fileFilter);

        int result = dialog.run();

        if (result == Gtk::RESPONSE_OK) {            
            const std::string path = dialog.get_filename();
            const std::string name = fs::path(path).filename().string();
            const std::string content = felide::FileUtil::load(path);

            m_editorPanel.OpenEditor(path, name, content);
        }
    }

    void MainWindow::on_action_file_save_as() {
        // trigger dialog
        auto fileFilter = Gtk::FileFilter::create();
        fileFilter->set_name("Text files");
        fileFilter->add_mime_type("text/plain");

        Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);
        dialog.set_transient_for(*this);
        dialog.add_filter(fileFilter);

        int result = dialog.run();

        if (result == Gtk::RESPONSE_OK) {
            const std::string filePath = dialog.get_filename();
        }
    }

    void MainWindow::on_action_file_exit() {
        hide();
    }

    void MainWindow::on_item_activated(std::string path) {
        if (fs::is_directory(path)) {
            return;
        }

        const std::string name = fs::path(path).filename().string();
        const std::string content = felide::FileUtil::load(path);

        m_editorPanel.OpenEditor(path, name, content);
    }
}

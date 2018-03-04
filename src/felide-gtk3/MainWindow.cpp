
#include "MainWindow.hpp"

#include <felide/FileUtil.hpp>

namespace Felide::GTK3 {
    MainWindow::MainWindow() : m_projectExplorer(&m_editorPanel) {
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

        m_paned.add2(m_editorPanel);
        m_editorPanel.show();

        add(m_paned);
        m_paned.show();
    }

    MainWindow::~MainWindow() {}

    void MainWindow::on_action_file_new() {
        m_title = "Untitled";
        m_path = "";
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
            const std::string filePath = dialog.get_filename();
            const std::string fileContent = felide::FileUtil::load(filePath);

            // set_title(filePath);
            m_editorPanel.OpenEditor(filePath, fileContent);
        }
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
        
    }

    void MainWindow::on_action_file_save_as() {
        
    }

    void MainWindow::on_action_file_exit() {
        hide();
    }
}


#include "ProjectExplorer.hpp"

#include <iostream>
#include <experimental/filesystem>
#include <felide/FileUtil.hpp>
#include "EditorPanel.hpp"

namespace fs = std::experimental::filesystem;

namespace Felide::GTK3 {
    ProjectExplorer::ProjectExplorer() {
        // setup UI
        add(m_scrolled);

        m_refTreeStore = Gtk::TreeStore::create(m_treeModel);
        m_treeView.set_model(m_refTreeStore);
        m_treeView.append_column("Name", m_treeModel.m_itemName);
        m_treeView.set_headers_visible(false);

        m_scrolled.set_border_width(5);
        m_scrolled.add(m_treeView);
        m_scrolled.show();
        m_treeView.show();

        show_all_children();

        // connect event handlers
        // m_treeView.get_selection()->signal_changed().connect(sigc::mem_fun(*this, &ProjectExplorer::OnItemSelected));
        m_treeView.signal_row_activated().connect(sigc::mem_fun(*this, &ProjectExplorer::OnItemActivated));
    }

    void ProjectExplorer::LoadProject(const std::string &projectPath) {
        // internal variable cleanup
        m_projectPath = projectPath;
        m_refTreeStore->clear();

        // populate the model
        fs::path path(projectPath);
        Gtk::TreeModel::iterator treeIterator = m_refTreeStore->append();
        Gtk::TreeModel::Row row = *treeIterator;
        row[m_treeModel.m_itemName] = this->GetPathName(path);
        row[m_treeModel.m_itemPath] = path.string();

        this->PopulateTreeNode(path, treeIterator);

        Gtk::TreeModel::Path treePath;
        treePath.push_back(0);

        m_treeView.expand_row(treePath, false);
    }

    void ProjectExplorer::OnItemActivated(const Gtk::TreeModel::Path& treePath, Gtk::TreeViewColumn* column) {
        Gtk::TreeModel::iterator iterator = m_treeView.get_model()->get_iter(treePath);

        if (!iterator) {
            return;
        }
        
        Gtk::TreeModel::Row row = *iterator;
        std::string name = row[m_treeModel.m_itemName];
        std::string path = row[m_treeModel.m_itemPath];

        m_signal_item_activated(path);
    }

    void ProjectExplorer::OnItemSelected() {
        /*
        Gtk::TreeModel::iterator iterator = m_treeView.get_selection()->get_selected();

        if (iterator) {
            Gtk::TreeModel::Row row = *iterator;
            Glib::ustring name = row[m_treeModel.m_itemName];
            Glib::ustring path = row[m_treeModel.m_itemPath];

            const std::string content = felide::FileUtil::load(path);
            m_editorPanel->OpenEditor(name, content);
        }
        */
    }

    std::string ProjectExplorer::GetPathName(const fs::path &path) {
        return path.filename();
    }

    void ProjectExplorer::PopulateTreeNode(fs::path path, Gtk::TreeModel::iterator treeIterator) {
        if (fs::is_directory(path)) {
            fs::directory_iterator subPathIterator(path);
            fs::directory_iterator end;

            while (subPathIterator != end) {
                fs::path subPath = subPathIterator->path();

                Gtk::TreeModel::iterator childIterator = m_refTreeStore->append(treeIterator->children());
                Gtk::TreeModel::Row childRow = *childIterator;

                childRow[m_treeModel.m_itemName] = this->GetPathName(subPath);
                childRow[m_treeModel.m_itemPath] = subPath.string();

                this->PopulateTreeNode(subPath, childIterator);

                subPathIterator++;
            }
        }
    }

    ProjectExplorer::ProjectItemModel::ProjectItemModel() {
        add(m_itemName);
        add(m_itemPath);
    }
}

#include "ProjectExplorer.hpp"

#include <felide/FileUtil.hpp>
#include "EditorPanel.hpp"

namespace Felide::GTK3 {
    ProjectExplorer::ProjectExplorer(EditorPanel *editorPanel) {
        m_editorPanel = editorPanel;

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

        // connect 
        m_treeView.get_selection()->signal_changed().connect(sigc::mem_fun(*this, &ProjectExplorer::OnItemSelected));
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
    }

    void ProjectExplorer::OnItemSelected() {
        Gtk::TreeModel::iterator iterator = m_treeView.get_selection()->get_selected();

        if (iterator) {
            Gtk::TreeModel::Row row = *iterator;
            Glib::ustring name = row[m_treeModel.m_itemName];
            Glib::ustring path = row[m_treeModel.m_itemPath];

            const std::string content = felide::FileUtil::load(path);
            m_editorPanel->OpenEditor(name, content);
        }
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

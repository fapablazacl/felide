
#ifndef __FELIDE_GTK3_PROJECTEXPLORER_HPP__
#define __FELIDE_GTK3_PROJECTEXPLORER_HPP__

#include <string>
#include <gtkmm.h>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace Felide::GTK3 {
    class EditorPanel;
    /**
     * @brief ProjectExplorer thats open a "vanilla" project style (it just open a folder and shows it contents)
     */ 
    class ProjectExplorer : public Gtk::Bin {
    public:
        explicit ProjectExplorer(EditorPanel *editorPanel);

        void LoadProject(const std::string &projectPath);

    private:
        void OnItemSelected();

        std::string GetPathName(const fs::path &path);

        void PopulateTreeNode(fs::path path, Gtk::TreeModel::iterator treeIterator);

    private:
        class ProjectItemModel : public Gtk::TreeModel::ColumnRecord {
        public:
            ProjectItemModel();

            Gtk::TreeModelColumn<Glib::ustring> m_itemName;
            Gtk::TreeModelColumn<Glib::ustring> m_itemPath;
        };

    private:
        std::string m_projectPath;
        Gtk::ScrolledWindow m_scrolled;

        ProjectItemModel m_treeModel;
        Gtk::TreeView m_treeView;
        Glib::RefPtr<Gtk::TreeStore> m_refTreeStore;

        EditorPanel *m_editorPanel;
    };
}

#endif

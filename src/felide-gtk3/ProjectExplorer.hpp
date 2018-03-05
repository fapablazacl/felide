
#ifndef __FELIDE_GTK3_PROJECTEXPLORER_HPP__
#define __FELIDE_GTK3_PROJECTEXPLORER_HPP__

#include <string>
#include <gtkmm.h>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace Felide::GTK3 {
    /**
     * @brief ProjectExplorer thats open a "vanilla" project style (it just open a folder and shows it contents)
     */ 
    class ProjectExplorer : public Gtk::Bin {
    public:
        typedef sigc::signal<void, std::string> signal_item_activated_t;

        signal_item_activated_t signal_item_activated() {
            return m_signal_item_activated;
        }

    public:
        explicit ProjectExplorer();

        void LoadProject(const std::string &projectPath);

    private:
        void OnItemSelected();

        void OnItemActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

        std::string GetPathName(const fs::path &path);

        void PopulateTreeNode(fs::path path, Gtk::TreeModel::iterator treeIterator);

    private:
        class ProjectItemModel : public Gtk::TreeModel::ColumnRecord {
        public:
            ProjectItemModel();

            Gtk::TreeModelColumn<std::string> m_itemName;
            Gtk::TreeModelColumn<std::string> m_itemPath;
        };

    private:
        signal_item_activated_t m_signal_item_activated;

        std::string m_projectPath;
        Gtk::ScrolledWindow m_scrolled;

        ProjectItemModel m_treeModel;
        Gtk::TreeView m_treeView;
        Glib::RefPtr<Gtk::TreeStore> m_refTreeStore;
    };
}

#endif

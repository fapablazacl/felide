
#include "ProjectExplorer.hpp"

#include <iostream>
#include <experimental/filesystem>
#include <Felide/FileUtil.hpp>

namespace fs = std::experimental::filesystem;

namespace Felide::GTK3 {
    class ProjectItemModel : public Gtk::TreeModel::ColumnRecord {
    public:
        ProjectItemModel() {
            add(m_itemName);
            add(m_itemPath);
        }

        Gtk::TreeModelColumn<std::string> m_itemName;
        Gtk::TreeModelColumn<std::string> m_itemPath;
    };

    class ProjectExplorerImpl : public ProjectExplorer {
    public:
        ProjectExplorerImpl() {
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
            m_treeView.signal_row_activated().connect(sigc::mem_fun(*this, &ProjectExplorerImpl::OnItemActivated));
        }

        virtual ~ProjectExplorerImpl() {}

        virtual void LoadProject(const std::string &projectPath) override {
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

        virtual signal_item_activated_t signal_item_activated() override {
            return m_signal_item_activated;
        }

    private:
        void OnItemActivated(const Gtk::TreeModel::Path& treePath, Gtk::TreeViewColumn* column) {
            Gtk::TreeModel::iterator iterator = m_treeView.get_model()->get_iter(treePath);

            if (!iterator) {
                return;
            }
            
            Gtk::TreeModel::Row row = *iterator;
            std::string name = row[m_treeModel.m_itemName];
            std::string path = row[m_treeModel.m_itemPath];

            m_signal_item_activated(path);
        }

        void OnItemSelected() {
            /*
            Gtk::TreeModel::iterator iterator = m_treeView.get_selection()->get_selected();

            if (iterator) {
                Gtk::TreeModel::Row row = *iterator;
                Glib::ustring name = row[m_treeModel.m_itemName];
                Glib::ustring path = row[m_treeModel.m_itemPath];

                const std::string content = felide::FileUtil::load(path);
                m_editorManager->OpenEditor(name, content);
            }
            */
        }

        std::string GetPathName(const fs::path &path) {
            return path.filename();
        }

        void PopulateTreeNode(fs::path path, Gtk::TreeModel::iterator treeIterator) {
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

    private:
        signal_item_activated_t m_signal_item_activated;

        std::string m_projectPath;
        Gtk::ScrolledWindow m_scrolled;

        ProjectItemModel m_treeModel;
        Gtk::TreeView m_treeView;
        Glib::RefPtr<Gtk::TreeStore> m_refTreeStore;
    };

    Glib::RefPtr<ProjectExplorer> ProjectExplorer::create() {
        return Glib::RefPtr<ProjectExplorer>(new ProjectExplorerImpl());
    }
}

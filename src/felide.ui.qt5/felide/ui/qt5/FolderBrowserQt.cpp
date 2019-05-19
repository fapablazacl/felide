
#include "FolderBrowserQt.hpp"

#include <QVBoxLayout>
#include <QBoxLayout>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QMimeData>
#include <iostream>
#include <felide/ui/folder-browser/FolderBrowserPresenter.hpp>

#include "DialogManagerQt.hpp"
#include "UtilitiesQt.hpp"

#include <boost/filesystem.hpp>

namespace felide {
    namespace fs = boost::filesystem;

    // TODO: Refactor file handling logic into another layer
    class FolderBrowserQtTreeModel : public QFileSystemModel {
    public:
        FolderBrowserQtTreeModel(QWidget *parent, FolderBrowserPresenter *presenter) : QFileSystemModel(parent) {
            this->presenter = presenter;
        }

        virtual Qt::ItemFlags flags(const QModelIndex &index) const override {
            if (!index.isValid()) {
                return 0;
            }

            const auto path = fs::path(this->filePath(index).toStdString());

            Qt::ItemFlags flags = Qt::ItemFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled);

            if (fs::is_directory(path)) {
                flags |= Qt::ItemIsDropEnabled;
            }

            return flags;
        }

        virtual Qt::DropActions supportedDropActions() const override {
            return Qt::DropActions(Qt::CopyAction | Qt::MoveAction);
        }

        virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override {
            if (action == Qt::MoveAction) {
                const QString absFilePath = this->fileInfo(parent).absoluteFilePath();

                presenter->onMoveSelectedPath(absFilePath.toStdString());
            }

            return QFileSystemModel::dropMimeData(data, action, row, column, parent);
        }

    private:
        FolderBrowserPresenter *presenter = nullptr;
    };
}

namespace felide {
    void FolderBrowserQt::displayFolder(const std::string &folder) {
        this->setProjectFolder(folder.c_str());
    }

    boost::optional<std::string> FolderBrowserQt::getSelectedPath() const {
        const QModelIndex index = m_treeView->currentIndex();
        const QString path = m_fileSystemModel->fileInfo(index).absoluteFilePath();

        return path.toStdString();
    }
}

namespace felide {
    FolderBrowserQt::FolderBrowserQt(QWidget *parent, FolderBrowserPresenter *presenter, DialogManagerQt *dialogManager) : QWidget(parent), FolderBrowser(presenter) {
        m_treeView = new QTreeView(this);

        this->setLayout(new QVBoxLayout(this));
        this->layout()->addWidget(m_treeView);

        // instance file system model
        m_fileSystemModel = new FolderBrowserQtTreeModel(this, presenter);
        m_fileSystemModel->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);

        // enable treeview support
        m_treeView->setDragDropMode(QAbstractItemView::InternalMove);
        // m_treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        m_treeView->setDragEnabled(true);
        m_treeView->setAcceptDrops(true);
        // m_treeView->setDropIndicatorShown(true);

        // bind view and model together
        m_treeView->setModel(m_fileSystemModel);
        m_treeView->setVisible(false);
        m_treeView->setHeaderHidden(true);
        m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);

        for (int i=1; i<m_fileSystemModel->columnCount(); ++i) {
            m_treeView->hideColumn(i);
        }

        // connect signal handlers
        connect(m_treeView, &QTreeView::doubleClicked, [this](const QModelIndex index) {
            m_presenter->onOpenSelectedFile();
        });

        connect(m_treeView, &QTreeView::customContextMenuRequested, [this](const QPoint &pos) {
            m_presenter->onContextMenuRequested({pos.x(), pos.y()});
        });

        m_presenter->onInitialized(this, dialogManager);
    }

    FolderBrowserQt::~FolderBrowserQt() {}

    void FolderBrowserQt::setProjectFolder(const QString &projectFolder) {
        m_treeView->setVisible(true);

        m_projectFolder = projectFolder;
        m_fileSystemModel->setRootPath(projectFolder);

        QModelIndex index = m_fileSystemModel->index(projectFolder);

        m_treeView->setRootIndex(index);
    }

    QString FolderBrowserQt::projectFolder() const {
        return m_projectFolder;
    }

    void FolderBrowserQt::displayContextualMenu(const Point &point, const Menu &menu) {
        QPoint pos;
        pos.setX(point.x);
        pos.setY(point.y);

        QMenu contextMenu(menu.text.c_str(), this);
        for (const Menu &childMenu : menu.childs) {
            setupMenu(&contextMenu, childMenu);
        }

        contextMenu.exec(this->mapToGlobal(pos));
    }
}

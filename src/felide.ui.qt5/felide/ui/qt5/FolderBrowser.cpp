
#include "FolderBrowser.hpp"

#include <QVBoxLayout>
#include <QBoxLayout>

namespace felide {
    FolderBrowser::FolderBrowser(QWidget *parent) : QWidget(parent) {

        m_treeView = new QTreeView(this);

        this->setLayout(new QVBoxLayout(this));
        this->layout()->addWidget(m_treeView);

        // instance file system model
        m_fileSystemModel = new QFileSystemModel(this);
        m_fileSystemModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);

        // bind view and model together
        m_treeView->setModel(m_fileSystemModel);
        m_treeView->setVisible(false);

        // connect signal handlers
        QObject::connect(m_treeView, &QTreeView::doubleClicked, [this](const QModelIndex index) {
            QString path = this->m_fileSystemModel->fileInfo(index).absoluteFilePath();

            this->projectItemOpenRequest(path);
        });
    }

    FolderBrowser::~FolderBrowser() {}

    void FolderBrowser::setProjectFolder(const QString &projectFolder) {
        m_treeView->setVisible(true);

        m_projectFolder = projectFolder;
        m_fileSystemModel->setRootPath(projectFolder);

        QModelIndex index = m_fileSystemModel->index(projectFolder);

        m_treeView->setRootIndex(index);
    }

    QString FolderBrowser::projectFolder() const {
        return m_projectFolder;
    }

    void FolderBrowser::displayFolder(const std::string &folder) {
        // TODO: Add implementation
    }
}

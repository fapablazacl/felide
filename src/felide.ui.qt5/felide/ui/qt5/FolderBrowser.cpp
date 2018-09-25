
#include "FolderBrowser.hpp"

#include <QVBoxLayout>
#include <QBoxLayout>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <iostream>

namespace felide {
    FolderBrowser::FolderBrowser(QWidget *parent) : QWidget(parent) {
        m_treeView = new QTreeView(this);

        this->setLayout(new QVBoxLayout(this));
        this->layout()->addWidget(m_treeView);

        // instance file system model
        m_fileSystemModel = new QFileSystemModel(this);
        m_fileSystemModel->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);

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
            QString path = this->m_fileSystemModel->fileInfo(index).absoluteFilePath();

            this->projectItemOpenRequest(path);
        });

        connect(m_treeView, &QTreeView::customContextMenuRequested, [this](const QPoint &pos) {
            QMenu contextMenu("Context Menu", this);
            QAction action("Rename", this);

            contextMenu.addAction(&action);

            this->connect(&action, &QAction::triggered, [this]() {
                
            });

            contextMenu.exec(this->mapToGlobal(pos));
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
        this->setProjectFolder(folder.c_str());
    }
}

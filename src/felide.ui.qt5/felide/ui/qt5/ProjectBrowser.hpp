
#ifndef __FELIDE_UI_QT5_PROJECT_BROWSER_HPP__
#define __FELIDE_UI_QT5_PROJECT_BROWSER_HPP__

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>

namespace felide {
    class ProjectBrowser : public QWidget {
        Q_OBJECT

    public:
        ProjectBrowser(QWidget *parent);

        ~ProjectBrowser();

        void setProjectFolder(const QString &projectFolder);

        QString projectFolder() const;

        Q_PROPERTY(QString projectFolder WRITE setProjectFolder READ projectFolder NOTIFY projectFolderChanged)

    signals:
        void projectFolderChanged(const QString &projectFolder);

        void projectItemOpenRequest(const QString &projectItemPath);

    private:
        QString m_projectFolder;
        QTreeView *m_treeView = nullptr;
        QFileSystemModel *m_fileSystemModel = nullptr;
    };
}

#endif

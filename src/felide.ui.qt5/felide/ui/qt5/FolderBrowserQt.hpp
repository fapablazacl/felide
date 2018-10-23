
#ifndef __FELIDE_UI_QT5_FOLDERBROWSER_HPP__
#define __FELIDE_UI_QT5_FOLDERBROWSER_HPP__

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>

#include <felide/ui/FolderBrowser.hpp>

namespace felide {
    class DialogManagerQt;
    class FELIDE_API FolderBrowserPresenter;
    class FELIDE_API DialogManager;

    class FolderBrowserQt : public QWidget, public FolderBrowser {
        Q_OBJECT

    public:
        void displayFolder(const std::string &folder) override;

    public:
        FolderBrowserQt(QWidget *parent, FolderBrowserPresenter *presenter, DialogManagerQt *dialogManager);

        ~FolderBrowserQt();

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

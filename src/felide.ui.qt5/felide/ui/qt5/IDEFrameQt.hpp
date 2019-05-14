
#ifndef __FELIDE_UI_QT5_MAINWINDOW_HPP__
#define __FELIDE_UI_QT5_MAINWINDOW_HPP__

#include <QMainWindow>
#include <QDockWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <map>

#include <felide/ui/ide-frame/IDEFramePresenter.hpp>
#include <felide/ui/ide-frame/IDEFrame.hpp>
#include <felide/ui/folder-browser/FolderBrowserPresenter.hpp>
#include <felide/ui/document-manager/DocumentManagerPresenter.hpp>
#include <felide/ui/Menu.hpp>
#include "DocumentManagerQt.hpp"
#include "DialogManagerQt.hpp"

namespace felide {
    class FolderBrowserQt;
    class IDEFrameQt : public QMainWindow, public IDEFrame {
        Q_OBJECT;

    public:
        explicit IDEFrameQt(IDEFramePresenter *controller);

    public:
        virtual DocumentManager* getDocumentManager() override;

        virtual DialogManager* getDialogManager() override;
        
        virtual FolderBrowser* getFolderBrowser() override;
        
        virtual void close() override;

        virtual void show() override;

    private:
        void setupMenuBar();
        void setupDocumentManager();
        void setupDockUI();

    private:
        virtual void closeEvent(QCloseEvent *evt) override;
        
    private:
        DocumentManagerQt *m_editorManager = nullptr;
        std::unique_ptr<DialogManagerQt> m_dialogManager = nullptr;
        
    private:
        FolderBrowserQt *m_folderBrowser;
        QDockWidget *m_folderBrowserDock;
    };
}

#endif

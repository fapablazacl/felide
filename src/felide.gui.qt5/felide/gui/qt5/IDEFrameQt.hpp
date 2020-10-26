
#ifndef __FELIDE_UI_QT5_MAINWINDOW_HPP__
#define __FELIDE_UI_QT5_MAINWINDOW_HPP__

#include <map>

#include <QMainWindow>
#include <QDockWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <felide/gui/ide-frame/IDEFramePresenter.hpp>
#include <felide/gui/ide-frame/IDEFrame.hpp>
#include <felide/gui/folder-browser/FolderBrowserPresenter.hpp>
#include <felide/gui/document-manager/DocumentManagerPresenter.hpp>
#include <felide/gui/Menu.hpp>
#include <felide/gui/MenuPanel.hpp>

#include "DialogManagerQt.hpp"
#include "DocumentManagerMdiQt.hpp"

namespace felide {
    class FolderBrowserQt;
    class IDEFrameQt : public QMainWindow, public IDEFrame, public MenuPanel {
        Q_OBJECT;

    public:
        explicit IDEFrameQt(IDEFramePresenter *controller);

    public:
        virtual DocumentManager* getDocumentManager() override;

        virtual DialogManager* getDialogManager() override;
        
        virtual FolderBrowser* getFolderBrowser() override;
        
        virtual void close() override;

        virtual void show() override;

        virtual void setupMenuBar(const Menu &menu) override;

    private:
        void setupDocumentManager();
        void setupDockUI();

    private:
        virtual void closeEvent(QCloseEvent *evt) override;
        
    private:
        DocumentManagerMdiQt *mDocumentManager = nullptr;
        std::unique_ptr<DialogManagerQt> mDialogManager = nullptr;
        
    private:
        FolderBrowserQt *mFolderBrowser;
        QDockWidget *mFolderBrowserDock;
    };
}

#endif

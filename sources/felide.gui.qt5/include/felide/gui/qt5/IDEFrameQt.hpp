
#ifndef __FELIDE_UI_QT5_MAINWINDOW_HPP__
#define __FELIDE_UI_QT5_MAINWINDOW_HPP__

#include <map>

#include <QMainWindow>
#include <QDockWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <felide/gui/IDEFramePresenter.hpp>
#include <felide/gui/IDEFrame.hpp>
#include <felide/gui/FolderBrowserPresenter.hpp>
#include <felide/gui/DocumentManagerPresenter.hpp>
#include <felide/gui/Menu.hpp>
#include <felide/gui/MenuPanel.hpp>

#include <felide/gui/qt5/DialogManagerQt.hpp>
#include <felide/gui/qt5/DocumentManagerMdiQt.hpp>

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

        virtual void showPanel(const Panel panel) override;

        virtual void setupMenuBar(const Menu &menu) override;

    private:
        void setupDocumentManager();
        void setupDockUI();

    private:
        virtual void closeEvent(QCloseEvent *evt) override;
        
    private:
        DocumentManagerMdiQt *mDocumentManager = nullptr;
        std::unique_ptr<DialogManagerQt> mDialogManager;
        FolderBrowserQt *mFolderBrowser = nullptr;
        QDockWidget *mFolderBrowserDock = nullptr;
    };
}

#endif

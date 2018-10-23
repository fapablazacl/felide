
#ifndef __FELIDE_UI_QT5_MAINWINDOW_HPP__
#define __FELIDE_UI_QT5_MAINWINDOW_HPP__

#include <QMainWindow>
#include <QDockWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <map>

#include <felide/ui/IDEFramePresenter.hpp>
#include <felide/ui/IDEFrame.hpp>
#include <felide/ui/FolderBrowserPresenter.hpp>
#include <felide/ui/Menu.hpp>
#include "EditorManagerQt.hpp"
#include "DialogManagerQt.hpp"

namespace felide {
    class FolderBrowserQt;
    class IDEFrameQt : public QMainWindow, public IDEFrame {
        Q_OBJECT;

    public:
        explicit IDEFrameQt(IDEFramePresenter *presenter);

    public:
        virtual EditorManager* getEditorManager() override;

        virtual DialogManager* getDialogManager() override;
        
        virtual FolderBrowser* getFolderBrowser() override;
        
        virtual void close() override;

        virtual void show() override;

    private:
        void setupMenuBar();
        void setupEditorManager();
        void setupDockUI();

        void setupFolderBrowser();

    private:
        virtual void closeEvent(QCloseEvent *evt) override;
        
    private:
        EditorManagerQt *m_editorManager = nullptr;
        std::unique_ptr<DialogManagerQt> m_dialogManager = nullptr;
        
    private:
        FolderBrowserPresenter m_folderBrowserPresenter;
        FolderBrowserQt *m_folderBrowser;
        QDockWidget *m_folderBrowserDock;
    };
}

#endif


#ifndef __FELIDE_UI_QT5_MAINWINDOW_HPP__
#define __FELIDE_UI_QT5_MAINWINDOW_HPP__

#include <QMainWindow>
#include <QDockWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <map>

#include <felide/ui/MainWindowPresenter.hpp>
#include <felide/ui/MainWindowView.hpp>
#include <felide/ui/Menu.hpp>
#include "EditorManager.hpp"
#include "DialogManager.hpp"

namespace felide {
    class FolderBrowser;
    class MainWindow : public QMainWindow, public MainWindowView {
        Q_OBJECT;

    public:
        MainWindow();

    public:
        virtual EditorManagerView* getEditorManagerView() override;

        virtual DialogManagerView* getDialogManagerView() override;
        
        virtual FolderBrowserView* getFolderBrowserView() override;
        
        virtual void close() override;

    private:
        void setupMenuBar();
        void setupEditorManager();
        void setupDockUI();

    private:
        virtual void closeEvent(QCloseEvent *evt) override;
        
    private:
        Menu mainMenu;
        MainWindowPresenter presenter;

        EditorManager *m_editorManager = nullptr;

        std::unique_ptr<DialogManager> m_dialogManager = nullptr;
        
    private:
        FolderBrowser *m_folderBrowser;
        QDockWidget *m_folderBrowserDock;
    };
}

#endif

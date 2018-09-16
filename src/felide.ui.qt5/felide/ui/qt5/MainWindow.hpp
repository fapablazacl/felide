
#ifndef __FELIDE_UI_QT5_MAINWINDOW_HPP__
#define __FELIDE_UI_QT5_MAINWINDOW_HPP__

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <map>

#include "../MainWindowPresenter.hpp"
#include "../MainWindowView.hpp"
#include "../Menu.hpp"
#include "EditorManager.hpp"

namespace felide {
    class MainWindow : public QMainWindow, public MainWindowView {
        Q_OBJECT;

    public:
        MainWindow();

    public:
        virtual boost::optional<std::string> showDialogModal(const DialogViewData &dialogViewData) override;
        
        virtual boost::optional<bool> showAskModal(const std::string &title, const std::string &message) override;

        virtual EditorManagerView* getEditorManagerView() override;

    private:
        void setupMenuBar();
        void setupEditorManager();

    private:
        Menu mainMenu;
        MainWindowPresenter presenter;

        EditorManager *m_tabbedEditorManager = nullptr;
    };
}

#endif

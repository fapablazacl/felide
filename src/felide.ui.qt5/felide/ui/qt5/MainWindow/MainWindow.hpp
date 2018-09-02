
#ifndef __FELIDE_UI_QT5_MAINWINDOW_HPP_
#define __FELIDE_UI_QT5_MAINWINDOW_HPP__

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <map>

#include "MainWindowPresenter.hpp"
#include "MainWindowView.hpp"
#include "Menu.hpp"

namespace felide {
    class MainWindow : public QMainWindow, public MainWindowView {
        Q_OBJECT;

    public:
        MainWindow();

    public:
        virtual std::optional<std::string> openFileDialog(const FileDialogViewData &fileDialogData) override;

        virtual std::optional<std::string> saveFileDialog(const FileDialogViewData &fileDialogData) override;

        virtual EditorView* appendEditor() override;

        virtual void removeEditor(const std::string &fileKey) override;

        virtual std::map<std::string, EditorView*> getEditor(const std::string &fileKey) override;

        virtual EditorView* getCurrentEditor() override;

    private:
        void setupMenuBar();

    private:
        Menu mainMenu;
        MainWindowPresenter presenter;
    };
}

#endif

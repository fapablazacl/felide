
#ifndef __FELIDE_UI_QT5_MAINWINDOW_HPP_
#define __FELIDE_UI_QT5_MAINWINDOW_HPP__

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <map>

namespace felide {
    class MainWindow : public QMainWindow {
        Q_OBJECT;

    public:
        MainWindow();

    private:
        void setupMenuBar();
    };
}

#endif

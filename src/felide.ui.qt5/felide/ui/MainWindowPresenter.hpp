
#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include "MainWindowModel.hpp"

namespace felide {
    class MainWindowView;
    class MainWindowPresenter {
    public:
        explicit MainWindowPresenter(MainWindowView *view);

        void fileNew();

        void fileSave();

        void fileSaveAs();

        void fileSaveAll();

        void fileClose();

        void fileExit();

    private:
        MainWindowView *view;
        MainWindowModel model;
    };
} 

#endif

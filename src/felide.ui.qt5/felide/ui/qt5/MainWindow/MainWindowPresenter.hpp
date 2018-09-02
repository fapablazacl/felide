
#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include "MainWindowModel.hpp"

namespace felide {
    class MainWindowView;
    class MainWindowPresenter {
    public:
        MainWindowPresenter();

        void attachView(MainWindowView *view);

        void detachView();

    public:
        void fileNew();        

        void fileOpen();

        void fileSave();

        void fileSaveAs();

        void fileSaveAll();

        void fileClose();

        void fileExit();

    private:
        MainWindowView *view = nullptr;
        MainWindowModel model;
    };
} 

#endif

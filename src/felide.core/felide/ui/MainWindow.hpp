
#ifndef __FELIDE_UI_MAINWINDOWVIEW_HPP__
#define __FELIDE_UI_MAINWINDOWVIEW_HPP__

#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API EditorManager;
    class FELIDE_API DialogManager;
    class FELIDE_API FolderBrowser;

    class FELIDE_API MainWindowPresenter;

    struct Menu;

    class FELIDE_API MainWindow {
    public:
        explicit MainWindow(MainWindowPresenter *presenter);

        virtual ~MainWindow();

        virtual EditorManager* getEditorManager() = 0;

        virtual DialogManager* getDialogManager() = 0;
        
        virtual FolderBrowser* getFolderBrowser() = 0;
        
        virtual void close() = 0;

        virtual void show() = 0;

    protected:
        MainWindowPresenter *m_presenter;
        Menu *m_menu;
    };
}

#endif

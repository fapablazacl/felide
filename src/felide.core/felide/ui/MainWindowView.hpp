
#ifndef __FELIDE_UI_MAINWINDOWVIEW_HPP__
#define __FELIDE_UI_MAINWINDOWVIEW_HPP__

#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API EditorManagerView;
    class FELIDE_API DialogManagerView;
    class FELIDE_API FolderBrowserView;

    class FELIDE_API MainWindowPresenter;

    struct Menu;

    class FELIDE_API MainWindowView {
    public:
        explicit MainWindowView(MainWindowPresenter *presenter);

        virtual ~MainWindowView();

        virtual EditorManagerView* getEditorManagerView() = 0;

        virtual DialogManagerView* getDialogManagerView() = 0;
        
        virtual FolderBrowserView* getFolderBrowserView() = 0;
        
        virtual void close() = 0;

        virtual void show() = 0;

    protected:
        MainWindowPresenter *m_presenter;
        Menu *m_menu;
    };
}

#endif

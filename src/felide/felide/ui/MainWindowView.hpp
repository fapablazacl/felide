
#ifndef __FELIDE_UI_MAINWINDOWVIEW_HPP__
#define __FELIDE_UI_MAINWINDOWVIEW_HPP__

namespace felide {
    class EditorManagerView;
    class DialogManagerView;
    class FolderBrowserView;
    class MainWindowView {
    public:
        virtual ~MainWindowView();

        virtual EditorManagerView* getEditorManagerView() = 0;

        virtual DialogManagerView* getDialogManagerView() = 0;
        
        virtual FolderBrowserView* getFolderBrowserView() = 0;
        
        virtual void close() = 0;
    };
}

#endif

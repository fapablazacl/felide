
#ifndef __FELIDE_UI_MAINWINDOWVIEW_HPP__
#define __FELIDE_UI_MAINWINDOWVIEW_HPP__

namespace felide {
    class EditorManagerView;
    class DialogManagerView;
    class MainWindowView {
    public:
        virtual ~MainWindowView();

        virtual EditorManagerView* getEditorManagerView() = 0;

        virtual DialogManagerView* getDialogManagerView() = 0;
    };
}

#endif

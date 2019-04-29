
#ifndef __FELIDE_UI_EDITORMANAGERCONTROLLER_HPP__
#define __FELIDE_UI_EDITORMANAGERCONTROLLER_HPP__

#include <cstddef>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API EditorManagerModel;
    class FELIDE_API Editor;
    class FELIDE_API EditorManager;
    class FELIDE_API EditorManagerController {
    public:
        explicit EditorManagerController(EditorManagerModel *model);

        void attachView(EditorManager *view);

        void onCloseEditor(Editor *editor);

        void onCloseOthers(Editor *editor);

        void onCloseToTheRight(Editor *editor);

        void onCloseAll();

    private:
        EditorManager *m_view = nullptr;
        EditorManagerModel *m_model = nullptr;
    };
}

#endif

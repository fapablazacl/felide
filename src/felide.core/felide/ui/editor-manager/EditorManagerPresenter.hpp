
#ifndef __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__
#define __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__

#include <cstddef>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API EditorManagerModel;
    class FELIDE_API Editor;
    class FELIDE_API EditorManager;
    class FELIDE_API EditorManagerPresenter {
    public:
        explicit EditorManagerPresenter(EditorManagerModel *model);

        void attachView(EditorManager *view);

        void closeEditor(Editor *editor);

        void closeOthers(Editor *editor);

        void closeToTheRight(Editor *editor);

        void closeAll();

    private:
        EditorManager *m_view = nullptr;
        EditorManagerModel *m_model = nullptr;
    };
}

#endif

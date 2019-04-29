
#ifndef __FELIDE_UI_EDITORMANAGERCONTROLLER_HPP__
#define __FELIDE_UI_EDITORMANAGERCONTROLLER_HPP__

#include <cstddef>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API DocumentManagerModel;
    class FELIDE_API Document;
    class FELIDE_API DocumentManager;
    class FELIDE_API DocumentManagerController {
    public:
        explicit DocumentManagerController(DocumentManagerModel *model);

        void attachView(DocumentManager *view);

        void onCloseEditor(Document *editor);

        void onCloseOthers(Document *editor);

        void onCloseToTheRight(Document *editor);

        void onCloseAll();

    private:
        DocumentManager *m_view = nullptr;
        DocumentManagerModel *m_model = nullptr;
    };
}

#endif


#ifndef __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__
#define __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__

#include <cstddef>
#include <map>
#include <tuple>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API Document;
    class FELIDE_API DocumentModel;

    class FELIDE_API DocumentManagerModel;
    class FELIDE_API DocumentManager;
    class FELIDE_API DocumentManagerPresenter {
    public:
        explicit DocumentManagerPresenter(DocumentManagerModel *model);

        void attachView(DocumentManager *view);

        void onCloseDocument(Document *document);

        void onCloseOthers(Document *document);

        void onCloseToTheRight(Document *document);

        void onCloseAll();

        std::tuple<Document*, DocumentModel*> createDocument(const int tag);
        std::tuple<Document*, DocumentModel*> createDocument(const std::string &filePath);

    private:
        DocumentManager *view = nullptr;
        DocumentManagerModel *model = nullptr;

        std::map<Document*, DocumentModel*> documentModels;
    };
}

#endif

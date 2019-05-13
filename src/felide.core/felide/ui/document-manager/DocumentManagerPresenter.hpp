
#ifndef __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__
#define __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__

#include <cstddef>
#include <map>
#include <tuple>
#include <list>

#include <boost/filesystem/path.hpp>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API Document;
    class FELIDE_API DocumentModel;
    class FELIDE_API DocumentPresenter;

    class FELIDE_API DocumentManagerModel;
    class FELIDE_API DocumentManager;
    class FELIDE_API DocumentManagerPresenter {
    public:
        explicit DocumentManagerPresenter(DocumentManagerModel *model);

        ~DocumentManagerPresenter();

        void onInitialized(DocumentManager *view);

        void onNewDocument();

        void onOpenDocument(const boost::filesystem::path &path);

        void onSaveDocument();

        void onSaveAsDocument();

        void onCloseDocument(Document *document);

        void onCloseOthers(Document *document);

        void onCloseToTheRight(Document *document);

        void onCloseAll();

    private:
        DocumentPresenter* createDocumentMVP();

        DocumentPresenter* createDocumentMVP(const boost::filesystem::path &filePath);

        DocumentPresenter* findDocumentPresenter(Document *document);

        DocumentPresenter* findDocumentPresenter(const boost::filesystem::path &filePath);

    private:
        DocumentManager *view = nullptr;
        DocumentManagerModel *model = nullptr;

        std::list<std::unique_ptr<DocumentPresenter>> documentPresenters;
    };
}

#endif

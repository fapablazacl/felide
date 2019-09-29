
#ifndef __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__
#define __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__

#include <cstddef>
#include <map>
#include <tuple>
#include <list>

#include <boost/filesystem/path.hpp>
#include <felide/core/Predef.hpp>

namespace felide {
    class FELIDE_API DialogManager;

    class FELIDE_API Document;
    class FELIDE_API DocumentModel;
    class FELIDE_API DocumentPresenter;

    class FELIDE_API DocumentManagerModel;
    class FELIDE_API DocumentManager;
    class FELIDE_API DocumentManagerPresenter {
    public:
        explicit DocumentManagerPresenter(DocumentManagerModel *model);

        ~DocumentManagerPresenter();

        void onInitialized(DocumentManager *view, DialogManager *dialogView);

        void onNewDocument();

        void onOpenDocument(const boost::filesystem::path &path);

        void onSaveDocument();

        void onSaveAsDocument();

        void onSaveAllDocuments();

        void onCloseCurrentDocument();

        void onCloseDocument(Document *document);

        void onCloseOtherDocuments(Document *document);

        void onCloseDocumentsToTheRight(Document *document);

        void onCloseAllDocuments();

    private:
        DocumentPresenter* createDocumentMVP();

        DocumentPresenter* createDocumentMVP(const boost::filesystem::path &filePath);

        DocumentPresenter* findDocumentPresenter(Document *document);

        DocumentPresenter* findDocumentPresenter(const boost::filesystem::path &filePath);

        void closeDocumentPresenter(DocumentPresenter *documentPresenter);

        void closeDocumentMVP(DocumentPresenter *documentPresenter);

    private:
        DialogManager *dialogView = nullptr;
        DocumentManager *view = nullptr;
        DocumentManagerModel *model = nullptr;

        std::list<std::unique_ptr<DocumentPresenter>> documentPresenters;
    };
}

#endif

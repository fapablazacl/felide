
#ifndef __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__
#define __FELIDE_UI_EDITORMANAGERPRESENTER_HPP__

#include <cstddef>
#include <map>
#include <tuple>
#include <list>

#include <boost/filesystem/path.hpp>
#include <Xenoide/Core/Predef.hpp>

namespace felide {
    class DialogManager;

    class Document;
    class DocumentModel;
    class DocumentPresenter;

    class DocumentManagerModel;
    class DocumentManager;
    class DocumentManagerPresenter {
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

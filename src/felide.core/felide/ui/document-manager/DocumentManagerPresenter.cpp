
#include "DocumentManagerPresenter.hpp"

#include "DocumentManager.hpp"
#include "DocumentManagerModel.hpp"

#include <felide/util/FileService.hpp>
#include <felide/ui/document/DocumentModel.hpp>
#include <felide/ui/document/DocumentPresenter.hpp>

namespace felide {
    DocumentManagerPresenter::DocumentManagerPresenter(DocumentManagerModel *model) {
        this->model = model;
    }

    DocumentManagerPresenter::~DocumentManagerPresenter() {}

    void DocumentManagerPresenter::onInitialized(DocumentManager *view) {
        this->view = view;
    }

    void DocumentManagerPresenter::onNewDocument() {
        auto documentModel = model->createDocument();
        auto documentPresenter = this->createDocumentPresenter(documentModel);
        auto documentView = view->appendDocument(documentPresenter);
    }

    void DocumentManagerPresenter::onOpenDocument(const boost::filesystem::path &filePath) {
        auto fileService = FileService::create();

        auto documentModel = model->createDocument();
        documentModel->setContent(fileService->load(filePath));
        documentModel->setFilePath(filePath.string());

        auto documentPresenter = this->createDocumentPresenter(documentModel);
        auto documentView = view->appendDocument(documentPresenter);
    }

    void DocumentManagerPresenter::onCloseDocument(Document *document) {
        view->closeDocument(document);
    }

    void DocumentManagerPresenter::onCloseOthers(Document *document) {
        auto documents = view->enumerateDocuments();
        
        for (auto current : documents) {
            if (current != document) {
                view->closeDocument(current);
            }
        }
    }

    void DocumentManagerPresenter::onCloseToTheRight(Document *document) {
        bool close = false;

        auto documents = view->enumerateDocuments();

        for (auto current : documents) {
            if (close == true) {
                view->closeDocument(current);
            }

            if (current == document) {
                close = true;
            }
        }
    }

    void DocumentManagerPresenter::onCloseAll() {
        auto editors = view->enumerateDocuments();

        for (auto editor : editors) {
            view->closeDocument(editor);
        }
    }

    DocumentPresenter* DocumentManagerPresenter::createDocumentPresenter(DocumentModel *documentModel) {
        auto presenter = new DocumentPresenter(documentModel);

        documentPresenters.emplace_back(presenter);

        return presenter;
    }
}

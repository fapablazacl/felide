
#include "DocumentManagerPresenter.hpp"

#include "DocumentManager.hpp"
#include "DocumentManagerModel.hpp"

#include <algorithm>

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
        this->createDocumentMVP();
    }

    void DocumentManagerPresenter::onOpenDocument(const boost::filesystem::path &filePath) {
        DocumentPresenter *documentPresenter;

        if (documentPresenter = this->findDocumentPresenter(filePath)) {
            view->setCurrentDocument(documentPresenter->getView());
        } else {
            this->createDocumentMVP(filePath);
        }
    }

    void DocumentManagerPresenter::onSaveDocument() {
        if (auto document = view->getCurrentDocument()) {
            if (auto documentPresenter = this->findDocumentPresenter(document)) {
                documentPresenter->onSave();
            }
        }
    }

    void DocumentManagerPresenter::onSaveAsDocument() {

    }

    void DocumentManagerPresenter::onCloseDocument(Document *document) {
        if (auto documentPresenter = this->findDocumentPresenter(document)) {
            view->closeDocument(document);
            model->closeDocument(documentPresenter->getModel());
        }
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

    DocumentPresenter* DocumentManagerPresenter::createDocumentMVP() {
        return this->createDocumentMVP("");
    }

    DocumentPresenter* DocumentManagerPresenter::createDocumentMVP(const boost::filesystem::path &filePath) {
        auto documentModel = model->createDocument();
        documentModel->setFilePath(filePath.string());

        auto documentPresenter = new DocumentPresenter(documentModel);
        auto documentView = view->appendDocument(documentPresenter);

        documentPresenters.emplace_back(documentPresenter);

        return documentPresenter;
    }

    DocumentPresenter* DocumentManagerPresenter::findDocumentPresenter(Document *document) {
        auto &dps = documentPresenters;
        auto documentPresenterIt = std::find_if(dps.begin(), dps.end(), [document](std::unique_ptr<DocumentPresenter> &dp) {
            return dp->getView() == document;
        });

        if (documentPresenterIt != dps.end()) {
            return documentPresenterIt->get();
        }

        return nullptr;
    }
    
    DocumentPresenter* DocumentManagerPresenter::findDocumentPresenter(const boost::filesystem::path &filePath) {
        auto &dps = documentPresenters;
        auto documentPresenterIt = std::find_if(dps.begin(), dps.end(), [filePath](std::unique_ptr<DocumentPresenter> &dp) {
            return dp->hasFilePath(filePath);
        });

        if (documentPresenterIt != dps.end()) {
            return documentPresenterIt->get();
        }

        return nullptr;
    }
}

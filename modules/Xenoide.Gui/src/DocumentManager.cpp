
#include <Xenoide/Gui/DocumentManager.hpp>

namespace Xenoide {
    DocumentManager::DocumentManager(DocumentManagerPresenter *presenter) {
        this->presenter = presenter;
    }

    DocumentManager::~DocumentManager() {}

    std::vector<Document*> DocumentManager::enumerateDocuments() {
        std::vector<Document*> editors;

        editors.reserve(this->getDocumentCount());

        for (int i=0; i<this->getDocumentCount(); i++) {
            editors.push_back(this->getDocument(i));
        }

        return editors;
    }

    void DocumentManager::closeDocuments(const std::vector<Document*> &documents) {
        for (Document *document : documents) {
            this->closeDocument(document);
        }
    }
}

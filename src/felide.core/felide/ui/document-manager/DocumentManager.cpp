
#include "DocumentManager.hpp"

namespace felide {
    DocumentManager::DocumentManager(DocumentManagerController *presenter) {
        m_presenter = presenter;
    }

    DocumentManager::~DocumentManager() {}

    std::vector<Document*> DocumentManager::enumerateDocuments() {
        std::vector<Document*> editors;

        for (int i=0; i<this->getDocumentCount(); i++) {
            editors.push_back(this->getDocument(i));
        }

        return editors;
    }
}

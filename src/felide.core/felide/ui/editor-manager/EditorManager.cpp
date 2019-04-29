
#include "EditorManager.hpp"

namespace felide {
    DocumentManager::DocumentManager(DocumentManagerController *presenter) {
        m_presenter = presenter;
    }

    DocumentManager::~DocumentManager() {}

    std::vector<Document*> DocumentManager::getEditors() {
        std::vector<Document*> editors;

        for (int i=0; i<this->getEditorCount(); i++) {
            editors.push_back(this->getEditor(i));
        }

        return editors;
    }
}

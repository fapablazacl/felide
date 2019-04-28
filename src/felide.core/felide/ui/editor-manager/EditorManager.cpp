
#include "EditorManager.hpp"

namespace felide {
    EditorManager::EditorManager(EditorManagerController *presenter) {
        m_presenter = presenter;
    }

    EditorManager::~EditorManager() {}

    std::vector<Editor*> EditorManager::getEditors() {
        std::vector<Editor*> editors;

        for (int i=0; i<this->getEditorCount(); i++) {
            editors.push_back(this->getEditor(i));
        }

        return editors;
    }
}

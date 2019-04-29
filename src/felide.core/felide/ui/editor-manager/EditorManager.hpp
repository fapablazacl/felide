
#ifndef __FELIDE_UI_DOCUMENTMANAGER_HPP__
#define __FELIDE_UI_DOCUMENTMANAGER_HPP__

#include <cstddef>
#include <felide/Predef.hpp>
#include <vector>

namespace felide {
    class FELIDE_API DocumentManagerController;
    class FELIDE_API Document;
    class FELIDE_API DocumentManager {
    public:
        explicit DocumentManager(DocumentManagerController *presenter);

        virtual ~DocumentManager();

        virtual Document* appendEditor() = 0;

        virtual Document* getCurrentEditor() = 0;

        virtual std::size_t getEditorCount() const = 0;

        virtual Document* getEditor(const std::size_t index) = 0;
        
        virtual void closeEditor(Document *editor) = 0;

        virtual void showEditor(Document *editor) = 0;

        std::vector<Document*> getEditors();

    protected:
        DocumentManagerController *m_presenter = nullptr;
    };
} 

#endif

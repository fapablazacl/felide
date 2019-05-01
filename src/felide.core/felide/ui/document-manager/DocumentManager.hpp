
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

        virtual Document* appendDocument() = 0;

        virtual Document* getCurrentDocument() = 0;

        virtual std::size_t getDocumentCount() const = 0;

        virtual Document* getDocument(const std::size_t index) = 0;
        
        virtual void closeDocument(Document *editor) = 0;

        virtual void showDocument(Document *editor) = 0;

        std::vector<Document*> enumerateDocuments();

    protected:
        DocumentManagerController *m_presenter = nullptr;
    };
} 

#endif


#include "CIdeDocumentManager.hpp"

namespace felide {
    int CIdeDocumentManager::OnCreate(LPCREATESTRUCT lpCreateStruct) {

        return 0;
    }

    void CIdeDocumentManager::OnSize(UINT nType, CSize size) {
        
    }



    Document* CIdeDocumentManager::getDocument(const std::size_t index)
    {
        return nullptr;
    }


    void CIdeDocumentManager::closeDocument(Document* editor)
    {
    }


    void CIdeDocumentManager::showDocument(Document* editor)
    {
    }


    void CIdeDocumentManager::closeDocuments(const std::vector<Document*>& documents)
    {
    }


    std::vector<Document*> CIdeDocumentManager::enumerateDocuments()
    {
        return std::vector<Document*>();
    }


    CIdeDocumentManager::CIdeDocumentManager(DocumentManagerPresenter* presenter) : DocumentManager(presenter)
    {
    }


    CIdeDocumentManager::~CIdeDocumentManager()
    {
    }


    Document* CIdeDocumentManager::appendDocument(DocumentPresenter* presenter)
    {
        return nullptr;
    }


    Document* CIdeDocumentManager::getCurrentDocument()
    {
        return nullptr;
    }


    void CIdeDocumentManager::setCurrentDocument(Document* document)
    {
    }


    std::size_t CIdeDocumentManager::getDocumentCount() const
    {
        return std::size_t();
    }
}

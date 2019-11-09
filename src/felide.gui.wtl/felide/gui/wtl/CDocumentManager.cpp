
#include "CDocumentManager.hpp"

namespace felide {
    int CDocumentManager::OnCreate(LPCREATESTRUCT lpCreateStruct) {

        return 0;
    }

    void CDocumentManager::OnSize(UINT nType, CSize size) {
        
    }



    Document* CDocumentManager::getDocument(const std::size_t index)
    {
        return nullptr;
    }


    void CDocumentManager::closeDocument(Document* editor)
    {
    }


    void CDocumentManager::showDocument(Document* editor)
    {
    }


    void CDocumentManager::closeDocuments(const std::vector<Document*>& documents)
    {
    }


    std::vector<Document*> CDocumentManager::enumerateDocuments()
    {
        return std::vector<Document*>();
    }


    CDocumentManager::CDocumentManager(DocumentManagerPresenter* presenter) : DocumentManager(presenter)
    {
    }


    CDocumentManager::~CDocumentManager()
    {
    }


    Document* CDocumentManager::appendDocument(DocumentPresenter* presenter)
    {
        return nullptr;
    }


    Document* CDocumentManager::getCurrentDocument()
    {
        return nullptr;
    }


    void CDocumentManager::setCurrentDocument(Document* document)
    {
    }


    std::size_t CDocumentManager::getDocumentCount() const
    {
        return std::size_t();
    }
}

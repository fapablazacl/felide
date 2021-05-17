
#include "CDocumentManager.hpp"

namespace felide {
    int CDocumentManager::OnCreate(LPCREATESTRUCT lpCreateStruct) {
        const DWORD dwStyle = WS_CHILD | WS_VISIBLE;

        RECT clientRect = {};
        this->GetClientRect(&clientRect);

        tabControl.Create(m_hWnd, clientRect, "", dwStyle);

        tabControl.AddItem("Test1");
        tabControl.AddItem("Test2");
        tabControl.AddItem("Test3");

        return 0;
    }

    void CDocumentManager::OnSize(UINT nType, CSize size) {
        
    }
}


namespace felide {
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

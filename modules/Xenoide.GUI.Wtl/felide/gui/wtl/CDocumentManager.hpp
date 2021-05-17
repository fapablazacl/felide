
#pragma once 

#include <felide/gui/document-manager/DocumentManager.hpp>

#include <atlbase.h>
#include <atlwin.h>
#include <atlapp.h>
#include <atlctrls.h>
#include <atlmisc.h>
#include <atlcrack.h>

namespace felide {

    /**
     * @brief Source code editor window
     */
    class CDocumentManager : public CWindowImpl<CDocumentManager>, public DocumentManager {
    public:
        DECLARE_WND_CLASS(_T("CDocumentManager"))
        
        BEGIN_MSG_MAP(CDocument)
            MSG_WM_CREATE(OnCreate)
            MSG_WM_SIZE(OnSize)
        END_MSG_MAP()

        CDocumentManager(DocumentManagerPresenter *presenter);

        virtual ~CDocumentManager();

        virtual Document* appendDocument(DocumentPresenter *presenter) override;

        virtual Document* getCurrentDocument() override;

        virtual void setCurrentDocument(Document *document) override;

        virtual std::size_t getDocumentCount() const override;

        virtual Document* getDocument(const std::size_t index) override;
        
        virtual void closeDocument(Document *editor) override;

        virtual void showDocument(Document *editor) override;

        virtual void closeDocuments(const std::vector<Document*> &documents) override;

        std::vector<Document*> enumerateDocuments();

    public:
        int OnCreate(LPCREATESTRUCT lpCreateStruct);

        void OnSize(UINT nType, CSize size);

    private:
        CTabCtrl tabControl;
    };
}

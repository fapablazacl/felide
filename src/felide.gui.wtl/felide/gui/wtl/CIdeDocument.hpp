
#pragma once 

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
    class CIdeDocument : public CWindowImpl<CIdeDocument> {
    public:
        DECLARE_WND_CLASS(_T("CIdeDocument"))
        
        BEGIN_MSG_MAP(CIdeDocument)
            MSG_WM_CREATE(OnCreate)
            MSG_WM_SIZE(OnSize)
        END_MSG_MAP()

    public:
        int OnCreate(LPCREATESTRUCT lpCreateStruct);

        void OnSize(UINT nType, CSize size);

        void SetText(const CString &string);

        CString GetText() const;

    private:
        CEdit m_edit;
    };
}

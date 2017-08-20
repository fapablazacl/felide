
#pragma once 

#include <atlbase.h>
#include <atlwin.h>
#include <atlapp.h>
#include <atlctrls.h>
#include <atlmisc.h>
#include <atlcrack.h>

namespace felide::view::win {

    /**
     * @brief Source code editor window
     */
    class CEditor : public CWindowImpl<CEditor> {
    public:
        DECLARE_WND_CLASS(_T("CEditor"))
        
        BEGIN_MSG_MAP(CEditor)
            MSG_WM_CREATE(OnCreate)
            MSG_WM_SIZE(OnSize)
        END_MSG_MAP()

    public:
        int OnCreate(LPCREATESTRUCT lpCreateStruct);

        void OnSize(UINT nType, CSize size);

    private:
        CEdit m_edit;
    };
}

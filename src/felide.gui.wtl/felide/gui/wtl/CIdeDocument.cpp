
#include "CIdeDocument.hpp"

namespace felide {
    int CIdeDocument::OnCreate(LPCREATESTRUCT lpCreateStruct) {
        RECT rcClient;
        this->GetClientRect(&rcClient);

        const DWORD dwStyle = ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL;

        m_edit.Create(m_hWnd, rcClient, "Test", dwStyle);

        return 0;
    }

    void CIdeDocument::OnSize(UINT nType, CSize size) {
        m_edit.ResizeClient(size.cx, size.cy, TRUE);
    }

    void CIdeDocument::SetText(const CString &string) {
        m_edit.SetWindowText(string);
    }

    CString CIdeDocument::GetText() const {
        return "";
    }
}

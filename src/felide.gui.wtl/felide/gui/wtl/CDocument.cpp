
#include "CDocument.hpp"

namespace felide {
    int CDocument::OnCreate(LPCREATESTRUCT lpCreateStruct) {
        RECT rcClient;
        this->GetClientRect(&rcClient);

        const DWORD dwStyle = ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL;

        m_edit.Create(m_hWnd, rcClient, "Test", dwStyle);

        return 0;
    }

    void CDocument::OnSize(UINT nType, CSize size) {
        m_edit.ResizeClient(size.cx, size.cy, TRUE);
    }

    void CDocument::SetText(const CString &string) {
        m_edit.SetWindowText(string);
    }

    CString CDocument::GetText() const {
        return "";
    }
}

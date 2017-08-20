
#include "CMainFrame.hpp"

namespace felide::view::win {

    LRESULT CMainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
        RECT rcClient;
        this->GetClientRect(&rcClient);

        const DWORD dwStyle = WS_CHILD | WS_VISIBLE;

        m_editor.Create(m_hWnd, rcClient, "", dwStyle);
        return 0;
    }

    LRESULT CMainFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
        DestroyWindow();

        return 0;
    }

    LRESULT CMainFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
        PostQuitMessage(0);

        return 0;
    }

    LRESULT CMainFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
        RECT rcClient;
        this->GetClientRect(&rcClient);

        const int w = rcClient.right - rcClient.left;
        const int h = rcClient.bottom - rcClient.top;

        m_editor.ResizeClient(w, h, TRUE);

        return 0;
    }
}


#include "CMainFrame.hpp"

namespace felide::view::win {

	LRESULT CMainFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
		DestroyWindow();

		return 0;
	}

	LRESULT CMainFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
		PostQuitMessage(0);

		return 0;
	}
}

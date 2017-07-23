
#pragma once 

#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>

namespace felide::view::win {
	
	class CMainFrame : public CWindowImpl<CMainFrame, CWindow, CFrameWinTraits> {
	public:
		DECLARE_WND_CLASS(_T("CMainFrame Class"))

		BEGIN_MSG_MAP(CMainFrame)
			MESSAGE_HANDLER(WM_CLOSE, OnClose)
			MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		END_MSG_MAP()

	public:
		LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

		LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	};
}

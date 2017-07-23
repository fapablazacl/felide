
#pragma once 

#include <atlbase.h>
#include <atlwin.h>
#include <atlapp.h>
#include <atlctrls.h>

namespace felide::view::win {

	/**
	 * @brief Source code editor window
	 */
	class CEditor : public CWindowImpl<CEditor> {
	public:
		DECLARE_WND_CLASS(_T("CEditor"))
		
		BEGIN_MSG_MAP(CEditor)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
		END_MSG_MAP()

	public:
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

	private:
		CEdit m_edit;
	};
}


#pragma once 

#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atluser.h>

#include "CEditor.hpp"

namespace felide::view::win {
    
    class CMainFrame : public CWindowImpl<CMainFrame, CWindow, CFrameWinTraits> {
    public:
        DECLARE_WND_CLASS(_T("CMainFrame Class"))

        BEGIN_MSG_MAP(CMainFrame)
            MESSAGE_HANDLER(WM_CREATE, OnCreate)
            MESSAGE_HANDLER(WM_CLOSE, OnClose)
            MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
            MESSAGE_HANDLER(WM_SIZE, OnSize)
        END_MSG_MAP()

    public:
        LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

        LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

        LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

        LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

    private:
        CEditor m_editor;
    };
}

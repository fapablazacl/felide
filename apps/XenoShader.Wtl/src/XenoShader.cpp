

#define STRICT
#define WIN32_LEAN_AND_MEAN
#define _WTL_USE_CSTRING

#include <atlbase.h>
#include <atlapp.h>

// WTL version of CComModule
extern CAppModule _Module;

#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atluser.h>
#include <atlmisc.h>
#include <atlcrack.h>
#include <atlsplit.h>

#include "resource.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


// All Dialogs must inherit from the CDialogImpl template class.
// Must declar a class-scoped member IDD, wich haves the dialog's resource identifier.
class AboutDlg : public CDialogImpl<AboutDlg> {
public:
    enum {IDD = IDD_ABOUT};

public:
    BEGIN_MSG_MAP(AboutDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        COMMAND_ID_HANDLER(IDOK, OnOKCancel)
        COMMAND_ID_HANDLER(IDCANCEL, OnOKCancel)
    END_MSG_MAP()

public:
    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        CenterWindow();

        // let the system set the focus
        return TRUE;
    }
 
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        EndDialog(IDCANCEL);
        return 0;
    }
 
    LRESULT OnOKCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        EndDialog(wID);
        return 0;
    }
};


class CodeView : public CWindowImpl<CodeView> {
public:
    DECLARE_WND_CLASS(NULL)

    BEGIN_MSG_MAP_EX(ClockView)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_TIMER(OnTimer)
        MSG_WM_ERASEBKGND(OnEraseBkgnd)
    END_MSG_MAP()

public:
    CodeView() {
        m_bMsgHandled = false;
    }

    LRESULT OnCreate(LPCREATESTRUCT cs) {
        SetMsgHandled(true);

        return 0;
    }

    void OnDestroy() {
        SetMsgHandled(false);
    }

    void OnTimer(UINT uTimerID) {
        if (uTimerID != 1) {
            SetMsgHandled(false);
        } else {
            RedrawWindow();
        }
    }

    LRESULT OnEraseBkgnd(HDC hDC) {
        CDCHandle dc(hDC);
        CRect rc;
        SYSTEMTIME st;
        CString sTime;

        GetClientRect(rc);

        GetLocalTime(&st);
        sTime.Format(_T("The time is %d:%02d:%02d"), st.wHour, st.wMinute, st.wSecond);

        dc.SaveDC();
        dc.SetBkColor(RGB(255, 133, 0));
        dc.SetTextColor(RGB(0, 0, 0));
        dc.ExtTextOut (0, 0, ETO_OPAQUE, rc, sTime,  sTime.GetLength(), NULL);
        dc.RestoreDC(-1);

        return 1;
    }

    void StartClock() {
        SetTimer(1, 1000);
    }

    void StopClock() {
        KillTimer(1);
    }
};


// Frame Windows are defined with CFrameWindowImpl
class MainFrame :   public CFrameWindowImpl<MainFrame>,
                    public CUpdateUI<MainFrame>/*,
                    public CMessageFilter,
                    public CIdleHandler*/ {
public:
    DECLARE_FRAME_WND_CLASS("MainFrame", IDR_MAINFRAME)

    BEGIN_UPDATE_UI_MAP(MainFrame)
        // UPDATE_ELEMENT(ID_CLOCK_START, UPDUI_MENUPOPUP)
        // UPDATE_ELEMENT(ID_CLOCK_STOP, UPDUI_MENUPOPUP)
    END_UPDATE_UI_MAP()

    BEGIN_MSG_MAP(MainFrame)
        COMMAND_ID_HANDLER_EX(ID_FILE_NEW, OnFileMenu)
        COMMAND_ID_HANDLER_EX(ID_FILE_OPEN, OnFileMenu)
        COMMAND_ID_HANDLER_EX(ID_FILE_SAVE, OnFileMenu)
        COMMAND_ID_HANDLER_EX(ID_FILE_SAVE_AS, OnFileMenu)
        COMMAND_ID_HANDLER_EX(ID_FILE_EXIT, OnFileMenu)

        COMMAND_ID_HANDLER_EX(ID_EDIT_UNDO, OnEditMenu)
        COMMAND_ID_HANDLER_EX(ID_EDIT_REDO, OnEditMenu)
        COMMAND_ID_HANDLER_EX(ID_EDIT_CUT, OnEditMenu)
        COMMAND_ID_HANDLER_EX(ID_EDIT_COPY, OnEditMenu)
        COMMAND_ID_HANDLER_EX(ID_EDIT_PASTE, OnEditMenu)
        
        COMMAND_ID_HANDLER_EX(ID_HELP_ABOUT, OnAboutMenu)
        
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)

        CHAIN_MSG_MAP(CUpdateUI<MainFrame>)
        CHAIN_MSG_MAP(CFrameWindowImpl<MainFrame>)
    END_MSG_MAP()

private:
    CodeView mCodeView;

public:
    LRESULT OnCreate(LPCREATESTRUCT cs) {
        const DWORD dwClientStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
        const DWORD dwClientExStyle = WS_EX_CLIENTEDGE;

        m_hWndClient = mCodeView.Create(m_hWnd, rcDefault, NULL, dwClientStyle, dwClientExStyle);
        
        return 0;
    }

    void OnDestroy() {
        SetMsgHandled(false);
        PostQuitMessage(0);
    }

    void OnFileMenu(UINT uCode, int nID, HWND hwndCtrl) {
        if (nID == ID_FILE_OPEN) {
            
        }

        if (nID == ID_FILE_SAVE_AS) {

            int x = 0;
        }


        if (nID == ID_FILE_EXIT) {
            DestroyWindow();
        }
    }

    void OnEditMenu(UINT uCode, int nID, HWND hwndCtrl) {
        int x = 0;
    }

    void OnAboutMenu(UINT uCode, int nID, HWND hwndCtrl) {
        if (nID == ID_HELP_ABOUT) {
            AboutDlg dlg;
            dlg.DoModal();
        }
    }
};


CAppModule _Module;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ::SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    ::AtlInitCommonControls(ICC_COOL_CLASSES | ICC_TREEVIEW_CLASSES | ICC_BAR_CLASSES);

    _Module.Init(NULL, hInstance);

    MainFrame mainFrame;
    MSG msg;

    if (NULL == mainFrame.CreateEx()) {
        return 1;
    }

    mainFrame.ShowWindow(nCmdShow);
    mainFrame.UpdateWindow();

    while (::GetMessage(&msg, NULL, 0, 0) > 0) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    _Module.Term();

    return static_cast<int>(msg.wParam);
}

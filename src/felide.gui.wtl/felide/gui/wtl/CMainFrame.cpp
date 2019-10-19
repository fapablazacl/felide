
#include "CMainFrame.hpp"

#include <felide/core/util/FileUtil.hpp>
#include <atldlgs.h>

namespace felide::view::win {
    int CMainFrame::OnFileNew(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CMainFrame::OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {
        CFileDialog dialog(TRUE, _T("All Files\0*.*"));

        if (dialog.DoModal() == IDOK) {
            CString filename = dialog.m_szFileName;

            auto content2 = FileUtil::load(dialog.m_szFileName).c_str();

            CString content = FileUtil::load((LPCSTR)filename).c_str();

            m_editor.SetText(content);
        }
        
        return 0;
    }

    int CMainFrame::OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CMainFrame::OnFileSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CMainFrame::OnFileClose(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CMainFrame::OnFileExit(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
        this->InitFrame();
        this->InitMenuBar();

        return 0;
    }

    void CMainFrame::InitFrame() {
        // set the main view
        RECT rcClient;
        this->GetClientRect(&rcClient);

        const DWORD dwStyle = WS_CHILD | WS_VISIBLE;

        m_editor.Create(m_hWnd, rcClient, "", dwStyle);
    }

    void CMainFrame::InitMenuBar() {
        // create the menu 
        m_menu.CreateMenu();

        // file menu
        CMenuHandle fileMenu;
        fileMenu.CreateMenu();
        fileMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_FILE_NEW, "New");
        fileMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_FILE_OPEN, "Open");
        fileMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_FILE_SAVE, "Save");
        fileMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_FILE_SAVE_AS, "Save As");
        fileMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_FILE_CLOSE, "Close");
        m_menu.AppendMenu(MF_STRING, fileMenu, "File");

        // edit menu
        CMenuHandle editMenu;
        editMenu.CreateMenu();
        editMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_EDIT_UNDO, "Undo");
        editMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_EDIT_REDO, "Redo");
        editMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_EDIT_CUT, "Cut");
        editMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_EDIT_COPY, "Copy");
        editMenu.AppendMenu(MF_STRING | MF_ENABLED, FID_EDIT_PASTE, "Paste");
        m_menu.AppendMenu(MF_STRING, editMenu, "Edit");

        this->SetMenu(m_menu);
    }

    void CMainFrame::OnClose() {
        DestroyWindow();
    }

    void CMainFrame::OnDestroy() {
        PostQuitMessage(0);
    }

    void CMainFrame::OnSize(UINT nType, CSize size) {
        m_editor.ResizeClient(size.cx, size.cy, TRUE);
    }
}

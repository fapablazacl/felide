
#include "CIdeMainFrame.hpp"

#include "../../../resource.h"

#include <felide/core/util/FileService.hpp>
#include <atldlgs.h>

namespace felide {
    int CIdeMainFrame::OnFileNew(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CIdeMainFrame::OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {
        CFileDialog dialog(TRUE, _T("All Files\0*.*"));

        if (dialog.DoModal() == IDOK) {
            auto fileService = FileService::create();

            CString filename = dialog.m_szFileName;

            auto content2 = fileService->load(dialog.m_szFileName).c_str();

            CString content = fileService->load((LPCSTR)filename).c_str();

            m_editor.SetText(content);
        }
        
        return 0;
    }

    int CIdeMainFrame::OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CIdeMainFrame::OnFileSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CIdeMainFrame::OnFileClose(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CIdeMainFrame::OnFileExit(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {

        return 0;
    }

    int CIdeMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
        imageList.Create(16, 16, ILC_COLOR24, 0, 1);

        this->SetupClassView();
        this->SetupMenuBar();

        return 0;
    }

    void CIdeMainFrame::SetupDocumentManager() {
        // set the main view
        RECT rcClient;
        this->GetClientRect(&rcClient);

        m_editor.Create(m_hWnd, rcClient, "", WS_CHILD | WS_VISIBLE);
    }

    void CIdeMainFrame::SetupClassView()
    {
        // setup image list 
        HBITMAP b1 = bitmap1.LoadBitmapA(IDB_BITMAP3);
        HBITMAP b2 = bitmap2.LoadBitmapA(IDB_BITMAP2);
        HBITMAP b3 = bitmap3.LoadBitmapA(IDB_BITMAP4);

        int image1 = imageList.Add(bitmap1);
        int image2 = imageList.Add(bitmap2);
        int image3 = imageList.Add(bitmap3);

        // set the main view
        RECT rcClient;
        this->GetClientRect(&rcClient);

        classView.Create(m_hWnd, rcClient, "", TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | WS_VISIBLE | WS_CHILD);
        classView.SetImageList(imageList, TVSIL_NORMAL);

        HTREEITEM rootItem = classView.InsertItem("namespace", 0, 0, nullptr, nullptr);
         
        TVINSERTSTRUCT insertStruct = {};

        insertStruct.hParent = rootItem;
        insertStruct.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
        insertStruct.item.pszText = "Class1";
        insertStruct.item.iImage = 1;
        insertStruct.item.iSelectedImage = 1;
        classView.InsertItem(&insertStruct);

        insertStruct.hParent = rootItem;
        insertStruct.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
        insertStruct.item.pszText = "Class2";
        insertStruct.item.iImage = 1;
        insertStruct.item.iSelectedImage = 1;
        classView.InsertItem(&insertStruct);

        insertStruct.hParent = rootItem;
        insertStruct.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
        insertStruct.item.pszText = "Function1";
        insertStruct.item.iImage = 2;
        insertStruct.item.iSelectedImage = 2;
        classView.InsertItem(&insertStruct);
    }

    void CIdeMainFrame::SetupMenuBar() {
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

    void CIdeMainFrame::OnClose() {
        DestroyWindow();
    }

    void CIdeMainFrame::OnDestroy() {
        PostQuitMessage(0);
    }

    void CIdeMainFrame::OnSize(UINT nType, CSize size) {
        // m_editor.ResizeClient(size.cx, size.cy, TRUE);
        classView.ResizeClient(size.cx, size.cy, TRUE);
    }
}

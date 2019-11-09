
#include "CIdeMainFrame.hpp"

#include "../../../resource.h"

#include <felide/core/util/FileService.hpp>
#include <felide/core/util/FolderService.hpp>
#include <felide/gui/folder-browser/FolderBrowserModel.hpp>
#include <felide/gui/document-manager/DocumentManagerModel.hpp>
#include <atldlgs.h>

#include "CFolderBrowser.hpp"

namespace felide {
    CIdeMainFrame::CIdeMainFrame(IDEFramePresenter *presenter) : IDEFrame(presenter) {
        folderService = FolderService::create();
        folderBrowserModel = FolderBrowserModel::create(folderService.get());
        documentManagerModel = DocumentManagerModel::create();

        folderBrowserPresenter = std::make_unique<FolderBrowserPresenter>(folderBrowserModel.get(), presenter);
        documentManagerPresenter = std::make_unique<DocumentManagerPresenter>(documentManagerModel.get());

        folderBrowser = std::make_unique<CFolderBrowser>(folderBrowserPresenter.get());
        dialogManager = std::make_unique<CDialogManager>();
        documentManager = std::make_unique<CIdeDocumentManager>(documentManagerPresenter.get());
    }


    CIdeMainFrame::~CIdeMainFrame() {

    }


    DocumentManager* CIdeMainFrame::getDocumentManager() {
        return documentManager.get();
    }


    DialogManager* CIdeMainFrame::getDialogManager() {
        return dialogManager.get();
    }
    

    FolderBrowser* CIdeMainFrame::getFolderBrowser() {
        return folderBrowser.get();
    }


    void CIdeMainFrame::close() {

    }

    void CIdeMainFrame::show() {

    }
}


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
        CRect clientRect;
        this->GetClientRect(&clientRect);

        splitterWindow.Create(m_hWnd, &clientRect, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

        this->SetupClassView();
        this->SetupDocumentManager();

        splitterWindow.SetSplitterPane(SPLIT_PANE_LEFT, folderBrowser->m_hWnd);
        splitterWindow.SetSplitterPane(SPLIT_PANE_RIGHT, m_editor);
        
        // set the vertical splitter parameters
        splitterWindow.m_cxyMin = 35; // minimum size
        splitterWindow.SetSplitterPos(85); // from left

        this->SetupMenuBar();

        return 0;
    }


    void CIdeMainFrame::SetupDocumentManager() {
        // set the main view
        RECT rcClient;
        splitterWindow.GetClientRect(&rcClient);

        m_editor.Create(splitterWindow, rcClient, "", WS_CHILD | WS_VISIBLE);
    }

    void CIdeMainFrame::SetupClassView() {
        RECT clientRect;
        splitterWindow.GetClientRect(&clientRect);
        
        folderBrowser->Create(splitterWindow, clientRect, "", WS_VISIBLE | WS_CHILD);
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
        splitterWindow.ResizeClient(size.cx, size.cy, TRUE);
    }
}


#pragma once 

#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atluser.h>
#include <atlcrack.h>

#include "CEditor.hpp"

namespace felide::view::win {
    
    class CMainFrame : public CWindowImpl<CMainFrame, CWindow, CFrameWinTraits> {
    public:
        enum {
            FID_FILE_NEW = 1000, 
            FID_FILE_OPEN,
            FID_FILE_SAVE,
            FID_FILE_SAVE_AS,
            FID_FILE_CLOSE,
            FID_FILE_EXIT, 

            FID_EDIT_UNDO = 2000,
            FID_EDIT_REDO,
            FID_EDIT_CUT,
            FID_EDIT_COPY,
            FID_EDIT_PASTE,

            FID_HELP_ABOUT = 3000,
        };

    public:
        DECLARE_WND_CLASS(_T("CMainFrame Class"))

        BEGIN_MSG_MAP(CMainFrame)
            COMMAND_ID_HANDLER(FID_FILE_NEW, OnFileNew)
            COMMAND_ID_HANDLER(FID_FILE_OPEN, OnFileOpen)
            COMMAND_ID_HANDLER(FID_FILE_SAVE, OnFileSave)
            COMMAND_ID_HANDLER(FID_FILE_SAVE_AS, OnFileSaveAs)
            COMMAND_ID_HANDLER(FID_FILE_CLOSE, OnFileClose)
            COMMAND_ID_HANDLER(FID_FILE_EXIT, OnFileExit)
            
            /*
            COMMAND_ID_HANDLER(FID_EDIT_UNDO, OnEditUndo)
            COMMAND_ID_HANDLER(FID_EDIT_REDO, OnEditRedo)
            COMMAND_ID_HANDLER(FID_EDIT_CUT, OnEditCut)
            COMMAND_ID_HANDLER(FID_EDIT_COPY, OnEditCopy)
            COMMAND_ID_HANDLER(FID_EDIT_PASTE, OnEditPaste)
            
            COMMAND_ID_HANDLER(FID_HELP_ABOUT, OnHelpAbout)
            */

            MSG_WM_CREATE(OnCreate)
            MSG_WM_CLOSE(OnClose)
            MSG_WM_DESTROY(OnDestroy)
            MSG_WM_SIZE(OnSize)
        END_MSG_MAP()

    public:
        int OnFileNew(WORD wNotifyCode  , WORD wID, HWND hWndCtrl, BOOL &bHandled);

        int OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled);

        int OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled);

        int OnFileSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled);

        int OnFileClose(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled);

        int OnFileExit(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled);

    public:
        int OnCreate(LPCREATESTRUCT lpCreateStruct);

        void OnClose();

        void OnDestroy();

        void OnSize(UINT nType, CSize size);

    private:
        void InitFrame();

        void InitMenuBar();

    private:
        CEditor m_editor;
        CMenu m_menu;
    };
}


#pragma once 

#include <map>

#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atluser.h>
#include <atlcrack.h>
#include <atlsplit.h>

#include <felide/gui/MenuPanel.hpp>
#include <felide/gui/ide-frame/IDEFrame.hpp>
#include <felide/gui/document-manager/DocumentManagerPresenter.hpp>
#include <felide/gui/folder-browser/FolderBrowserPresenter.hpp>
#include <felide/core/util/FolderService.hpp>

#include "CDocument.hpp"
#include "CDocumentManager.hpp"
#include "CFolderBrowser.hpp"
#include "CDialogManager.hpp"

namespace felide {
    
    class CIdeFrame : public CWindowImpl<CIdeFrame, CWindow, CFrameWinTraits>, public IDEFrame, public MenuPanel {
    public:
        CIdeFrame(IDEFramePresenter *presenter);

        virtual ~CIdeFrame();

        virtual DocumentManager* getDocumentManager() override;

        virtual DialogManager* getDialogManager() override;
        
        virtual FolderBrowser* getFolderBrowser() override;

        virtual void close() override;

        virtual void show() override;

    public:
        void fillMenuItem(CMenuHandle parent, const Menu &menu);

        std::string mapMenuTitle(const Menu& menu) const;

        virtual void setupMenuBar(const Menu &menu) override;

    public:
        DECLARE_WND_CLASS(_T("CIdeFrame Class"))

        BEGIN_MSG_MAP(CIdeFrame)
            COMMAND_CODE_HANDLER(0, OnCommand)

            MSG_WM_CREATE(OnCreate)
            MSG_WM_CLOSE(OnClose)
            MSG_WM_DESTROY(OnDestroy)
            MSG_WM_SIZE(OnSize)
        END_MSG_MAP()

    public:
        int OnCommand(WORD wNotifyCode  , WORD wID, HWND hWndCtrl, BOOL &bHandled);

        int OnCreate(LPCREATESTRUCT lpCreateStruct);

        void OnClose();

        void OnDestroy();

        void OnSize(UINT nType, CSize size);

    private:
        void SetupDocumentManager();

        void SetupClassView();

        void SetupMenuBar();

    private:
        CSplitterWindow splitterWindow;
        CDocument m_editor;
        CMenu menuBar;
        
        std::unique_ptr<FolderService> folderService;

        std::unique_ptr<FolderBrowserModel> folderBrowserModel;
        std::unique_ptr<DocumentManagerModel> documentManagerModel;

        std::unique_ptr<FolderBrowserPresenter> folderBrowserPresenter;
        std::unique_ptr<DocumentManagerPresenter> documentManagerPresenter;

        std::unique_ptr<CFolderBrowser> folderBrowser;
        std::unique_ptr<CDialogManager> dialogManager;
        std::unique_ptr<CDocumentManager> documentManager;

        std::map<int, std::function<void()>> commandMap;
    };
}

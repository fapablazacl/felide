
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

#include <Xenoide/Core/FolderService.hpp>
#include <Xenoide/Gui/MenuPanel.hpp>
#include <Xenoide/Gui/IDEFrame.hpp>

#include "CDocument.hpp"
#include "CDocumentManager.hpp"
#include "CFolderBrowser.hpp"
#include "CDialogManager.hpp"

namespace Xenoide {
    
    class CIdeFrame : public CWindowImpl<CIdeFrame, CWindow, CFrameWinTraits>, public IDEFrame, public MenuPanel {
    public:
        CIdeFrame(IDEFrame::Presenter *presenter);

        virtual ~CIdeFrame();

        virtual DocumentManager* getDocumentManager() override;

        virtual DialogManager* getDialogManager() override;
        
        virtual FolderBrowser* getFolderBrowser() override;

        virtual void close() override;

        virtual void show() override;

        virtual void showPanel(const Panel panel) override;

    public:
        void fillMenuItem(CMenuHandle parent, const Menu &menu);

        std::string mapMenuTitle(const Menu& menu) const;

        virtual void setupMenuBar(const Menu &menu) override;

    public:
        DECLARE_WND_CLASS(_T("CIdeFrame"))

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

        void SetupFolderBrowser();

        void SetupMenuBar();

    private:
        CSplitterWindow splitterWindow;
        CMenu menuBar;
        
        std::unique_ptr<FolderService> folderService;

        std::unique_ptr<FolderBrowser::Model> folderBrowserModel;
        std::unique_ptr<DocumentManager::Model> documentManagerModel;

        std::unique_ptr<FolderBrowser::Presenter> folderBrowserPresenter;
        std::unique_ptr<DocumentManager::Presenter> documentManagerPresenter;

        std::unique_ptr<CFolderBrowser> folderBrowser;
        std::unique_ptr<CDialogManager> dialogManager;
        std::unique_ptr<CDocumentManager> documentManager;

        std::map<int, std::function<void()>> commandMap;
    };
}

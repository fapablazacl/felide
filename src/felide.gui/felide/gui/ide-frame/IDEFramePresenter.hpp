
#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include <felide/core/Predef.hpp>
#include <felide/gui/DialogManager.hpp>
#include <felide/gui/document/Document.hpp>
#include <felide/gui/document/DocumentModel.hpp>
#include <felide/gui/document-manager/DocumentManager.hpp>
#include <felide/gui/document-manager/DocumentManagerPresenter.hpp>
#include <felide/gui/folder-browser/FolderBrowser.hpp>

#include "IDEFrameModel.hpp"

#include <map>
#include <memory>

namespace felide {
    class FELIDE_API DocumentModel;
    class FELIDE_API Document;
    class FELIDE_API IDEFrame;
    class FELIDE_API DialogManager;
    class FELIDE_API MenuPanel;
    
    class FELIDE_API IDEFramePresenter {
    public:
        IDEFramePresenter(IDEFrameModel *model);

        virtual ~IDEFramePresenter();

        void onInitialized(IDEFrame *view, DialogManager *dialogView, MenuPanel *menuView);

    public:
        void onFileNew();

        void onFileOpen();
        
        void onFileOpen(const std::string &fileName);

        void onFileOpenFolder();

        void onFileSave();

        void onFileSaveAs();

        void onFileSaveAll();

        void onFileClose();

        void onFileExit();

        void onEditUndo();

        void onEditRedo();

        void onEditCut();

        void onEditCopy();

        void onEditPaste();

        void onViewFolderBrowser();

        void onToolsFileSearch();

        bool onCloseRequested();

    public:
        DocumentManagerPresenter* getDocumentManagerPresenter();

        FolderBrowserPresenter* getFolderBrowserPresenter();

        // TODO: Make it private (used in Main.cpp)
        void openFolder(const std::string &fullPath);

    private:
        DialogManager *dialogView = nullptr;
        MenuPanel *menuView = nullptr;
        IDEFrame *view = nullptr;
        IDEFrameModel *model = nullptr;
        
        std::unique_ptr<DocumentManagerPresenter> documentManagerPresenter;
        std::unique_ptr<FolderBrowserPresenter> folderBrowserPresenter;
    };
}

#endif

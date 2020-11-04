
#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include <felide/core/Predef.hpp>
#include <felide/gui/DialogManager.hpp>
#include <felide/gui/Document.hpp>
#include <felide/gui/DocumentModel.hpp>
#include <felide/gui/DocumentManager.hpp>
#include <felide/gui/DocumentManagerPresenter.hpp>
#include <felide/gui/FolderBrowser.hpp>

#include "IDEFrameModel.hpp"

#include <map>
#include <memory>

namespace felide {
    class DocumentModel;
    class Document;
    class IDEFrame;
    class DialogManager;
    class MenuPanel;
    
    class IDEFramePresenter {
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

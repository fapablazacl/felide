
#ifndef __XENOIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __XENOIDE_UI_MAINWINDOWPRESENTER_HPP__

#include <Xenoide/Core/Predef.hpp>
#include <Xenoide/GUI/DialogManager.hpp>
#include <Xenoide/GUI/Document.hpp>
#include <Xenoide/GUI/DocumentModel.hpp>
#include <Xenoide/GUI/DocumentManager.hpp>
#include <Xenoide/GUI/DocumentManagerPresenter.hpp>
#include <Xenoide/GUI/FolderBrowser.hpp>

#include "IDEFrameModel.hpp"

#include <map>
#include <memory>

namespace Xenoide {
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


#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include <felide/Predef.hpp>
#include <felide/ui/DialogManager.hpp>
#include <felide/ui/document/Document.hpp>
#include <felide/ui/document/DocumentModel.hpp>
#include <felide/ui/document-manager/DocumentManager.hpp>
#include <felide/ui/folder-browser/FolderBrowser.hpp>

#include "IDEFrameModel.hpp"

#include <map>
#include <memory>

namespace felide {
    class FELIDE_API DocumentModel;
    class FELIDE_API Document;
    class FELIDE_API IDEFrame;
    
    class FELIDE_API IDEFramePresenter {
    public:
        IDEFramePresenter();

        virtual ~IDEFramePresenter();

        void attachView(IDEFrame *view);

        void detachView();

    public:
        void onFileNew();

        void onFileOpen();
        
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

        void onDocumentContentModified(Document *view);
        
        void onDocumentCloseRequested(Document *view);
        
        void onDocumentShow(const std::string &fileName);

        void onViewFolderBrowser();

        bool onCloseRequested();

    public:
        // TODO: Make it private (used in Main.cpp)
        void openFolder(const std::string &fullPath);

    private:
        void editorSave(Document *view, DocumentModel *editorModel);
        
        void editorSaveAs(Document *view);
        
        DocumentModel* createDocumentModel(const Document *view, const int tag);

        DocumentModel* createDocumentModel(const Document *view, const std::string &fileName);

        DocumentModel* getDocumentModel(const Document *view);
        
        Document* getDocument(const DocumentModel *model);

    private:
        IDEFrame *view = nullptr;
        IDEFrameModel model;

        std::map<const Document*, std::unique_ptr<DocumentModel>> editorModels;
    };
}

#endif

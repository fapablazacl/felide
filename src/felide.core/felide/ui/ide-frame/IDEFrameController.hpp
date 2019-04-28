
#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include <felide/Predef.hpp>
#include <felide/ui/DialogManager.hpp>
#include <felide/ui/editor/Editor.hpp>
#include <felide/ui/editor/EditorModel.hpp>
#include <felide/ui/editor-manager/EditorManager.hpp>
#include <felide/ui/folder-browser/FolderBrowser.hpp>

#include "IDEFrameModel.hpp"

#include <map>
#include <memory>

namespace felide {
    class FELIDE_API EditorModel;
    class FELIDE_API Editor;
    class FELIDE_API IDEFrame;
    
    class FELIDE_API IDEFrameController {
    public:
        IDEFrameController();

        virtual ~IDEFrameController();

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

        void onEditorContentModified(Editor *view);
        
        void onEditorCloseRequested(Editor *view);
        
        void onEditorShow(const std::string &fileName);

        void onViewFolderBrowser();

        bool onCloseRequested();

    public:
        // TODO: Make it private (used in Main.cpp)
        void openFolder(const std::string &fullPath);

    private:
        void editorSave(Editor *view, EditorModel *editorModel);
        
        void editorSaveAs(Editor *view);
        
        EditorModel* createEditorModel(const Editor *view, const int tag);

        EditorModel* createEditorModel(const Editor *view, const std::string &fileName);

        EditorModel* getEditorModel(const Editor *view);
        
        Editor* getEditor(const EditorModel *model);

    private:
        IDEFrame *view = nullptr;
        IDEFrameModel model;

        std::map<const Editor*, std::unique_ptr<EditorModel>> editorModels;
    };
}

#endif

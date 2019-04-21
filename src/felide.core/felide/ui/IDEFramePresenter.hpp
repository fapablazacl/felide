
#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include <felide/Predef.hpp>

#include "IDEFrameModel.hpp"
#include "Editor.hpp"
#include "EditorModel.hpp"
#include "EditorManager.hpp"
#include "DialogManager.hpp"
#include "FolderBrowser.hpp"
#include <map>
#include <memory>

namespace felide {
    class FELIDE_API EditorModel;
    class FELIDE_API Editor;
    class FELIDE_API IDEFrame;
    
    class FELIDE_API IDEFramePresenter {
    public:
        IDEFramePresenter();

        virtual ~IDEFramePresenter();

        void attachView(IDEFrame *view);

        void detachView();

    public:
        void fileNewTriggered();

        void fileOpenTriggered();
        
        void fileOpenFolderTriggered();

        void fileSaveTriggered();

        void fileSaveAsTriggered();

        void fileSaveAllTriggered();

        void fileCloseTriggered();

        void fileExitTriggered();

        void editUndo();

        void editRedo();

        void editCut();

        void editCopy();

        void editPaste();

        void editorContentModified(Editor *view);
        
        void editorCloseRequested(Editor *view);
        
        void editorShow(const std::string &fileName);

        void viewFolderBrowserToggle();

        bool closeRequested();

    public:
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

        EditorManager *editorManager = nullptr;
        DialogManager *dialogManager = nullptr;
        
        std::map<const Editor*, std::unique_ptr<EditorModel>> editorModels;
    };
}

#endif

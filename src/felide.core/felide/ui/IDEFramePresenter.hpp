
#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include <felide/Predef.hpp>

#include "IDEFrameModel.hpp"

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

        bool closeRequested();
        
    private:
        void editorSave(Editor *view, EditorModel *editorModel);
        
        void editorSaveAs(Editor *view);
        
        EditorModel* createEditorModel(const Editor *view, const int tag);

        EditorModel* createEditorModel(const Editor *view, const std::string &fileName);

        EditorModel* getEditorModel(const Editor *view);
        
        Editor* getEditor(const EditorModel *model);

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif

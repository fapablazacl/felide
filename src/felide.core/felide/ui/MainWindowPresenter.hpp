
#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include "MainWindowModel.hpp"
#include "EditorModel.hpp"

#include <felide/Predef.hpp>

#include <map>
#include <memory>

namespace felide {
    class FELIDE_API EditorModel;
    class FELIDE_API EditorView;
    class FELIDE_API MainWindowView;

    class FELIDE_API MainWindowPresenter {
    public:
        MainWindowPresenter();

        virtual ~MainWindowPresenter();

        void attachView(MainWindowView *view);

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

        void editorContentModified(EditorView *editorView);
        
        void editorCloseRequested(EditorView *editorView);
        
        void editorShow(const std::string &fileName);

        bool closeRequested();
        
    private:
        void editorSave(EditorView *editorView, EditorModel *editorModel);
        
        void editorSaveAs(EditorView *editorView);
        
        EditorModel* createEditorModel(const EditorView *view, const int tag);

        EditorModel* createEditorModel(const EditorView *view, const std::string &fileName);

        EditorModel* getEditorModel(const EditorView *view);
        
        EditorView* getEditorView(const EditorModel *model);

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif

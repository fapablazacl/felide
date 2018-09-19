
#ifndef __FELIDE_UI_MAINWINDOWPRESENTER_HPP__
#define __FELIDE_UI_MAINWINDOWPRESENTER_HPP__

#include "MainWindowModel.hpp"
#include "EditorModel.hpp"

#include <map>
#include <memory>

namespace felide {
    class EditorModel;
    class EditorView;
    class MainWindowView;
    class EditorManagerView;
    class DialogManagerView;
    class MainWindowPresenter {
    public:
        MainWindowPresenter();

        void attachView(MainWindowView *view);

        void detachView();

        virtual ~MainWindowPresenter();

    public:
        void fileNewTriggered();

        void fileOpenTriggered();
        
        void fileOpenFolderTriggered();

        void fileSaveTriggered();

        void fileSaveAsTriggered();

        void fileSaveAllTriggered();

        void fileCloseTriggered();

        void fileExitTriggered();

        void editorContentModified(EditorView *editorView);
        
        void editorCloseRequested(EditorView *editorView);
        
        bool closeRequested();
        
    private:
        void editorSave(EditorView *editorView, EditorModel *editorModel);
        
        void editorSaveAs(EditorView *editorView);
        
        EditorModel* createEditorModel(const EditorView *view, const int tag);

        EditorModel* createEditorModel(const EditorView *view, const std::string &fileName);

        EditorModel* getEditorModel(const EditorView *view);
        
        EditorView* getEditorView(const EditorModel *model);

    private:
        MainWindowView *m_view = nullptr;
        EditorManagerView *m_editorManager = nullptr;
        DialogManagerView *m_dialogManager = nullptr;

        MainWindowModel m_model;

        std::map<const EditorView*, std::unique_ptr<EditorModel>> m_editorViewModels;
    };
}

#endif

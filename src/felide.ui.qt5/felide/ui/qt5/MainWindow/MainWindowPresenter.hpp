
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
    class MainWindowPresenter {
    public:
        MainWindowPresenter();

        void attachView(MainWindowView *view);

        void detachView();

        virtual ~MainWindowPresenter();

    public:
        void fileNew();

        void fileOpen();

        void fileSave();

        void fileSaveAs();

        void fileSaveAll();

        void fileClose();

        void fileExit();

        void editorContentModified(EditorView *editorView);
        
        void editorCloseRequested(EditorView *editorView);
        
        void editorSave(EditorView *editorView);
        
        void editorSaveAs(EditorView *editorView);
        
    private:
        void handleSaveAs(EditorView *editorView);
        
        void saveFile(EditorView *editorView, EditorModel *editorModel);

        EditorModel* createEditorModel(const EditorView *view, const int tag);

        EditorModel* createEditorModel(const EditorView *view, const std::string &fileName);

        EditorModel* getEditorModel(const EditorView *view);
        
        EditorView* getEditorView(const EditorModel *model);

    private:
        MainWindowView *m_view = nullptr;
        EditorManagerView *m_editorManager = nullptr;

        MainWindowModel m_model;

        std::map<const EditorView*, std::unique_ptr<EditorModel>> m_editorViewModels;
    };
} 

#endif

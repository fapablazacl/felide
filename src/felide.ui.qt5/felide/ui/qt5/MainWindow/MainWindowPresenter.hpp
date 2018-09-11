
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
    class MainWindowPresenter {
    public:
        MainWindowPresenter();

        void attachView(MainWindowView *view);

        void detachView();

        ~MainWindowPresenter();

    public:
        void fileNew();

        void fileOpen();

        void fileSave();

        void fileSaveAs();

        void fileSaveAll();

        void fileClose();

        void fileExit();

        void editorContentModified(EditorView *editorView);

    private:
        EditorModel* createEditorModel(const EditorView *view, const int tag);

        EditorModel* createEditorModel(const EditorView *view, const std::string &fileName);

    private:
        MainWindowView *m_view = nullptr;
        MainWindowModel m_model;

        std::map<const EditorView*, std::unique_ptr<EditorModel>> editorViewModels;
    };
} 

#endif

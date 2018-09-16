
#ifndef __FELIDE_UI_EDITORMANAGERVIEW_HPP__
#define __FELIDE_UI_EDITORMANAGERVIEW_HPP__

#include <cstddef>

namespace felide {
    class EditorView;
    class EditorManagerView {
    public:
        virtual ~EditorManagerView();

        virtual EditorView* appendEditor() = 0;

        virtual EditorView* getCurrentEditor() = 0;

        virtual std::size_t getEditorCount() const = 0;

        virtual EditorView* getEditor(const std::size_t index) = 0;
        
        virtual void closeEditor(EditorView *editorView) = 0;
    };
} 

#endif

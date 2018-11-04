
#ifndef __FELIDE_UI_EDITORMANAGERVIEW_HPP__
#define __FELIDE_UI_EDITORMANAGERVIEW_HPP__

#include <cstddef>
#include <felide/Predef.hpp>
#include <vector>

namespace felide {
    class FELIDE_API Editor;
    class FELIDE_API EditorManager {
    public:
        virtual ~EditorManager();

        virtual Editor* appendEditor() = 0;

        virtual Editor* getCurrentEditor() = 0;

        virtual std::size_t getEditorCount() const = 0;

        virtual Editor* getEditor(const std::size_t index) = 0;
        
        virtual void closeEditor(Editor *editor) = 0;

        virtual void showEditor(Editor *editor) = 0;

        std::vector<Editor*> getEditors();
    };
} 

#endif

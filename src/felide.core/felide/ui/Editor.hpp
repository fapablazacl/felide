
#ifndef __FELIDE_UI_EDITORVIEW_HPP_
#define __FELIDE_UI_EDITORVIEW_HPP_

#include <string>
#include <felide/Predef.hpp>

namespace felide {
    struct EditorConfig {
        std::string fontName;
        int fontSize;
        int tabWidth;
        bool caretLineVisible;
        bool showLineNumbers;

        static EditorConfig Default();
    };

    class FELIDE_API Editor {
    public:
        virtual ~Editor();

        virtual void setTitle(const std::string &title) = 0;
        virtual std::string getTitle() const = 0;

        virtual void setContent(const std::string &content) = 0;
        virtual std::string getContent() const = 0;

        virtual void setConfig(const EditorConfig &config) = 0;
        virtual EditorConfig getConfig() const = 0;

        virtual void clearAll() = 0;

        virtual void clearUndoBuffer() = 0;

        virtual void undo() = 0;
        virtual void redo() = 0;

        virtual void cut() = 0;
        virtual void copy() = 0;
        virtual void paste() = 0;
    };    
}

#endif

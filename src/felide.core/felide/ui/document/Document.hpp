
#ifndef __FELIDE_UI_DOCUMENT_HPP__
#define __FELIDE_UI_DOCUMENT_HPP__

#include <string>
#include <felide/Predef.hpp>

namespace felide {
    struct DocumentConfig {
        std::string fontName;
        int fontSize;
        int tabWidth;
        bool caretLineVisible;
        bool showLineNumbers;

        static DocumentConfig Default();
    };

    class FELIDE_API Document {
    public:
        virtual ~Document();

        virtual void setTitle(const std::string &title) = 0;
        virtual std::string getTitle() const = 0;

        virtual void setContent(const std::string &content) = 0;
        virtual std::string getContent() const = 0;

        virtual void setConfig(const DocumentConfig &config) = 0;
        virtual DocumentConfig getConfig() const = 0;

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

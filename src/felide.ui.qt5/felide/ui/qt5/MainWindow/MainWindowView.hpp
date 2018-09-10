
#ifndef __FELIDE_UI_MAINWINDOWVIEW_HPP__
#define __FELIDE_UI_MAINWINDOWVIEW_HPP__

#include <string>
#include <boost/optional.hpp>
#include <vector>
#include <map>

namespace felide {
    enum class DialogType {
        OpenFile,
        SaveFile
    };

    struct DialogViewData {
        struct FileFilter {
            std::string description;
            std::vector<std::string> wildcards;
        };

        DialogType dialogType;
        std::string title;
        std::vector<FileFilter> filters;
    };

    struct EditorConfig {
        std::string fontName;
        int fontSize;
        int tabWidth;
        bool caretLineVisible;

        static EditorConfig Default() {
            return {
                "Inconsolata", 10, 4, true
            };
        }
    };

    class EditorView {
    public:
        virtual ~EditorView() {}

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

    class EditorManagerView {
    public:
        virtual ~EditorManagerView() {}

        virtual EditorView* appendEditor() = 0;

        virtual EditorView* getCurrentEditor() = 0;

        virtual std::size_t getEditorCount() const = 0;

        virtual EditorView* getEditor(const std::size_t index) = 0;
    };

    class MainWindowView {
    public:
        virtual ~MainWindowView();

        virtual boost::optional<std::string> showDialogModal(const DialogViewData &dialogViewData) = 0;

        virtual EditorManagerView* getEditorManagerView() = 0;
    };
}

#endif

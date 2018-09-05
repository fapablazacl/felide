
#ifndef __FELIDE_UI_MAINWINDOWVIEW_HPP__
#define __FELIDE_UI_MAINWINDOWVIEW_HPP__

#include <string>
#include <optional>
#include <vector>
#include <map>

namespace felide {
    struct FileDialogViewData {
        struct FileFilter {
            std::string description;
            std::vector<std::string> wildcards;
        };

        std::string title;
        std::vector<FileFilter> filters;
    };

    struct EditorConfig {
        std::string fontName = "Inconsolata";
        int fontSize = 10;
        int tabWidth = 4;
        bool caretLineVisible = true;
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

    class MainWindowView {
    public:
        virtual ~MainWindowView();

        virtual std::optional<std::string> openFileDialog(const FileDialogViewData &fileDialogData) = 0;

        virtual std::optional<std::string> saveFileDialog(const FileDialogViewData &fileDialogData) = 0;

        virtual EditorView* appendEditor() = 0;

        virtual void removeEditor(const std::string &fileKey) = 0;

        virtual std::map<std::string, EditorView*> getEditor(const std::string &fileKey) = 0;

        virtual EditorView* getCurrentEditor() = 0;
    };
}

#endif

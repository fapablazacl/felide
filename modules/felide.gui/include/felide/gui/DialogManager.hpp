
#ifndef __FELIDE_UI_DIALOGMANAGER_HPP__
#define __FELIDE_UI_DIALOGMANAGER_HPP__

#include <string>
#include <vector>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include <felide/gui/FileFilter.hpp>
#include <felide/core/Predef.hpp>

namespace felide {
    enum class FileDialogType {
        OpenFile,
        SaveFile
    };

    struct FileDialogData {
        std::string title;
        FileDialogType type;
        std::vector<FileFilter> filters;
        boost::filesystem::path defaultPath;
    };

    struct FolderDialogData {
        std::string title;
        boost::filesystem::path defaultPath;
    };

    enum class DialogIcon {
        Information,
        Warning,
        Error,
        Question
    };

    enum class DialogButton {
        Ok = 1,
        Cancel = 2,
        Yes = 4,
        No = 8,
        OkCancel = Ok | Cancel,
        YesNoCancel = Yes | No | Cancel,
        YesNo = Yes | No
    };

    inline DialogButton operator| (const DialogButton f1, const DialogButton f2) {
        return static_cast<DialogButton>(static_cast<int>(f1) | static_cast<int>(f2));
    }

    inline bool operator& (const DialogButton f1, const DialogButton f2) {
        if (f1 & f2) {
            return true;
        }

        return false;
    }

    struct MessageDialogData {
        std::string title;
        std::string message;
        DialogIcon icon;
        DialogButton buttons;
    };

    struct InputDialogData {
        std::string title;
        std::string label;
        std::string defaultText;
    };

    struct FileSearchDialogData {
        std::string title;
        boost::filesystem::path defaultPath;
    };

    class DialogManager {
    public:
        virtual ~DialogManager();
        virtual DialogButton showMessageDialog(const MessageDialogData &data) const = 0;
        virtual boost::optional<std::string> showInputDialog(const InputDialogData &data) const = 0;
        virtual boost::optional<boost::filesystem::path> showFileDialog(const FileDialogData &data) const = 0;
        virtual boost::optional<boost::filesystem::path> showFolderDialog(const FolderDialogData &data) = 0;
        virtual boost::optional<boost::filesystem::path> showFileSearchDialog(const FileSearchDialogData &data) const = 0;
    };
}

#endif


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

    class EditorManagerView;
    class MainWindowView {
    public:
        virtual ~MainWindowView();

        virtual boost::optional<std::string> showDialogModal(const DialogViewData &dialogViewData) = 0;
        
        virtual boost::optional<bool> showAskModal(const std::string &title, const std::string &message) = 0;

        virtual EditorManagerView* getEditorManagerView() = 0;
    };
}

#endif

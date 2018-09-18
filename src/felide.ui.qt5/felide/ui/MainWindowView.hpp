
#ifndef __FELIDE_UI_MAINWINDOWVIEW_HPP__
#define __FELIDE_UI_MAINWINDOWVIEW_HPP__

#include <string>
#include <boost/optional.hpp>
#include <vector>
#include <map>

namespace felide {
    class EditorManagerView;
    class DialogManagerView;
    class MainWindowView {
    public:
        virtual ~MainWindowView();

        virtual boost::optional<std::string> showDialogModal(const DialogViewData &dialogViewData) = 0;
        
        virtual boost::optional<bool> showAskModal(const std::string &title, const std::string &message) = 0;

        virtual EditorManagerView* getEditorManagerView() = 0;

        virtual DialogManagerView* getDialogManagerView() = 0;
    };
}

#endif

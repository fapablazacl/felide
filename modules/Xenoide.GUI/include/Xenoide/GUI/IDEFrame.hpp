
#ifndef __XENOIDE_UI_MAINWINDOWVIEW_HPP__
#define __XENOIDE_UI_MAINWINDOWVIEW_HPP__

#include <Xenoide/Core/Predef.hpp>
#include <Xenoide/GUI/FileFilter.hpp>
#include <boost/optional/optional.hpp>
#include <boost/filesystem/path.hpp>

namespace Xenoide {
    class DocumentManager;
    class DialogManager;
    class FolderBrowser;

    class IDEFramePresenter;

    class IDEFrame {
    public:
        enum Panel {
            FOLDER_BROWSER
        };

    public:
        explicit IDEFrame(IDEFramePresenter *presenter);

        virtual ~IDEFrame();

        virtual DocumentManager* getDocumentManager() = 0;

        virtual DialogManager* getDialogManager() = 0;
        
        virtual FolderBrowser* getFolderBrowser() = 0;

        virtual void close() = 0;

        virtual void show() = 0;

        virtual void showPanel(const Panel panel) = 0;

    protected:
        IDEFramePresenter *mPresenter;
    };
}

#endif

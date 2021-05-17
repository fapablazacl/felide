
#ifndef __XENOIDE_UI_FOLDERBROWSERCONTROLLER_HPP_
#define __XENOIDE_UI_FOLDERBROWSERCONTROLLER_HPP_

#include <string>
#include <Xenoide/Core/Predef.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/optional/optional_fwd.hpp>

namespace Xenoide {
    struct Point;

    class IDEModel;
    class FolderBrowser;
    class DialogManager;
    class IDEFramePresenter;

    class FolderBrowserModel;

    class FolderBrowserPresenter {
    public:
        FolderBrowserPresenter(FolderBrowserModel *model, IDEFramePresenter *ideFramePresenter);

        void onInitialized(FolderBrowser *folderBrowser, DialogManager *dialogManager);

        virtual ~FolderBrowserPresenter();

        virtual void onBrowseFolder();

        virtual void onCreateFile();

        virtual void onCreateFolder();

        virtual void onMoveSelectedPath(const std::string &targetFolder);

        virtual void onRenameSelectedPath();

        virtual void onOpenSelectedFile();

        virtual void onDeleteSelectedPath();
        
        virtual void onDisplayFolder(const boost::filesystem::path &folderPath);

        virtual void onContextMenuRequested(const Point &point);

    private:
        boost::optional<std::string> askValidPath(const std::string &title, const std::string &prompt, const std::string &promptForInvalidInput, const std::string &defaultValue);

    private:
        DialogManager *dialogView;
        FolderBrowser *view;
        FolderBrowserModel *model;
        IDEFramePresenter *ideFramePresenter;
    };
} 

#endif

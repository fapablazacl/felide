
#ifndef __FELIDE_UI_MAINWINDOWVIEW_HPP__
#define __FELIDE_UI_MAINWINDOWVIEW_HPP__

#include <felide/Predef.hpp>
#include <felide/ui/FileFilter.hpp>
#include <boost/optional/optional.hpp>
#include <boost/filesystem/path.hpp>

namespace felide {
    class FELIDE_API DocumentManager;
    class FELIDE_API DialogManager;
    class FELIDE_API FolderBrowser;

    class FELIDE_API IDEFramePresenter;

    struct Menu;

    class FELIDE_API IDEFrame {
    public:
        struct FileOperationViewData {
            std::string title;
            std::vector<FileFilter> filters;
            boost::optional<boost::filesystem::path> defaultFilePath;
        };

        struct FolderOpenViewData {
            std::string title;
            boost::optional<boost::filesystem::path> defaultDirectoryPath;
        };

    public:
        explicit IDEFrame(IDEFramePresenter *presenter);

        virtual ~IDEFrame();

        [[deprecated]]
        virtual DocumentManager* getDocumentManager() = 0;

        [[deprecated]]
        virtual DialogManager* getDialogManager() = 0;
        
        [[deprecated]]
        virtual FolderBrowser* getFolderBrowser() = 0;

        virtual boost::optional<boost::filesystem::path> showFileOpenDialog(const FileOperationViewData &viewData) const = 0;

        virtual boost::optional<boost::filesystem::path> showFileSaveDialog(const FileOperationViewData &viewData) const = 0;

        virtual boost::optional<boost::filesystem::path> showFolderOpenDialog(const FolderOpenViewData &viewData) const = 0;

        virtual void close() = 0;

        virtual void show() = 0;

    protected:
        IDEFramePresenter *m_presenter;
        Menu *m_menu;
    };
}

#endif

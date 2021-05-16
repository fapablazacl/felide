
#ifndef __XENOIDE_UI_FILESEARCHDIALOG_HPP__
#define __XENOIDE_UI_FILESEARCHDIALOG_HPP__

#include <string>
#include <vector>

namespace Xenoide {
    class FileSearchDialogPresenter;
    class FileSearchDialog {
    public:
        struct FileViewData {
            //! File to be shown to the User
            std::string fileTitle;
            
            //! Parent folder
            std::string fileFolder;

            //! Full file path
            std::string filePath;
        };

    public:
        explicit FileSearchDialog(FileSearchDialogPresenter *presenter);

        virtual ~FileSearchDialog();

        virtual void clearFileList() = 0;

        virtual void displayFileList(const std::vector<FileViewData> &files) = 0;

        virtual void hide() = 0;
        
    protected:
        FileSearchDialogPresenter *presenter = nullptr;
    };
}

#endif

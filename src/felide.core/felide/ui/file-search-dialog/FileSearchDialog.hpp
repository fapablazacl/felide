
#ifndef __FELIDE_UI_FILESEARCHDIALOG_HPP__
#define __FELIDE_UI_FILESEARCHDIALOG_HPP__

#include <string>
#include <vector>

namespace felide {
    class FileSearchDialogPresenter;
    class FileSearchDialog {
    public:
        explicit FileSearchDialog(FileSearchDialogPresenter *presenter);

        virtual ~FileSearchDialog();

        virtual void displayFileList(const std::vector<std::string> &files) = 0;

        virtual void hide() = 0;
        
    private:
        FileSearchDialogPresenter *presenter;
    };
}

#endif

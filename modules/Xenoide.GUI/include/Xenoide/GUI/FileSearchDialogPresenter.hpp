
#ifndef __XENOIDE_UI_FILESEARCHDIALOGPRESENTER_HPP__
#define __XENOIDE_UI_FILESEARCHDIALOGPRESENTER_HPP__

#include <string>
#include <Xenoide/Core/Predef.hpp>

namespace felide {
    class FileSearchDialog;
    class FileSearchDialogModel;
    class FileSearchDialogPresenter {
    public:
        FileSearchDialogPresenter(FileSearchDialogModel *model);

        void onInitialized(FileSearchDialog *view);

        void onAccepted(const std::string &filePath);

        void onCancelled();

        void onFilenameFilterRequested(const std::string &fileNamePart);

    private:
        FileSearchDialogModel *model = nullptr;
        FileSearchDialog *view = nullptr;
    };
}

#endif

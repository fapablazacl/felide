
#ifndef __FELIDE_UI_FILESEARCHDIALOGPRESENTER_HPP__
#define __FELIDE_UI_FILESEARCHDIALOGPRESENTER_HPP__

#include <string>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API FileSearchDialog;
    class FELIDE_API FileSearchDialogModel;
    class FELIDE_API FileSearchDialogPresenter {
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

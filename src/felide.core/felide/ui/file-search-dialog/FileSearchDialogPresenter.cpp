
#include "FileSearchDialogPresenter.hpp"
#include "FileSearchDialog.hpp"

namespace felide {
    FileSearchDialogPresenter::FileSearchDialogPresenter(FileSearchDialogModel *model) {
        this->model = model;
    }

    void FileSearchDialogPresenter::onInitialized(FileSearchDialog *view) {
        this->view = view;
    }

    void FileSearchDialogPresenter::onAccepted(const std::string &filePath) {
        view->hide();
    }

    void FileSearchDialogPresenter::onCancelled() {
        view->hide();
    }

    void FileSearchDialogPresenter::onFilenameFilterRequested(const std::string &fileNamePart) {
        if (fileNamePart.size() < 3) {
            return;
        }

        const std::vector<std::string> files = {
            "1", "1", "1"
        };

        view->displayFileList(files);
    }
}

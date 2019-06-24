
#include "FileSearchDialogPresenter.hpp"
#include "FileSearchDialog.hpp"
#include "FileSearchDialogModel.hpp"

#include <cassert>

namespace felide {
    FileSearchDialogPresenter::FileSearchDialogPresenter(FileSearchDialogModel *model) {
        this->model = model;
    }

    void FileSearchDialogPresenter::onInitialized(FileSearchDialog *view) {
        this->view = view;
        this->model->scanFolder();
    }

    void FileSearchDialogPresenter::onAccepted(const std::string &filePath) {
        assert(view);

        view->hide();
    }

    void FileSearchDialogPresenter::onCancelled() {
        assert(view);

        view->hide();
    }

    void FileSearchDialogPresenter::onFilenameFilterRequested(const std::string &filePattern) {
        assert(view);

        const std::vector<boost::filesystem::path> files = model->searchFilePattern(filePattern);

        std::vector<FileSearchDialog::FileViewData> fileList;

        for (const auto &file : files) {
			FileSearchDialog::FileViewData fileViewData;

			fileViewData.fileTitle = file.filename().string();
			fileViewData.fileFolder = file.parent_path().string();
			fileViewData.filePath = file.string();

            fileList.push_back(fileViewData);
        }

        view->displayFileList(fileList);
    }
}

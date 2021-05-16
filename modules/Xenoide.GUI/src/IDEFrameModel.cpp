
#include <Xenoide/GUI/IDEFrameModel.hpp>

#include <iostream>
#include <Xenoide/GUI/DocumentManagerModel.hpp>
#include <Xenoide/GUI/FolderBrowserModel.hpp>
#include <Xenoide/Core/FolderService.hpp>

namespace Xenoide {
    class IDEFrameModelImpl : public IDEFrameModel {
    public:
        IDEFrameModelImpl() {
            this->folderService = FolderService::create();

            this->documentManagerModel = DocumentManagerModel::create();
            this->folderBrowserModel = FolderBrowserModel::create(this->folderService.get());
        }

        virtual std::vector<FileFilter> getFileFilters() const override {
            return {
                {"All Files", {"*.*"}},
                {"C/C++ Files", {"*.hpp", "*.cpp", "*.hh", "*.cc", "*.h", "*.c"}},
            };
        }

        virtual DocumentManagerModel *getDocumentManagerModel() override {
            return documentManagerModel.get();
        }

        virtual FolderBrowserModel *getFolderBrowserModel() override {
            return folderBrowserModel.get();
        }

        virtual boost::optional<boost::filesystem::path> getWorkspaceFolder() const override {
            return this->workspaceFolder;
        }

        virtual void setWorkspaceFolder(boost::filesystem::path workspaceFolder) override {
            std::cout << "setWorkspaceFolder(" << workspaceFolder.string() << ")" << std::endl;
            this->workspaceFolder = workspaceFolder;
        }

    private:
        std::unique_ptr<FolderService> folderService;
        std::unique_ptr<DocumentManagerModel> documentManagerModel;
        std::unique_ptr<FolderBrowserModel> folderBrowserModel;
        boost::optional<boost::filesystem::path> workspaceFolder;
    };
}

namespace Xenoide {
    IDEFrameModel::~IDEFrameModel() {}

    std::unique_ptr<IDEFrameModel> IDEFrameModel::create() {
        return std::make_unique<IDEFrameModelImpl>();
    }
}

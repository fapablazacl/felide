
#include <Xenoide/Gui/FolderBrowserModel.hpp>

#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <Xenoide/Core/FolderService.hpp>

namespace Xenoide {
    class FolderBrowserModelImpl : public FolderBrowserModel {
    public:
        FolderBrowserModelImpl(FolderService *folderService) {
            this->folderService = folderService;
            this->currentFolderPath = boost::filesystem::current_path();
        }

        virtual void setCurrentFolderPath(const boost::filesystem::path &folderPath) override {
            currentFolderPath = folderPath;
        }

        virtual boost::filesystem::path getCurrentFolderPath() const override {
            return currentFolderPath;
        }

        virtual std::vector<boost::filesystem::path> listChildPaths(const boost::filesystem::path &folderPath) const override {
            return folderService->listChildFolders(folderPath);
        }
    
    private:
        FolderService *folderService;
        boost::filesystem::path currentFolderPath;
    };
}

namespace Xenoide {
    FolderBrowserModel::~FolderBrowserModel() {}

    std::unique_ptr<FolderBrowserModel> FolderBrowserModel::create(FolderService *folderService) {
        return std::make_unique<FolderBrowserModelImpl>(folderService);
    }
}


#include "FileSearchDialogModel.hpp"

#include <felide/util/FolderService.hpp>

namespace felide {
    class FileSearchDialogModelImpl : public FileSearchDialogModel {
    public:
        FileSearchDialogModelImpl(const boost::filesystem::path &baseFolder, FolderService *folderService)  {
            this->baseFolder = baseFolder;
            this->folderService = folderService;
        }

        virtual ~FileSearchDialogModelImpl() {}

        virtual std::vector<boost::filesystem::path> getFileList(const std::string &filePart) override {
            
        }

    private:
        boost::filesystem::path baseFolder;
        FolderService *folderService = nullptr;
    };
}

namespace felide {
    FileSearchDialogModel::~FileSearchDialogModel() {}
}


#include <Xenoide/Core/FolderService.hpp>

#include <boost/filesystem.hpp>

namespace Xenoide {
    class FolderServiceImpl : public FolderService {
    public:
        virtual std::vector<boost::filesystem::path> listChildFolders(const boost::filesystem::path &folderPath) const override {
            auto childPathVector = std::vector<boost::filesystem::path>{};

            auto subPathIterator = boost::filesystem::directory_iterator{folderPath};
            auto end = boost::filesystem::directory_iterator{};

            while (subPathIterator != end) {
                boost::filesystem::path subPath = subPathIterator->path();

                childPathVector.push_back(subPath);

                subPathIterator++;
            }

            return childPathVector;
        }    
    };
}


namespace Xenoide {
    FolderService::~FolderService() {}

    std::unique_ptr<FolderService> FolderService::create() {
        return std::make_unique<FolderServiceImpl>();
    }
}

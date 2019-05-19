
#include "FolderBrowserModel.hpp"

#include <boost/filesystem/operations.hpp>

namespace felide {
    class FolderBrowserModelImpl : public FolderBrowserModel {
    public:
        FolderBrowserModelImpl() {
            currentFolderPath = boost::filesystem::current_path();
        }

        virtual void setCurrentFolderPath(const boost::filesystem::path &folderPath) override {
            currentFolderPath = folderPath;
        }

        virtual boost::filesystem::path getCurrentFolderPath() const override {
            return currentFolderPath;
        }

        virtual std::vector<boost::filesystem::path> listChildPaths(const boost::filesystem::path &folderPath) const override {
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
    
    private:
        boost::filesystem::path currentFolderPath;
    };
}

namespace felide {
    FolderBrowserModel::~FolderBrowserModel() {}

    std::unique_ptr<FolderBrowserModel> FolderBrowserModel::create() {
        return std::make_unique<FolderBrowserModelImpl>();
    }
}

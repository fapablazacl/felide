
#include "FolderBrowserModel.hpp"

#include <boost/filesystem/operations.hpp>

namespace felide {
    class FolderBrowserModelImpl : public FolderBrowserModel {
    public:
        virtual boost::filesystem::path getCurrentFolderPath() const override {
            return boost::filesystem::current_path();
        }
    };
}

namespace felide {
    FolderBrowserModel::~FolderBrowserModel() {}

    std::unique_ptr<FolderBrowserModel> FolderBrowserModel::create() {
        return std::make_unique<FolderBrowserModelImpl>();
    }
}

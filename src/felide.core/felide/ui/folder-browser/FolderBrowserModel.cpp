
#include "FolderBrowserModel.hpp"

namespace felide {
    class FolderBrowserModelImpl : public FolderBrowserModel {
    public:
        virtual std::string getHello() const override {
            return "Hello, World!";
        }
    };
}

namespace felide {
    FolderBrowserModel::~FolderBrowserModel() {}

    std::unique_ptr<FolderBrowserModel> FolderBrowserModel::create() {
        return std::make_unique<FolderBrowserModelImpl>();
    }
}

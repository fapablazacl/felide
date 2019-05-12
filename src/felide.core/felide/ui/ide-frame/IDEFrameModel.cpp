
#include "IDEFrameModel.hpp" 

namespace felide {
    class IDEFrameModelImpl : public IDEFrameModel {
    public:
        virtual int getCreatedDocumentCount() const override {
            return createdDocumentCount;
        }

        virtual int increaseDocumentCount() override {
            return ++createdDocumentCount;
        }

        virtual std::vector<FileFilter> getFileFilters() const override {
            return {
                {"All Files", {"*.*"}},
                {"C/C++ Files", {"*.hpp", "*.cpp", "*.hh", "*.cc", "*.h", "*.c"}},
            };
        }

    private:
        int createdDocumentCount = 0;
    };
}

namespace felide {
    IDEFrameModel::~IDEFrameModel() {}

    std::unique_ptr<IDEFrameModel> IDEFrameModel::create() {
        return std::make_unique<IDEFrameModelImpl>();
    }
}

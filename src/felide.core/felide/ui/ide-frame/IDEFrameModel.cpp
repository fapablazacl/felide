
#include "IDEFrameModel.hpp" 

#include <felide/ui/document-manager/DocumentManagerModel.hpp>
#include <felide/ui/folder-browser/FolderBrowserModel.hpp>

namespace felide {
    class IDEFrameModelImpl : public IDEFrameModel {
    public:
        IDEFrameModelImpl() {
            this->documentManagerModel = DocumentManagerModel::create();
            this->folderBrowserModel = FolderBrowserModel::create();
        }

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

        virtual DocumentManagerModel *getDocumentManagerModel() override {
            return documentManagerModel.get();
        }

        virtual FolderBrowserModel *getFolderBrowserModel() override {
            return folderBrowserModel.get();
        }

    private:
        int createdDocumentCount = 0;
        std::unique_ptr<DocumentManagerModel> documentManagerModel;
        std::unique_ptr<FolderBrowserModel> folderBrowserModel;
    };
}

namespace felide {
    IDEFrameModel::~IDEFrameModel() {}

    std::unique_ptr<IDEFrameModel> IDEFrameModel::create() {
        return std::make_unique<IDEFrameModelImpl>();
    }
}

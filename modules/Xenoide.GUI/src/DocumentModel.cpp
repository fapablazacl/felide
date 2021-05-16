
#include <Xenoide/GUI/DocumentModel.hpp>

namespace Xenoide {
    class DocumentModelImpl : public DocumentModel {
    public:
        DocumentModelImpl(int tag) {
            id = ++count;

            this->tag = tag;
        }

        DocumentModelImpl(const std::string &filePath) {
            id = ++count;
        
            this->setFilePath(filePath);
        }

        DocumentModelImpl(const std::string &filePath, const std::string &content) {
            id = ++count;

            this->setFilePath(filePath);
            this->setContent(content);
        }

        virtual ~DocumentModelImpl() {}

        int getTag() const {
            return tag;
        }

        int getId() const {
            return id;
        }

        void setModifiedFlag(const bool value) {
            modified = value;
        }

        bool getModifiedFlag() const {
            return modified;
        }

        void modify() {
            modified = true;
        }

        void setFilePath(const std::string &value) {
            filePath = value;
        }

        std::string getFilePath() const {
            return filePath;
        }

        bool hasFilePath() const {
            return filePath != "";
        }

        void setContent(const std::string &value) {
            content = value;
        }

        std::string getContent() const {
            return content;        
        }

    private:
        int tag = 0;
        int id = 0;
        bool modified = false;
        std::string filePath;
        std::string content;
    };
}

namespace Xenoide {
    int DocumentModel::count = 0;

    DocumentModel::~DocumentModel() {}

    int DocumentModel::getCount() {
        return DocumentModel::count;
    }

    std::unique_ptr<DocumentModel> DocumentModel::create(int tag) {
        return std::make_unique<DocumentModelImpl>(tag);
    }

    std::unique_ptr<DocumentModel> DocumentModel::create(const std::string &filePath) {
        return std::make_unique<DocumentModelImpl>(filePath);
    }

    std::unique_ptr<DocumentModel> DocumentModel::create(const std::string &filePath, const std::string &content) {
        return std::make_unique<DocumentModelImpl>(filePath, content);
    }
}

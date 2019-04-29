
#include "DocumentModel.hpp"

namespace felide {
    int DocumentModel::count = 0;

    DocumentModel::DocumentModel(int tag) {
        this->tag = tag;
        id = ++count;
    }

    DocumentModel::DocumentModel(const std::string &filePath) {
        id = ++count;
        
        this->setFilePath(filePath);
    }

    DocumentModel::DocumentModel(const std::string &filePath, const std::string &content) {
        id = ++count;

        this->setFilePath(filePath);
        this->setContent(content);
    }

    DocumentModel::~DocumentModel() {}

    int DocumentModel::getTag() const {
        return tag;
    }

    int DocumentModel::getId() const {
        return id;
    }

    void DocumentModel::setModifiedFlag(const bool value) {
        modified = value;
    }

    bool DocumentModel::getModifiedFlag() const {
        return modified;
    }

    void DocumentModel::modify() {
        modified = true;
    }

    void DocumentModel::setFilePath(const std::string &value) {
        filePath = value;
    }

    std::string DocumentModel::getFilePath() const {
        return filePath;
    }

    bool DocumentModel::hasFilePath() const {
        return filePath != "";
    }

    void DocumentModel::setContent(const std::string &value) {
        content = value;
    }

    std::string DocumentModel::getContent() const {
        return content;        
    }
}

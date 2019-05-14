
#include "DocumentManagerModel.hpp"

#include <list>
#include <algorithm>
#include <felide/ui/document/DocumentModel.hpp>

namespace felide {
    class DocumentManagerModelImpl : public DocumentManagerModel {
    public:
        virtual ~DocumentManagerModelImpl() {}

        virtual DocumentModel* createDocument() override {
            auto document = DocumentModel::create(++createdDocumentCount);
            auto documentPtr = document.get();

            documents.push_back(std::move(document));

            return documentPtr;
        }

        virtual DocumentModel* createDocument(const boost::filesystem::path &filePath) override {
            auto document = this->createDocument();
            document->setFilePath(filePath.string());

            return document;
        }

        virtual void closeDocument(DocumentModel *documentModel) override {
            auto documentIt = std::find_if(documents.begin(), documents.end(), [documentModel](auto &document) {
                return document.get() == documentModel;
            });

            if (documentIt != documents.end()) {
                documents.erase(documentIt);
            }
        }

        virtual std::vector<DocumentModel*> enumerateDocuments() const override {
            std::vector<DocumentModel*> result;

            result.reserve(documents.size());

            for (auto &document : documents) {
                result.push_back(document.get());
            }

            return result;
        }

    private:
        std::list<std::unique_ptr<DocumentModel>> documents;
        int createdDocumentCount = 0;
    };
}

namespace felide {
    DocumentManagerModel::~DocumentManagerModel() {}

    std::unique_ptr<DocumentManagerModel> DocumentManagerModel::create() {
        return std::make_unique<DocumentManagerModelImpl>();
    }
}

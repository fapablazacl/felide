
#ifndef __FELIDE_UI_DOCUMENTMANAGERMODEL_HPP__
#define __FELIDE_UI_DOCUMENTMANAGERMODEL_HPP__

#include <memory>
#include <string>
#include <vector>
#include <felide/Predef.hpp>
#include <boost/filesystem/path.hpp>

namespace felide {
    class FELIDE_API DocumentModel;
    class FELIDE_API DocumentManagerModel {
    public:
        virtual ~DocumentManagerModel();

        virtual DocumentModel* createDocument() = 0;

        virtual DocumentModel* createDocument(const boost::filesystem::path &filePath) = 0;

        virtual void closeDocument(DocumentModel *documentModel) = 0;

        virtual std::vector<DocumentModel*> enumerateDocuments() const = 0;

    public:
        static std::unique_ptr<DocumentManagerModel> create();
    };
}

#endif

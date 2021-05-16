
#ifndef __FELIDE_UI_DOCUMENTMODEL_HPP__
#define __FELIDE_UI_DOCUMENTMODEL_HPP__

#include <string>
#include <memory>

namespace felide {
    /**
     * An abstraction of a Document.
     */
    class DocumentModel {
    public:
        virtual ~DocumentModel();

        virtual int getTag() const = 0;

        virtual int getId() const = 0;

        virtual void setModifiedFlag(const bool value) = 0;

        virtual bool getModifiedFlag() const = 0;

        virtual void modify() = 0;

        virtual void setFilePath(const std::string &value) = 0;

        virtual std::string getFilePath() const = 0;

        virtual bool hasFilePath() const = 0;

        virtual void setContent(const std::string &value) = 0;

        virtual std::string getContent() const = 0;

    public:
        static int getCount();

        static std::unique_ptr<DocumentModel> create(int tag);

        static std::unique_ptr<DocumentModel> create(const std::string &filePath);

        static std::unique_ptr<DocumentModel> create(const std::string &filePath, const std::string &content);

    protected:
        static int count;
    };
}

#endif

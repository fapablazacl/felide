
#ifndef __FELIDE_UI_EDITORMODEL_HPP__
#define __FELIDE_UI_EDITORMODEL_HPP__

#include <string>

namespace felide {
    class EditorModel {
    public:
        explicit EditorModel();

        explicit EditorModel(const std::string &filePath);

        explicit EditorModel(const std::string &filePath, const std::string &content);

        ~EditorModel();

        int getId() const;

        void setModifiedFlag(const bool value);

        bool getModifiedFlag() const;

        void modify();

        void setFilePath(const std::string &value);

        std::string getFilePath() const;

        bool hasFilePath() const;

        void setContent(const std::string &value);

        std::string getContent() const;

    private:
        int id = 0;
        bool modified = false;
        std::string filePath;
        std::string content;

    private:
        static int count;
    };
}

#endif

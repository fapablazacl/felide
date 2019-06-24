
#include "FileSearchDialogModel.hpp"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

namespace felide {
    class FileSearchDialogModelImpl : public FileSearchDialogModel {
    public:
        FileSearchDialogModelImpl(const boost::filesystem::path &basePath) {
            this->basePath = basePath;
        }

        virtual ~FileSearchDialogModelImpl() {}

        virtual void scanFolder() {
            this->files = this->getFileList();
        }

        virtual std::vector<boost::filesystem::path> searchFilePattern(const std::string &filePattern) override {
            std::vector<boost::filesystem::path> filteredFiles;

            std::string filePatternUppercased = filePattern;
            boost::to_upper(filePatternUppercased);

            for (const boost::filesystem::path &filePath : this->files) {
                std::string testAgaint = filePath.string();
                boost::to_upper(testAgaint);

                if (testAgaint.find(filePatternUppercased) != std::string::npos) {
                    filteredFiles.push_back(filePath);
                }
            }

            return filteredFiles;
        }

    private:
        std::vector<boost::filesystem::path> getFileList() const {
            std::vector<boost::filesystem::path> files;

            this->populateFileList(basePath, files);
            
            return files;
        }

        void populateFileList(const boost::filesystem::path &folder, std::vector<boost::filesystem::path> &files) const {
            if (! boost::filesystem::is_directory(folder)) {
                return;
            }

            boost::filesystem::directory_iterator subPathIterator(folder);
            boost::filesystem::directory_iterator end;

            while (subPathIterator != end) {
                boost::filesystem::path subPath = subPathIterator->path();

                files.push_back(subPath);
                this->populateFileList(subPath, files);

                subPathIterator++;
            }
        }

    private:
        boost::filesystem::path basePath;
        std::vector<boost::filesystem::path> files;
    };
}

namespace felide {
    FileSearchDialogModel::~FileSearchDialogModel() {}

    std::unique_ptr<FileSearchDialogModel> FileSearchDialogModel::create(const boost::filesystem::path &basePath) {
        return std::make_unique<FileSearchDialogModelImpl>(basePath);
    }
}

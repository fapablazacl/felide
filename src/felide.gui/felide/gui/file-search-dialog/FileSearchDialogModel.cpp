
#include "FileSearchDialogModel.hpp"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>

namespace felide {
    static bool is_logically_hidden(const boost::filesystem::path &path) {
        const std::string title = path.filename().string();

        std::cout << path.string() << " isHidden: " << (title[0] == '.') << std::endl;

        return title[0] == '.';
    }

    class FileSearchDialogModelImpl : public FileSearchDialogModel {
    public:
        FileSearchDialogModelImpl(const boost::filesystem::path &basePath) {
            this->basePath = basePath;
        }

        virtual ~FileSearchDialogModelImpl() {}

        virtual std::vector<boost::filesystem::path> searchFilePattern(const std::string &filePattern, const int maxResults) override {
            std::string filePatternUppercased = filePattern;
            boost::to_upper(filePatternUppercased);

            return this->search(filePatternUppercased, maxResults);
        }

    private:
        bool testFile(const boost::filesystem::path &filePath, const std::string &filePattern) const {
            std::string testAgaint = filePath.filename().string();
            boost::to_upper(testAgaint);

            return testAgaint.find(filePattern) != std::string::npos;
        }

        std::vector<boost::filesystem::path> search(const std::string &filePattern, const int maxResults) const {
            std::vector<boost::filesystem::path> files;

            this->searchImpl(files, basePath, filePattern, maxResults);

            return files;
        }

        void searchImpl(std::vector<boost::filesystem::path> &files, const boost::filesystem::path &folder, const std::string &filePattern, const int maxResults) const {
            // skips search inside files ...
            if (! boost::filesystem::is_directory(folder)) {
                return;
            }

            // skips hidden directories
            if ( boost::filesystem::is_directory(folder) && is_logically_hidden(folder)) {
                return;
            }

            boost::filesystem::directory_iterator subPathIterator(folder);
            boost::filesystem::directory_iterator end;

            while (subPathIterator != end) {
                boost::filesystem::path subPath = subPathIterator->path();

                if (this->testFile(subPath, filePattern)) {
                    files.push_back(subPath);
                }

                if (files.size() + 1 >= maxResults) {
                    return;
                }

                this->searchImpl(files, subPath, filePattern, maxResults);

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


#ifndef __FELIDE_UI_FILESEARCHDIALOGMODEL_HPP__
#define __FELIDE_UI_FILESEARCHDIALOGMODEL_HPP__

#include <vector>
#include <memory>
#include <boost/filesystem/path.hpp>

namespace felide {
    class FileSearchDialogModel {
    public:
        virtual ~FileSearchDialogModel();

        virtual std::vector<boost::filesystem::path> searchFilePattern(const std::string &filePattern, const int maxResults) = 0;

    public:
        static std::unique_ptr<FileSearchDialogModel> create(const boost::filesystem::path &basePath);
    };
}

#endif
 

#ifndef __FELIDE_UI_FILESEARCHDIALOGMODEL_HPP__
#define __FELIDE_UI_FILESEARCHDIALOGMODEL_HPP__

#include <vector>
#include <boost/filesystem/path.hpp>

namespace felide {
    class FileSearchDialogModel {
    public:
        virtual ~FileSearchDialogModel();

        virtual std::vector<boost::filesystem::path> getFileList(const std::string &filePart) = 0;
    };
}

#endif
 

#ifndef __FELIDE_UI_FOLDERSERVICE_HPP__
#define __FELIDE_UI_FOLDERSERVICE_HPP__

#include <memory>
#include <string>
#include <boost/filesystem/path.hpp>

namespace felide {
    class FolderService {
    public:
        virtual ~FolderService();

        virtual std::vector<boost::filesystem::path> listChildFolders(const boost::filesystem::path &folderPath) const = 0;

    public:
        static std::unique_ptr<FolderService> create();
    };
}

#endif


#ifndef __FELIDE_UI_FOLDERSERVICE_HPP__
#define __FELIDE_UI_FOLDERSERVICE_HPP__

#include <memory>
#include <string>
#include <boost/filesystem/path.hpp>

namespace felide {
    class FolderService {
    public:
        virtual ~FolderService() = 0;

    public:
        static std::unique_ptr<FolderService> create();
    };
}

#endif

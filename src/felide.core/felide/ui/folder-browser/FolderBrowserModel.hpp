
#ifndef __FELIDE_UI_FOLDERBROWSERMODEL_HPP__
#define __FELIDE_UI_FOLDERBROWSERMODEL_HPP__

#include <string>
#include <memory>
#include <boost/filesystem/path.hpp>

namespace felide {
    class FolderBrowserModel {
    public:
        virtual ~FolderBrowserModel();

        virtual boost::filesystem::path getCurrentFolderPath() const = 0;

    public:
        static std::unique_ptr<FolderBrowserModel> create();
    };
}

#endif

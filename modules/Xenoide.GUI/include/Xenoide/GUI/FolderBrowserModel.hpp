
#ifndef __XENOIDE_UI_FOLDERBROWSERMODEL_HPP__
#define __XENOIDE_UI_FOLDERBROWSERMODEL_HPP__

#include <string>
#include <memory>
#include <vector>
#include <boost/filesystem/path.hpp>

namespace felide {
    class FolderService;

    class FolderBrowserModel {
    public:
        virtual ~FolderBrowserModel();

        virtual void setCurrentFolderPath(const boost::filesystem::path &folderPath) = 0;

        virtual boost::filesystem::path getCurrentFolderPath() const = 0;

        virtual std::vector<boost::filesystem::path> listChildPaths(const boost::filesystem::path &folderPath) const = 0;

    public:
        static std::unique_ptr<FolderBrowserModel> create(FolderService *folderService);
    };
}

#endif

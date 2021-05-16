
#ifndef __XENOIDE_UI_MAINWINDOWMODEL_HPP__
#define __XENOIDE_UI_MAINWINDOWMODEL_HPP__

#include <memory>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>

#include <Xenoide/Core/Predef.hpp>
#include <Xenoide/GUI/FileFilter.hpp>

namespace Xenoide {
    class DocumentManagerModel;
    class FolderBrowserModel;

    class IDEFrameModel {
    public:
        virtual ~IDEFrameModel();

        virtual std::vector<FileFilter> getFileFilters() const = 0;

        virtual DocumentManagerModel *getDocumentManagerModel() = 0;

        virtual FolderBrowserModel *getFolderBrowserModel() = 0;

        virtual boost::optional<boost::filesystem::path> getWorkspaceFolder() const = 0;

        virtual void setWorkspaceFolder(boost::filesystem::path workspaceFolder) = 0;

    public:
        static std::unique_ptr<IDEFrameModel> create();
    };
} 

#endif

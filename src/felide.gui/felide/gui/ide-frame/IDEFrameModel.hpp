
#ifndef __FELIDE_UI_MAINWINDOWMODEL_HPP__
#define __FELIDE_UI_MAINWINDOWMODEL_HPP__

#include <memory>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>

#include <felide/Predef.hpp>
#include <felide/gui/FileFilter.hpp>

namespace felide {
    class FELIDE_API DocumentManagerModel;
    class FELIDE_API FolderBrowserModel;

    class FELIDE_API IDEFrameModel {
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

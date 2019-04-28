
#ifndef __FELIDE_UI_FOLDEREXPLORERVIEW_HPP_
#define __FELIDE_UI_FOLDEREXPLORERVIEW_HPP_

#include <string>
#include <felide/Predef.hpp>
#include <boost/optional/optional.hpp>

namespace felide {
    class FELIDE_API FolderBrowserController;
    class FELIDE_API FolderBrowser {
    public:
        explicit FolderBrowser(FolderBrowserController *presenter);
        virtual ~FolderBrowser();

        virtual void displayFolder(const std::string &folder) = 0;

        virtual boost::optional<std::string> getSelectedPath() const = 0;

    protected:
        FolderBrowserController *m_presenter;
    };
} 

#endif

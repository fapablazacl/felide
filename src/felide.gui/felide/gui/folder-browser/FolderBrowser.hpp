
#ifndef __FELIDE_UI_FOLDEREXPLORERVIEW_HPP_
#define __FELIDE_UI_FOLDEREXPLORERVIEW_HPP_

#include <string>
#include <felide/core/Predef.hpp>
#include <felide/gui/Menu.hpp>
#include <boost/optional/optional.hpp>

namespace felide {
    struct Point {
        int x, y;
    };

    class FELIDE_API FolderBrowserPresenter;
    class FELIDE_API FolderBrowser {
    public:
        explicit FolderBrowser(FolderBrowserPresenter *presenter);
        virtual ~FolderBrowser();

        virtual void displayFolder(const std::string &folder) = 0;

        virtual boost::optional<std::string> getSelectedPath() const = 0;

        virtual void displayContextualMenu(const Point &point, const Menu &menu) = 0;

    protected:
        FolderBrowserPresenter *m_presenter;
    };
} 

#endif

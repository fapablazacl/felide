
#ifndef __XENOIDE_UI_FOLDEREXPLORERVIEW_HPP_
#define __XENOIDE_UI_FOLDEREXPLORERVIEW_HPP_

#include <string>
#include <Xenoide/Core/Predef.hpp>
#include <Xenoide/Gui/Menu.hpp>
#include <boost/optional/optional.hpp>

namespace Xenoide {
    struct Point {
        int x, y;
    };

    class FolderBrowserPresenter;
    class FolderBrowser {
    public:
        explicit FolderBrowser(FolderBrowserPresenter *presenter);
        virtual ~FolderBrowser();

        virtual void displayFolder(const std::string &folder) = 0;

        virtual boost::optional<std::string> getSelectedPath() const = 0;

        virtual void displayContextualMenu(const Point &point, const Menu &menu) = 0;

    protected:
        FolderBrowserPresenter *mPresenter;
    };
} 

#endif

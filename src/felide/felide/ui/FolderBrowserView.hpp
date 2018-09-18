
#ifndef __FELIDE_UI_FOLDEREXPLORERVIEW_HPP_
#define __FELIDE_UI_FOLDEREXPLORERVIEW_HPP_

#include <string>

namespace felide {
    class FolderBrowserView {
    public:
        virtual ~FolderBrowserView();

        virtual void displayFolder(const std::string &folder) = 0;
    };
} 

#endif

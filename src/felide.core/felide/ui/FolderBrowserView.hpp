
#ifndef __FELIDE_UI_FOLDEREXPLORERVIEW_HPP_
#define __FELIDE_UI_FOLDEREXPLORERVIEW_HPP_

#include <string>
#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API FolderBrowserView {
    public:
        virtual ~FolderBrowserView();

        virtual void displayFolder(const std::string &folder) = 0;
    };
} 

#endif

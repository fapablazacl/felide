
#ifndef __FELIDE_UI_FOLDERBROWSERMODEL_HPP__
#define __FELIDE_UI_FOLDERBROWSERMODEL_HPP__

#include <string>
#include <memory>

namespace felide {
    class FolderBrowserModel {
    public:
        virtual ~FolderBrowserModel();

        virtual std::string getHello() const = 0;

    public:
        static std::unique_ptr<FolderBrowserModel> create();
    };
}

#endif


#ifndef __FELIDE_UI_MAINWINDOWMODEL_HPP__
#define __FELIDE_UI_MAINWINDOWMODEL_HPP__

#include <vector>
#include <felide/Predef.hpp>
#include <felide/ui/FileFilter.hpp>

namespace felide {
    class FELIDE_API IDEFrameModel {
    public:
        int getCreatedDocumentCount() const;

        int increaseDocumentCount();

        std::vector<FileFilter> getFileFilters() const;

    private:
        int createdDocumentCount = 0;
    };
} 

#endif

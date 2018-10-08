
#ifndef __FELIDE_UI_MAINWINDOWMODEL_HPP__
#define __FELIDE_UI_MAINWINDOWMODEL_HPP__

#include <felide/Predef.hpp>

namespace felide {
    class FELIDE_API IDEFrameModel {
    public:
        int getCreatedDocumentCount() const;

        int increaseDocumentCount();

    private:
        int createdDocumentCount = 0;
    };
} 

#endif

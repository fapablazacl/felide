
#include "IDEFrameModel.hpp" 

namespace felide {
    int IDEFrameModel::getCreatedDocumentCount() const {
        return createdDocumentCount;
    }

    int IDEFrameModel::increaseDocumentCount() {
        return ++createdDocumentCount;
    }
}


#include "MainWindowModel.hpp" 

namespace felide {
    int MainWindowModel::getCreatedDocumentCount() const {
        return createdDocumentCount;
    }

    int MainWindowModel::increaseDocumentCount() {
        return ++createdDocumentCount;
    }
}

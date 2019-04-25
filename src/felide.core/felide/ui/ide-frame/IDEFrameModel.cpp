
#include "IDEFrameModel.hpp" 

namespace felide {
    int IDEFrameModel::getCreatedDocumentCount() const {
        return createdDocumentCount;
    }

    int IDEFrameModel::increaseDocumentCount() {
        return ++createdDocumentCount;
    }

    std::vector<FileFilter> IDEFrameModel::getFileFilters() const {
        return {
            {"All Files", {"*.*"}},
            {"C/C++ Files", {"*.hpp", "*.cpp", "*.hh", "*.cc", "*.h", "*.c"}},
        };
    }
}

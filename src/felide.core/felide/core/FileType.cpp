
#include "FileType.hpp"

#include <algorithm>

namespace felide {
    /*
    bool FileType::operator== (const FileType &rhs) const {
        return name == rhs.name;
    }
    
    bool FileType::operator!= (const FileType &rhs) const {
        return ! (*this == rhs);
    }
    */

    bool FileType::check(const std::string &extension) const {
        auto it = std::find(extensions.begin(), extensions.end(), extension);

        return it != extensions.end();
    }
}
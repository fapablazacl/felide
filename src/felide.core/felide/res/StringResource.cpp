
#include "StringResource.hpp"

#include <map>

namespace felide {
    struct StringResource::Private {
        std::map<std::string, std::string> values;
    };

    StringResource::StringResource() {

    }

    StringResource::~StringResource() {

    }

    std::string StringResource::get(const std::string &key) const {
        return "";
    }
} 

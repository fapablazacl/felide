
#ifndef __FELIDE_CORE_POM_MODELS_PROJECTMODEL_HPP__
#define __FELIDE_CORE_POM_MODELS_PROJECTMODEL_HPP__

#include <tuple>
#include <string>
#include <vector>

namespace felide {
    struct ProjectModel {
        std::string name;
        std::string description;
        std::string version;
        std::string author;
        std::string license;
        std::vector<std::string> modules;
    };
}

#endif

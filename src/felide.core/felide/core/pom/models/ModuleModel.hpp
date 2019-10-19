
#ifndef __FELIDE_CORE_POM_MODELS_MODULEMODEL_HPP__
#define __FELIDE_CORE_POM_MODELS_MODULEMODEL_HPP__

#include <tuple>
#include <map>
#include <string>
#include <vector>

namespace felide {
    struct ModuleModel {
        std::string name;
        std::string type;
        std::map<std::string, std::string> defines;
        std::vector<std::string> imports;
        std::vector<std::string> sources;
    };
}

#endif

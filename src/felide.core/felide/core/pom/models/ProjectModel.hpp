
#ifndef __FELIDE_CORE_POM_MODELS_PROJECTMODEL_HPP__
#define __FELIDE_CORE_POM_MODELS_PROJECTMODEL_HPP__

#include "PropertyImpl.hpp"
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
        
        constexpr static auto properties = std::make_tuple (
            property(&ProjectModel::name, "name"),
            property(&ProjectModel::description, "description"),
            property(&ProjectModel::version, "version"),
            property(&ProjectModel::author, "author"),
            property(&ProjectModel::author, "author"),
            property(&ProjectModel::license, "license"),
            property(&ProjectModel::modules, "modules")
        );
    };
}

#endif


#include "ProjectFactory.hpp"

#include <optional>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <borc/core/FileUtil.hpp>
#include <borc/core/Module.hpp>
#include <borc/core/Project.hpp>

namespace borc {
    namespace model {
        struct Package {
            std::string name;
            std::optional<std::string> description;
            std::string version;
            std::optional<std::string> author;
            std::optional<std::string> license;
            std::vector<std::string> paths;
        };

        struct Module {
            std::string name;
            std::string type;
            std::optional<std::vector<std::string>> imports;
            std::vector<std::string> sources;
            std::optional<std::string> export_;
        };
    }

    borc::model::Package makePackageFromJson(const nlohmann::json &json) {
        borc::model::Package package;

        package.name = json["name"].get<std::string>();
        package.description = json["description"].get<std::string>();
        package.author = json["author"].get<std::string>();
        package.license = json["license"].get<std::string>();
        package.paths = json["paths"].get<std::vector<std::string>>();

        return package;
    }
    
    borc::model::Module makeModuleFromJson(const nlohmann::json &json) {
        borc::model::Module module;

        module.name = json["name"].get<std::string>();
        module.type = json["type"].get<std::string>();
        
        if (json.find("sources") != json.end()) {
            module.sources = json["sources"].get<std::vector<std::string>>();
        }

        if (json.find("imports") != json.end()) {
            module.imports = json["imports"].get<std::vector<std::string>>();
        }

        return module;
    }

    nlohmann::json makeJsonFromFile(const std::filesystem::path &filePath) {
        const std::string fileContent = FileUtil::load(filePath.string());
        return nlohmann::json::parse(fileContent);
    }

    std::unique_ptr<Project> ProjectFactory::createProject(const std::string &file) const {
        const auto filePath = std::filesystem::path(file);
        const auto parentPath = std::filesystem::path(filePath).parent_path();
        const nlohmann::json packageJson = makeJsonFromFile(filePath);

        borc::model::Package packageModel = makePackageFromJson(packageJson);

        std::vector<borc::model::Module> moduleModels;

        for (const std::string &partialPath : packageModel.paths) {
            const std::filesystem::path moduleFilePath = parentPath / partialPath / "Module.borc.json";
            const nlohmann::json moduleJson = makeJsonFromFile(moduleFilePath);

            const borc::model::Module module = makeModuleFromJson(moduleJson);

            moduleModels.push_back(module);
        }

        return std::unique_ptr<Project>();
    }
}

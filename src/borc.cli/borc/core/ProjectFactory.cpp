
#include "ProjectFactory.hpp"

#include <optional>
#include <iostream>
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

    std::unique_ptr<Project> ProjectFactory::createProject(const std::string &filePath) const {
        std::cout << filePath << std::endl;

        const std::string packageFileContent = FileUtil::load(filePath);
        const nlohmann::json packageJson = nlohmann::json::parse(packageFileContent);

        borc::model::Package packageModel;
        packageModel.name = packageJson["name"].get<std::string>();
        packageModel.description = packageJson["description"].get<std::string>();
        packageModel.author = packageJson["author"].get<std::string>();
        packageModel.license = packageJson["license"].get<std::string>();
        packageModel.paths = packageJson["paths"].get<std::vector<std::string>>();

        return std::unique_ptr<Project>();
    }
}


#include "ProjectParserJson.hpp"

#include <stdexcept>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include <felide/core/util/FileUtil.hpp>

#include <felide/core/pom/Project.hpp>
#include <felide/core/pom/models/ProjectModel.hpp>
#include <felide/core/pom/models/ModuleModel.hpp>

namespace felide {
    static nlohmann::json jsonFromFile(const std::string &filePath) {
        return {};
    }

    static boost::filesystem::path computeProjectBasePath(const std::string &projectPath) {
        return boost::filesystem::path(projectPath).parent_path();
    }

    ProjectParserJson::~ProjectParserJson() {}

    std::unique_ptr<Project> ProjectParserJson::parse(const boost::filesystem::path &filePath) {
        if (! boost::filesystem::exists(filePath) || !boost::filesystem::is_regular_file(filePath) 
        || filePath.filename().string() != "Project.borc") {
            throw std::runtime_error("Borc project files must be regular filenames and must be named Project.borc");
        }

        const boost::filesystem::path parentPath = filePath.parent_path();
        const nlohmann::json json = jsonFromFile(parentPath.string());

        return {};
    }
}


#include "ProjectParserYaml.hpp"

#include "Target.hpp"
#include "CppProject.hpp"

#include <iostream>

#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>

namespace fs = boost::filesystem;

namespace borc {
    void parseTarget(Target *target, const YAML::Node &node) {
        // get name
        target->setName(node["name"].as<std::string>());

        // get target relative directory
        if (node["path"]) {
            target->setPath(node["path"].as<std::string>());
        } else {
            target->setPath(target->getName());
        }

        // get target dependencies 
        /*
        if (node["imports"]) {
        if (node["imports"].IsSequence()) {
        for (const YAML::Node &depNode : node["imports"]) {
        target.deps.push_back(depNode.as<std::string>());
        }
        } else {
        const auto dep = node["imports"].as<std::string>();
        target.deps.push_back(dep);
        }
        }
        */
    }

    std::unique_ptr<Project> ProjectParserYaml::parse(const std::string &file) {
        fs::path path(file);

        YAML::Node borcfile = YAML::LoadFile(path.string());

        if (!borcfile["project"]) {
            throw std::runtime_error("There isn't a 'project' section defined");
        }

        if (!borcfile["targets"] || borcfile["targets"].size() == 0) {
            throw std::runtime_error("There isn't a 'targets' section defined");
        }

        auto projectNode = borcfile["project"];
        auto projectName = projectNode["name"].as<std::string>();
        auto project = std::make_unique<CppProject>(projectName);

        for (const YAML::Node targetNode : borcfile["targets"]) {
            auto target = project->addTarget();

            parseTarget(target, targetNode);

            if (targetNode["library"]) {
                target->setType(TargetType::Library);
            }
            else if (targetNode["program"]) {
                target->setType(TargetType::Program);
            }
        }

        return project;
    }
}

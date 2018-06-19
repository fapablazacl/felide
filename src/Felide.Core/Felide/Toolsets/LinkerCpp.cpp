
#include "LinkerCpp.hpp"

#include <Felide/TreeNode.hpp>
#include <Felide/POM/Source.hpp>
#include <Felide/POM/Target.hpp>
#include <Felide/Tasks/LogTask.hpp>
#include <Felide/Tasks/Task.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/join.hpp>

#include <fmt/format.h>

namespace Felide {
    LinkerCpp::LinkerCpp(const std::string &toolName) {
        m_toolName = toolName;
    }

    LinkerCpp::LinkerCpp(const std::string &toolName, const std::string &path) {
        m_toolName = toolName;
        m_path = path;
    }

    LinkerCpp::~LinkerCpp() {}

    bool LinkerCpp::isLinkable(const Target *target) const {
        if (target) {
            return true;
        } else {
            return false;
        }
    }

    std::string LinkerCpp::getToolName() const {
        return m_toolName;
    }

    std::string LinkerCpp::getPath() const {
        return m_path;
    }

    std::unique_ptr<TreeNode<Task>> LinkerCpp::createTask(const Target *target, const std::vector<std::string> &objectFiles) {
        assert(target);

        if (objectFiles.size() == 0) {
            throw std::runtime_error("At linking stage we should have one or more object files");
        }

        const std::string joinedObjectFiles = boost::join(objectFiles, " ");

        const std::string cmdTemplate = "{0} {1} {2}";
        const std::string targetName = target->getName();
        const std::string cmd = fmt::format(cmdTemplate, m_toolName, targetName, joinedObjectFiles);

        return TreeNode<Task>::create(std::make_unique<LogTask>(cmd));
    }
}
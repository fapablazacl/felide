
#include "ModuleLinker.hpp"
#include "ModuleToolset.hpp"

#include <felide/TreeNode.hpp>
#include <felide/util/Strings.hpp>
#include <felide/pom/Source.hpp>
#include <felide/pom/Target.hpp>
#include <felide/tasks/LogTask.hpp>
#include <felide/tasks/CommandTask.hpp>

#include <boost/filesystem.hpp>
#include <iostream>
#include <cassert>

namespace felide {
    const std::string FELIDE_OBJECT_FILES = "${ObjectFiles}";
    const std::string FELIDE_TARGET_NAME = "${TargetName}";
    
    ModuleLinker::ModuleLinker(const ModuleToolset *toolset, const LinkerDescription &description) {
        m_toolset = toolset;
        m_description = description;
    }

    ModuleLinker::~ModuleLinker() {}

    bool ModuleLinker::isLinkable(const Target *target) const {
        return target != nullptr;
    }

    std::string ModuleLinker::getToolName() const {
        return "m_toolName";
    }

    std::string ModuleLinker::getPath() const {
        return "m_path";
    }

    std::unique_ptr<TreeNode<Task>> ModuleLinker::createTask(const Target *target, const std::vector<std::string> &objectFiles, const ActionContext &context) {
        assert(target);

        if (objectFiles.size() == 0) {
            throw std::runtime_error("At linking stage we should have one or more object files");
        }

        const std::string joinedObjectFiles = join(objectFiles, " ");
        const std::string targetName = target->getName();

        std::string cmd = m_description.linkTemplate;

        cmd = replace(cmd, FELIDE_OBJECT_FILES, joinedObjectFiles);
        cmd = replace(cmd, FELIDE_TARGET_NAME, targetName);
        cmd = instanceTemplate(cmd, context);

        return TreeNode<Task>::create(std::make_unique<CommandTask>(cmd));
    }
}

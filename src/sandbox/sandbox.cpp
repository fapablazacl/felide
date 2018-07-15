
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <felide/TreeNode.hpp>
#include <felide/pom/Project.hpp>
#include <felide/pom/ModuleTarget.hpp>
#include <felide/pom/ModuleTargetType.hpp>
#include <felide/pom/TargetAction.hpp>
#include <felide/tasks/Task.hpp>

#include <felide/cpp/ModuleToolset.hpp>

#include <felide/FileTypeRegistry.hpp>

static std::unique_ptr<felide::FileTypeRegistry> createRegistry() {
    auto registry = felide::FileTypeRegistry::create();

    registry->addFileType("C Source File", {".c"});
    registry->addFileType("C Header File", {".h"});
    registry->addFileType("C++ Source File", {".cpp", ".cxx", ".cc", ".c++"});
    registry->addFileType("C++ Header File", {".hpp", ".hxx", ".hh", ".h++"});

    return registry;
}

static std::unique_ptr<felide::Project> createProject() {
    auto project = felide::Project::create("felide", "/Users/fapablaza/Desktop/devwarecl/felide");

    project->createTarget<felide::ModuleTarget>()
        ->setType(felide::ModuleTargetType::Library)
        ->setName("felide.core")
        ->setPath("src/felide.core");
        
    return project;
}

int main(int argc, char **argv) {
    try {
        auto registry = createRegistry();
        auto toolset = felide::ToolsetCpp::create(registry.get());

        auto project = createProject();
        auto task = project->createTask(felide::TargetAction::Build);

        task->getData()->perform();

        return 0;
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;

        return 1;
    }

    return 1001;
}

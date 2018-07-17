
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
#include <felide/tasks/TaskNodeVisitor.hpp>

#include <felide/cpp/ModuleCompiler.hpp>
#include <felide/cpp/ModuleLinker.hpp>
#include <felide/cpp/ModuleToolset.hpp>

#include <felide/FileTypeRegistry.hpp>

#define XSTR(a) STR(a)
#define STR(a) #a

static std::unique_ptr<felide::Project> createProject(felide::Toolset *toolset) {
    const std::string rootPath = XSTR(PROJECT_SOURCE_DIR);

    std::cout << "Building project at \"" << rootPath << "\" ..." << std::endl;

    auto project = felide::Project::create("felide", rootPath);

    project->createTarget<felide::ModuleTarget>()
        ->setType(felide::ModuleTargetType::Library)
        ->setName("felide.core")
        ->setPath("src/felide.core")
        ->setToolset(toolset);

    return project;
}

int main(int argc, char **argv) {
    try {
        const std::string rootPath = XSTR(PROJECT_SOURCE_DIR);

        const felide::CompilerActionContext context = {
            {"${IncludeDirectory}", rootPath + "/src/felide.core"}
        };

        auto toolset = felide::ModuleToolset::create (
            ".felide/build/gcc",
            {
                felide::CompilerDescription {
                    "gcc -g -O0 -c ${InputFile} -o ${OutputFile} ${IncludeDirectory}",
                    {".cpp", ".cxx", ".cc", ".c++"}, 
                    ".obj",
                    {
                        {"${IncludeDirectory}", "-I"}
                    }
                }
            }, {
                felide::LinkerDescription {
                    "gcc ${ObjectFiles} -o ${TargetName} -lstdc++",
                    "", 
                    ""
                }
            }
        );
        std::cout << "Configured a default Toolset" << std::endl;

        auto project = createProject(toolset.get());
        std::cout << "Created a Project" << std::endl;

        auto taskNode = project->createTask(felide::TargetAction::Build, context);
        std::cout << "Created a Task" << std::endl;

        auto visitor = felide::TaskNodeVisitor::create();

        visitor->visit(taskNode.get(), [](felide::Task *task) {
            if (task) {
                std::cout << task->toString() << std::endl;
                task->perform();
            } 
        });

        return 0;
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;

        return 1;
    }

    return 1001;
}

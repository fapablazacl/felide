//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//
//#include <felide/core/TreeNode.hpp>
//#include <felide/core/pom/Project.hpp>
//#include <felide/core/pom/ModuleTarget.hpp>
//#include <felide/core/pom/ModuleTargetType.hpp>
//#include <felide/core/pom/TargetAction.hpp>
//
//#include <felide/core/tasks/Task.hpp>
//#include <felide/core/tasks/TaskNodeVisitor.hpp>
//
//#include <felide/core/cpp/ModuleCompiler.hpp>
//#include <felide/core/cpp/ModuleLinker.hpp>
//#include <felide/core/cpp/ModuleToolset.hpp>
//
//#include <felide/core/FileTypeRegistry.hpp>
//
//#define XSTR(a) STR(a)
//#define STR(a) #a
//
//static std::unique_ptr<felide::Project> createProject(felide::Toolset *toolset) {
//    const std::string rootPath = XSTR(PROJECT_SOURCE_DIR);
//
//    std::cout << "Building project at \"" << rootPath << "\" ..." << std::endl;
//
//    auto project = felide::Project::create("felide", rootPath);
//
//    project->createTarget<felide::ModuleTarget>()
//        ->setType(felide::ModuleTargetType::Library)
//        ->setName("felide.core")
//        ->setPath("src/felide.core")
//        ->setToolset(toolset);
//
//    project->createTarget<felide::ModuleTarget>()
//        ->setType(felide::ModuleTargetType::Program)
//        ->setName("sandbox")
//        ->setPath("src/sandbox")
//        ->setToolset(toolset);
//
//    return project;
//}
//
//int main(int argc, char **argv) {
//    try {
//        const std::string rootPath = XSTR(PROJECT_SOURCE_DIR);
//
//        const felide::ActionContext context = {
//            {"${IncludeDirectory}", rootPath + "/src/felide.core"},
//            {"${LinkLibraries}", "-lstdc++ -lstdc++fs"}
//        };
//
//        auto toolset = felide::ModuleToolset::create (
//            ".felide/build/gcc",
//            {
//                felide::CompilerDescription {
//                    "gcc -std=c++17 -g -O0 -c ${InputFile} -o ${OutputFile} ${IncludeDirectory}",
//                    {".cpp", ".cxx", ".cc", ".c++"}, 
//                    ".obj",
//                    "/usr/local/Cellar/gcc/8.1.0/bin/",
//                    {
//                        {"${IncludeDirectory}", "-I"}
//                    }
//                }
//            }, {
//                felide::LinkerDescription {
//                    "gcc ${ObjectFiles} -o ${TargetName} ${LinkLibraries}",
//                    "", 
//                    ""
//                }
//            }
//        );
//        std::cout << "Configured a default Toolset" << std::endl;
//
//        auto project = createProject(toolset.get());
//        std::cout << "Created a Project" << std::endl;
//
//        auto taskNode = project->createTask(felide::TargetAction::Build, context);
//        std::cout << "Created a Build Task" << std::endl;
//
//        auto visitor = felide::TaskNodeVisitor::create();
//
//        visitor->visit(taskNode.get(), [](felide::Task *task) {
//            if (task) {
//                std::cout << task->toString() << std::endl;
//                task->perform();
//            } 
//        });
//
//        return 0;
//    } catch (const std::exception &exp) {
//        std::cout << exp.what() << std::endl;
//
//        return 1;
//    }
//
//    return 1001;
//}

int main() {
    return 0;
}

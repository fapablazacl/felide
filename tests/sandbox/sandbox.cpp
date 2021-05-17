//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//
//#include <Xenoide/core/TreeNode.hpp>
//#include <Xenoide/core/pom/Project.hpp>
//#include <Xenoide/core/pom/ModuleTarget.hpp>
//#include <Xenoide/core/pom/ModuleTargetType.hpp>
//#include <Xenoide/core/pom/TargetAction.hpp>
//
//#include <Xenoide/core/tasks/Task.hpp>
//#include <Xenoide/core/tasks/TaskNodeVisitor.hpp>
//
//#include <Xenoide/core/cpp/ModuleCompiler.hpp>
//#include <Xenoide/core/cpp/ModuleLinker.hpp>
//#include <Xenoide/core/cpp/ModuleToolset.hpp>
//
//#include <Xenoide/core/FileTypeRegistry.hpp>
//
//#define XSTR(a) STR(a)
//#define STR(a) #a
//
//static std::unique_ptr<Xenoide::Project> createProject(Xenoide::Toolset *toolset) {
//    const std::string rootPath = XSTR(PROJECT_SOURCE_DIR);
//
//    std::cout << "Building project at \"" << rootPath << "\" ..." << std::endl;
//
//    auto project = Xenoide::Project::create("Xenoide", rootPath);
//
//    project->createTarget<Xenoide::ModuleTarget>()
//        ->setType(Xenoide::ModuleTargetType::Library)
//        ->setName("Xenoide.core")
//        ->setPath("src/Xenoide.core")
//        ->setToolset(toolset);
//
//    project->createTarget<Xenoide::ModuleTarget>()
//        ->setType(Xenoide::ModuleTargetType::Program)
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
//        const Xenoide::ActionContext context = {
//            {"${IncludeDirectory}", rootPath + "/src/Xenoide.core"},
//            {"${LinkLibraries}", "-lstdc++ -lstdc++fs"}
//        };
//
//        auto toolset = Xenoide::ModuleToolset::create (
//            ".Xenoide/build/gcc",
//            {
//                Xenoide::CompilerDescription {
//                    "gcc -std=c++17 -g -O0 -c ${InputFile} -o ${OutputFile} ${IncludeDirectory}",
//                    {".cpp", ".cxx", ".cc", ".c++"}, 
//                    ".obj",
//                    "/usr/local/Cellar/gcc/8.1.0/bin/",
//                    {
//                        {"${IncludeDirectory}", "-I"}
//                    }
//                }
//            }, {
//                Xenoide::LinkerDescription {
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
//        auto taskNode = project->createTask(Xenoide::TargetAction::Build, context);
//        std::cout << "Created a Build Task" << std::endl;
//
//        auto visitor = Xenoide::TaskNodeVisitor::create();
//
//        visitor->visit(taskNode.get(), [](Xenoide::Task *task) {
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


#include "ProjectFactory.hpp"

#include <borc/core/Module.hpp>
#include <borc/core/Project.hpp>

namespace borc {
    std::unique_ptr<Project> ProjectFactory::createProject(const std::string &path) const {
        auto borcProject = std::make_unique<Project>("borc", path);

        Module *borcCoreModule = borcProject->addModule("borc.core", ModuleType::Library, "src/borc.core", {
            "Common.cpp",
            "Common.hpp",
            "BuildService.cpp",
            "BuildService.hpp",
            "RunService.cpp",
            "RunService.hpp",
            "Command.cpp",
            "Command.hpp",
            "CommandFactory.cpp",
            "CommandFactory.hpp",
            "SystemCommand.cpp",
            "SystemCommand.hpp",
            "ProcessCommand.cpp",
            "ProcessCommand.hpp",
            "Compiler.cpp",
            "Compiler.hpp",
            "Linker.cpp",
            "Linker.hpp",
            "Module.cpp",
            "Module.hpp",
            "Project.cpp",
            "Project.hpp",
            "win32/ProcessRedirector.cpp",
            "win32/ProcessRedirector.hpp"
        });

        Module *borcCliModule = borcProject->addModule("borc.cli", ModuleType::Executable, "src/borc.cli", {
            "Main.cpp"
        }, {borcCoreModule});

        return borcProject;
    }
}

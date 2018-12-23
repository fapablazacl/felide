
#include "Common.hpp"
#include "Module.hpp"
#include "Project.hpp"
#include "Compiler.hpp"
#include "Linker.hpp"
#include "BuildService.hpp"
#include "RunService.hpp"
#include "Command.hpp"
#include "CommandFactory.hpp"

namespace fs = std::filesystem;

#define XSTR(a) STR(a)
#define STR(a) #a

std::string getFullPath() {
    return XSTR(PROJECT_SOURCE_DIR);
}

int main(int argc, char **argv) {
    using namespace borc::model;

    const std::string fullPath = getFullPath();

    Project borcProject{"borc", fullPath};

    Module *borcCoreModule = borcProject.addModule("borc.core", ModuleType::Library, "src/borc.core", {
        "BuildService.hpp", 
        "BuildService.cpp",
        "Module.hpp", 
        "Module.cpp",
        "Project.hpp", 
        "Project.cpp",
        "Compiler.hpp", 
        "Compiler.cpp",
        "Linker.hpp", 
        "Linker.cpp"
    });

    Module *borcCliModule = borcProject.addModule("borc.cli", ModuleType::Executable, "src/borc.cli", {
        "Main.cpp"
    }, {borcCoreModule});

    // const std::string commandBase = "/usr/local/Cellar/gcc/8.2.0/bin/gcc-8";
    // const std::string commandBase = "gcc";

    // const Compiler compiler { commandBase, {"-c", "-o", "-g", "-O0"} };
    // const Linker linker { commandBase, {"-shared", "-o", "-l", "-L"} };

	const std::string commandBasePath = "C:\\Program Files(x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.16.27023\\bin\\Hostx64\\x64\\";
	const std::string commandCompiler = commandBasePath + "cl.exe";
	const std::string commandLinker = commandBasePath + "link.exe";

	CommandFactory commandFactory;

	const Compiler compiler { &commandFactory, "\"" + commandCompiler + "\"", {"/c", "", "", "/O0"} };
	const Linker linker { &commandFactory, commandLinker, {"/DLL", "", "/IMPLIB:", "/LIBPATH:"} };

    BuildService buildService {&compiler, &linker};
    buildService.buildProject(&borcProject);

    RunService runService {&compiler, &linker};
    runService.runModule(borcCliModule);

    return 0;
}

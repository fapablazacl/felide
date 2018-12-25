
#include "Common.hpp"
#include "Module.hpp"
#include "Project.hpp"
#include "Compiler.hpp"
#include "Linker.hpp"
#include "BuildService.hpp"
#include "RunService.hpp"
#include "Command.hpp"
#include "CommandFactory.hpp"

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

    Module *borcCliModule = borcProject.addModule("borc.cli", ModuleType::Executable, "src/borc.cli", {
        "Main.cpp"
    }, {borcCoreModule});

    // const std::string commandBase = "/usr/local/Cellar/gcc/8.2.0/bin/gcc-8";
    // const std::string commandBase = "gcc";

    // const Compiler compiler { commandBase, {"-c", "-o", "-g", "-O0"} };
    // const Linker linker { commandBase, {"-shared", "-o", "-l", "-L"} };

	const std::string basePath = "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.16.27023\\";
	const std::string commandBasePath = basePath + "bin\\Hostx64\\x64\\";
	const std::string commandCompiler = commandBasePath + "cl.exe";
	const std::string commandLinker = commandBasePath + "link.exe";

	const std::string standardIncludePath = basePath + "include";

	const std::string ucrtIncludePath = "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.17763.0\\ucrt";
	const std::string umIncludePath = "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.17763.0\\um";
	const std::string sharedIncludePath = "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.17763.0\\shared";

	CommandFactory commandFactory;

	const Compiler compiler {
		&commandFactory, 
		commandCompiler, 
		{ "/c", "/Fo", "/DEBUG:FULL", "/Od", "/I "},
		{ 
			{"/EHsc", "/std:c++17"}, 
			{ 
				"\"" + standardIncludePath + "\"", 
				"\"" + ucrtIncludePath + "\"",
				"\"" + umIncludePath + "\"",
				"\"" + sharedIncludePath + "\""
			}
		}
	};
	const Linker linker { &commandFactory, commandLinker, {"/DLL", "", "/IMPLIB:", "/LIBPATH:"} };

    BuildService buildService {&compiler, &linker};
    buildService.buildProject(&borcProject);

    RunService runService {&compiler, &linker};
    runService.runModule(borcCliModule);

    return 0;
}

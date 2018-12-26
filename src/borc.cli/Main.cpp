
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

namespace borc::model {
	class RunService;
	class BuildService;
	class ServiceFactory {
	public:
		virtual ~ServiceFactory() {}

		virtual BuildService createBuildService() = 0;

		virtual BuildService createRunService() = 0;

	private:
		std::vector<std::unique_ptr<Compiler>> compilers;
		std::vector<std::unique_ptr<Linker>> linkers;
	};

	class GNUServiceFactory : public ServiceFactory {

	}

	class MicrosoftServiceFactory : public ServiceFactory {
	public:
		MicrosoftServiceFactory(const std::string &basePath, const std::string &windowsKitPath) {
			// const std::string basePath = "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.16.27023\\";
			const std::string commandBasePath = basePath + "bin\\Hostx64\\x64\\";
			const std::string commandCompiler = commandBasePath + "cl.exe";
			const std::string commandLinker = commandBasePath + "link.exe";

			const std::string standardIncludePath = basePath + "include";

			// const std::string ucrtIncludePath = "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.17763.0\\ucrt";
			const std::string ucrtIncludePath = windowsKitPath + "Include\\10.0.17763.0\\ucrt";
			const std::string umIncludePath = windowsKitPath + "Include\\10.0.17763.0\\um";

			const std::string sharedIncludePath = windowsKitPath + "Include\\10.0.17763.0\\shared";

			CommandFactory commandFactory;

			CompilerSwitches compilerSwitches;
			compilerSwitches.compile = "/c";
			compilerSwitches.objectFileOutput = "/Fo";
			compilerSwitches.zeroOptimization = "/Od";
			compilerSwitches.includePath = "/I";
			compilerSwitches.includeDebug = "/DEBUG:FULL";

			this->compiler = std::make_unique<Compiler> (
				&commandFactory, 
				commandCompiler, 
				compilerSwitches,
				{ 
					{"/EHsc", "/std:c++17"}, 
					{ 
						"\"" + standardIncludePath + "\"", 
						"\"" + ucrtIncludePath + "\"",
						"\"" + umIncludePath + "\"",
						"\"" + sharedIncludePath + "\""
					}
				}
			);
		}

		virtual ~MicrosoftServiceFactory() {}

		virtual BuildService createBuildService() {
			return {compiler.get(), linker.get()};
		}

		virtual RunService createRunService() {
			return {compiler.get(), linker.get()};
		}


	private:
		std::unique_ptr<Compiler> compiler;
		std::unique_ptr<Linker> linker;

		CommandFactory commandFactory;
	};
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



	LinkerSwitches linkerSwitches;
	linkerSwitches.buildSharedLibrary = "/DLL";
	linkerSwitches.moduleOutput = "/OUT:";
	linkerSwitches.importLibrary = "/IMPLIB:";
	linkerSwitches.importLibraryPath = "/LIBPATH:";

	LinkerConfiguration linkerConfiguration;
	linkerConfiguration.importLibraryPaths = {
		"\"" + basePath + "lib\\x64" + "\"",
		"\"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.17763.0\\um\\x64\"",
		"\"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.17763.0\\ucrt\\x64\""
	};

	linkerConfiguration.importLibraries = {
		"AdvAPI32"
	};

	const Linker linker { &commandFactory, commandLinker, linkerSwitches, linkerConfiguration };

    BuildService buildService {&compiler, &linker};
    buildService.buildProject(&borcProject);

    RunService runService {&compiler, &linker};
    runService.runModule(borcCliModule);

    return 0;
}

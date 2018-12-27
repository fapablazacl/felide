
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

		virtual RunService createRunService() = 0;

	private:
		std::vector<std::unique_ptr<Compiler>> compilers;
		std::vector<std::unique_ptr<Linker>> linkers;
	};

	class GCCServiceFactory : public ServiceFactory {
	public:
		explicit GCCServiceFactory(const std::string &commandBase) {
			this->commandBase = commandBase;

			this->compiler = this->createCompiler();
			this->linker = this->createLinker();
		}

		virtual BuildService createBuildService() override {
			return BuildService{ compiler.get(), linker.get() };
		}

		virtual RunService createRunService() override {
			return RunService{ compiler.get(), linker.get() };
		}
	private:
		std::unique_ptr<Compiler> createCompiler() {
			CompilerSwitches switches;
			switches.compile = "-c";
			switches.includeDebug = "-g";
			switches.zeroOptimization = "-O0";
			switches.objectFileOutput = "-o";
			switches.includePath = "-I";

			CompilerConfiguration configuration;

			return std::make_unique<Compiler> (&commandFactory, commandBase, switches, configuration);
		}

		std::unique_ptr<Linker> createLinker() {
			LinkerSwitches switches;
			switches.buildSharedLibrary = "-shared";
			switches.moduleOutput = "-o";
			switches.importLibrary = "-l";
			switches.importLibraryPath = "-L";

			LinkerConfiguration configuration;
			configuration.importLibraries = {
				"stdc++", "stdc++fs"
			};

			return std::make_unique<Linker> (&commandFactory, commandBase, switches, configuration);
		}

	private:
		std::string commandBase;
		std::unique_ptr<Compiler> compiler;
		std::unique_ptr<Linker> linker;

		CommandFactory commandFactory;
	};

	class VCServiceFactory : public ServiceFactory {
	public:
		VCServiceFactory(const std::string &installationPath, const std::string &windowsKitPath) {
			// const std::string installationPath = "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.16.27023\\";
			const std::string commandBasePath = installationPath + "bin\\Hostx64\\x64\\";
			const std::string compilerCommand = commandBasePath + "cl.exe";
			const std::string linkerCommand = commandBasePath + "link.exe";

			this->compiler = this->createCompiler(compilerCommand, installationPath, windowsKitPath);
			this->linker = this->createLinker(linkerCommand, installationPath, windowsKitPath);
		}

		virtual ~VCServiceFactory() {}

		virtual BuildService createBuildService() override {
			return BuildService{ compiler.get(), linker.get() };
		}

		virtual RunService createRunService() override {
			return RunService{ compiler.get(), linker.get() };
		}

	private:
		std::unique_ptr<Compiler> createCompiler(const std::string &compilerCommand, const std::string &installationPath, const std::string &windowsKitPath) {
			const std::string standardIncludePath = installationPath + "include";

			// const std::string ucrtIncludePath = "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.17763.0\\ucrt";
			const std::string ucrtIncludePath = windowsKitPath + "Include\\10.0.17763.0\\ucrt";
			const std::string umIncludePath = windowsKitPath + "Include\\10.0.17763.0\\um";

			const std::string sharedIncludePath = windowsKitPath + "Include\\10.0.17763.0\\shared";

			CompilerSwitches compilerSwitches;
			compilerSwitches.compile = "/c";
			compilerSwitches.objectFileOutput = "/Fo";
			compilerSwitches.zeroOptimization = "/Od";
			compilerSwitches.includePath = "/I";
			compilerSwitches.includeDebug = "/DEBUG:FULL";

			return std::make_unique<Compiler> (
				&commandFactory, compilerCommand, compilerSwitches,
				CompilerConfiguration { 
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

		std::unique_ptr<Linker> createLinker(const std::string &linkerCommand, const std::string &installationPath, const std::string &windowsKitPath) {
			LinkerSwitches linkerSwitches;
			linkerSwitches.buildSharedLibrary = "/DLL";
			linkerSwitches.moduleOutput = "/OUT:";
			linkerSwitches.importLibrary = "/IMPLIB:";
			linkerSwitches.importLibraryPath = "/LIBPATH:";

			LinkerConfiguration linkerConfiguration;
			linkerConfiguration.importLibraryPaths = {
				"\"" + installationPath + "lib\\x64" + "\"",
				"\"" + windowsKitPath + "Lib\\10.0.17763.0\\um\\x64" + "\"",
				"\"" + windowsKitPath + "Lib\\10.0.17763.0\\ucrt\\x64" + "\""
				// "\"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.17763.0\\um\\x64\"",
				// "\"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.17763.0\\ucrt\\x64\""
			};

			linkerConfiguration.importLibraries = { "AdvAPI32" };

			return std::make_unique<Linker>(
				&commandFactory, 
				linkerCommand,
				linkerSwitches, 
				linkerConfiguration
			);
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

	// auto serviceFactory = GCCServiceFactory("/usr/local/Cellar/gcc/8.2.0/bin/gcc-8");
	auto serviceFactory = GCCServiceFactory("gcc");

    BuildService buildService = serviceFactory.createBuildService();
    buildService.buildProject(&borcProject);

    RunService runService = serviceFactory.createRunService();
    runService.runModule(borcCliModule);

    return 0;
}

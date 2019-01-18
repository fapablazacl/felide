
#include <borc/core/Common.hpp>
#include <borc/core/Source.hpp>
#include <borc/core/Module.hpp>
#include <borc/core/Project.hpp>
#include <borc/core/Compiler.hpp>
#include <borc/core/Linker.hpp>
#include <borc/core/BuildService.hpp>
#include <borc/core/RunService.hpp>
#include <borc/core/Command.hpp>
#include <borc/core/CommandFactory.hpp>

#include <borc/core/ServiceFactoryVC.hpp>
#include <borc/core/Toolchain.hpp>
#include <borc/dag/Node.hpp>
#include <borc/dag/NodeRepository.hpp>
#include <borc/dag/BuildGraphGenerator.hpp>

#define XSTR(a) STR(a)
#define STR(a) #a

std::string getFullPath() {
    return XSTR(PROJECT_SOURCE_DIR);
}

int main(int argc, char **argv) {
    using namespace borc;

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
	
	SourceType cppSourceType {"*.cpp", "*.cxx", "*.c++", "*.cc"};

	ServiceFactoryVC serviceFactory {
		"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.16.27023\\",
		"C:\\Program Files (x86)\\Windows Kits\\10\\"
	};

	Toolchain cppToolchain {
		{{cppSourceType, serviceFactory.getCompiler()}},
		serviceFactory.getLinker()
	};

	NodeRepository nodeRepository;
	BuildGraphGenerator buildGraphGenerator{ &nodeRepository, &cppToolchain };

	auto borcCliModuleNode = buildGraphGenerator.generateGraph(borcCliModule);
	auto borcCoreModuleNode = buildGraphGenerator.generateGraph(borcCoreModule);

	// auto serviceFactory = GCCServiceFactory("/usr/local/Cellar/gcc/8.2.0/bin/gcc-8");
	// auto serviceFactory = GCCServiceFactory("gcc");

    // BuildService buildService = serviceFactory.createBuildService();
    // buildService.buildProject(&borcProject);

    // RunService runService = serviceFactory.createRunService();
    // runService.runModule(borcCliModule);

    return 0;
}


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

#include <algorithm>
#include <vector>
#include <map>

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

		virtual const Compiler* getCompiler() const = 0;

		virtual const Linker* getLinker() const = 0;

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

		virtual const Compiler* getCompiler() const override {
			return compiler.get();
		}

		virtual const Linker* getLinker() const override {
			return linker.get();
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

		virtual const Compiler* getCompiler() const override {
			return compiler.get();
		}

		virtual const Linker* getLinker() const override {
			return linker.get();
		}

	private:
		std::unique_ptr<Compiler> createCompiler(const std::string &compilerCommand, const std::string &installationPath, const std::string &windowsKitPath) {
			const std::string standardIncludePath = installationPath + "include";
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

#include <set>

namespace borc::model {
	struct SourceType {
		SourceType(const std::initializer_list<std::string> &wildcards) {
			this->wildcards = wildcards;
		}

		std::set<std::string> wildcards;

		bool match(const std::filesystem::path &filePath) const {
			const std::string ext = "*" + filePath.extension().string();

			auto it = std::find(wildcards.begin(), wildcards.end(), ext);

			return it != wildcards.end();
		}
	};

	class Toolchain {
	public:
		explicit Toolchain(const std::vector<std::pair<SourceType, const Compiler*>> &compilers, const Linker *linker) {
			this->compilers = compilers;
			this->linker = linker;
		}

		~Toolchain() {}

		const Compiler* selectCompiler(const Source *source) const {
			for (auto &pair : compilers) {
				if (pair.first.match(source->getFilePath())) {
					return pair.second;
				}
			}

			return nullptr;
		}

		const Linker* selectLinker(const Module *module) const {
			return linker;
		}

	private:
		std::vector<std::pair<SourceType, const Compiler*>> compilers;
		const Linker *linker = nullptr;
	};
}

namespace borc::dag {
	class Node {
	public:
		explicit Node(const std::string &filePath) {
			this->filePath = filePath;
		}

		~Node() {}

		void addDependency(Node *dependency) {
			dependencies.push_back(dependency);
		}

		void removeDependency(Node *child) {
			auto location = std::find_if(dependencies.begin(), dependencies.end(), [child](auto node) {
				return node == child;
			});

			if (location != dependencies.end()) {
				dependencies.erase(location);
			}
		}

		std::vector<Node*> getDependencies() const {
			return dependencies;
		}

		std::string getFilePath() const {
			return filePath;
		}

	private:
		std::string filePath;
		std::vector<Node*> dependencies;
	};

	class NodeRepository {
	public:
		~NodeRepository() {}

		Node* getNode(const std::string &filePath) const {
			auto it = nodeMap.find(filePath);

			if (it != nodeMap.end()) {
				return it->second.get();
			} else {
				auto nodePtr = std::make_unique<Node>(filePath);
				auto node = nodePtr.get();

				nodeMap[filePath] = std::move(nodePtr);

				return node;
			}
		}

	private:
		mutable std::map<std::string, std::unique_ptr<Node>> nodeMap;
	};

	class BuildGraphGenerator {
	public:
		explicit BuildGraphGenerator(NodeRepository *nodeRepository, const borc::model::Toolchain *toolchain) {
			this->nodeRepository = nodeRepository;
			this->toolchain = toolchain;
		}

		Node* generateGraph(const borc::model::Module *module) const {
			const std::string moduleFilePath = module->getOutputFilePath().string();
			Node *moduleNode = nodeRepository->getNode(moduleFilePath);

			for (const borc::model::Source *source: module->getSources()) {
				Node *objectNode = this->generateGraph(source);

				if (!objectNode) {
					continue;
				}

				moduleNode->addDependency(objectNode);
			}

			return moduleNode;
		}

	private:
		Node* generateGraph(const borc::model::Source *source) const {
			const auto compiler = this->toolchain->selectCompiler(source);

			if (!compiler) {
				return nullptr;
			}

			const auto objectFilePath = compiler->getObjectFilePath(source);
			const auto objectNode = nodeRepository->getNode(objectFilePath.string());

			const auto sourceFilePath = source->getFilePath();
			const auto sourceNode = nodeRepository->getNode(sourceFilePath.string());

			objectNode->addDependency(sourceNode);

			// TODO: Compute header dependency information

			return objectNode;
		}

	private:
		NodeRepository *nodeRepository = nullptr;
		const borc::model::Toolchain *toolchain = nullptr;
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
	
	SourceType cppSourceType {"*.cpp", "*.cxx", "*.c++", "*.cc"};

	VCServiceFactory serviceFactory {
		"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.16.27023\\",
		"C:\\Program Files (x86)\\Windows Kits\\10\\"
	};

	Toolchain cppToolchain {
		{{cppSourceType, serviceFactory.getCompiler()}},
		serviceFactory.getLinker()
	};

	borc::dag::NodeRepository nodeRepository;
	borc::dag::BuildGraphGenerator buildGraphGenerator{ &nodeRepository, &cppToolchain };

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

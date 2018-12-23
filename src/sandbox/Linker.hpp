
#ifndef __BORC_MODEL_BUILDLINKER_HPP__
#define __BORC_MODEL_BUILDLINKER_HPP__

namespace borc::model {
	struct LinkerSwitches {
		std::string buildSharedLibrary;
		std::string moduleOutput;
		std::string importLibrary;
		std::string importLibraryPath;
	};

	class Linker {
	public:
		explicit Linker(CommandFactory *commandFactory, const std::string &commandPath, const LinkerSwitches &switches) {
			this->commandFactory = commandFactory;
			this->commandPath = commandPath;
			this->switches = switches;
		}

		std::string link(const Project *project, const Module *module, const std::vector<std::string> &objectFiles) const {
			std::cout << "Linking " << toString(module->getType()) << " module " << module->getName() << " ..." << std::endl;

			const std::string outputModuleFilePath = module->computeOutputPath().string();
			const auto librariesOptions = this->computeImportLibrariesOptions(project, module);

			Command *command = commandFactory->createCommand(commandPath);

			if (module->getType() == ModuleType::Library) {
				command->addOption(switches.buildSharedLibrary);
			}

			command->addOptionRange(objectFiles.begin(), objectFiles.end());
			command->addOptionRange(librariesOptions.begin(), librariesOptions.end());
			command->addOption(switches.moduleOutput + outputModuleFilePath);

			return outputModuleFilePath;
		}

	private:
		std::vector<std::string> computeImportLibrariesOptions(const Project *project, const Module *module) const {
			std::vector<std::string> options = {
				"-lstdc++", "-lstdc++fs"
			};

			const auto dependencies = module->getDependencies();

			for (const Module *dependency : dependencies) {
				const std::string importLibrary = dependency->getName();
				const std::string importLibraryDir = dependency->computeOutputPath().string();

				options.push_back(switches.importLibrary + importLibrary);
				options.push_back(switches.importLibraryPath + importLibraryDir);
			}

			return options;
		}

	private:
		CommandFactory *commandFactory = nullptr;
		std::string commandPath;
		LinkerSwitches switches;
	};
}

#endif

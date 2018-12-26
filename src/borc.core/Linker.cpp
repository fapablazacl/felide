
#include "Linker.hpp"

#include "Command.hpp"
#include "CommandFactory.hpp"
#include "Project.hpp"
#include "Module.hpp"
#include <iostream>

namespace borc::model {
	Linker::Linker(CommandFactory *commandFactory, const std::string &commandPath, const LinkerSwitches &switches, const LinkerConfiguration &configuration) {
		this->commandFactory = commandFactory;
		this->commandPath = commandPath;
		this->switches = switches;
		this->configuration = configuration;
	}

	std::string Linker::link(const Project *project, const Module *module, const std::vector<std::string> &objectFiles) const {
		std::cout << "Linking " << toString(module->getType()) << " module " << module->getName() << " ..." << std::endl;

		const std::string outputModuleFilePath = module->computeOutputPathFile().string();
		const auto librariesOptions = this->computeImportLibrariesOptions(project, module);

		Command *command = commandFactory->createCommand(commandPath);

		if (module->getType() == ModuleType::Library) {
			command->addOption(switches.buildSharedLibrary);
		}

		command->addOptionRange(librariesOptions.begin(), librariesOptions.end());
		command->addOption(switches.moduleOutput + outputModuleFilePath);
		command->addOptionRange(std::begin(objectFiles), std::end(objectFiles));
		command->execute();

		return outputModuleFilePath;
	}

	std::vector<std::string> Linker::computeImportLibraryPathOptions(const std::vector<std::string> &paths) const {
		std::vector<std::string> options;

		for (const std::string &path : paths) {
			const std::string option = switches.importLibraryPath + path;
			options.push_back(option);
		}

		return options;
	}

	std::vector<std::string> Linker::computeImportLibrariesOptions(const Project *project, const Module *module) const {
		std::vector<std::string> options = this->computeImportLibraryPathOptions(configuration.importLibraryPaths);

		for (const std::string &importLibrary : configuration.importLibraries) {
			options.push_back(/*switches.importLibrary + */importLibrary);
		}

		const auto dependencies = module->getDependencies();

		for (const Module *dependency : dependencies) {
			const std::string importLibrary = dependency->getName();
			const std::string importLibraryDir = dependency->computeOutputPath().string();

			options.push_back(/*switches.importLibrary + */importLibrary);
			options.push_back(switches.importLibraryPath + importLibraryDir);
		}

		return options;
	}
}

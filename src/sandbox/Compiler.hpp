
#ifndef __BORC_MODEL_BUILDCOMPILER_HPP__
#define __BORC_MODEL_BUILDCOMPILER_HPP__

#include "CommandFactory.hpp"
#include "Project.hpp"
#include "Module.hpp"
#include <iostream>
#include <filesystem>

namespace borc::model {
	struct CompilerSwitches {
		std::string compile;
		std::string objectFileOutput;
		std::string includeDebug;
		std::string zeroOptimization;
	};

	class Compiler {
	public:
		explicit Compiler(CommandFactory *commandFactory, const std::string &commandPath, const CompilerSwitches &switches) {
			this->commandFactory = commandFactory;
			this->commandPath = commandPath;
			this->switches = switches;
		}

		std::string compile(const Project *project, const Module *module, const std::string &file) const {
			const std::filesystem::path sourceFilePath = module->computeFullPath() / std::filesystem::path(file);
			const std::filesystem::path objectFilePath = module->computeOutputPath() / std::filesystem::path(file);

			std::cout << "    " << file << " ..." << std::endl;

			Command *command = commandFactory->createCommand(
				commandPath, {
					switches.zeroOptimization,
					switches.includeDebug,
					switches.compile,
					sourceFilePath.string(),
					switches.objectFileOutput + objectFilePath.string(),
				}
			);

			command->execute();

			return objectFilePath.string();
		}

	private:
		CommandFactory *commandFactory = nullptr;
		std::string commandPath;
		CompilerSwitches switches;
	};
}

#endif

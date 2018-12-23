
#include "Compiler.hpp"

#include "Command.hpp"
#include "CommandFactory.hpp"
#include "Project.hpp"
#include "Module.hpp"

namespace borc::model {
	Compiler::Compiler(CommandFactory *commandFactory, const std::string &commandPath, const CompilerSwitches &switches) {
		this->commandFactory = commandFactory;
		this->commandPath = commandPath;
		this->switches = switches;
	}

	std::string Compiler::compile(const Project *project, const Module *module, const std::string &file) const {
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
}

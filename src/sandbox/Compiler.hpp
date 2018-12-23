
#ifndef __BORC_MODEL_BUILDCOMPILER_HPP__
#define __BORC_MODEL_BUILDCOMPILER_HPP__

#include <iostream>
#include <filesystem>

namespace borc::model {
	class Project;
	class Module;
	class CommandFactory;

	struct CompilerSwitches {
		std::string compile;
		std::string objectFileOutput;
		std::string includeDebug;
		std::string zeroOptimization;
	};

	class Compiler {
	public:
		explicit Compiler(CommandFactory *commandFactory, const std::string &commandPath, const CompilerSwitches &switches);

		std::string compile(const Project *project, const Module *module, const std::string &file) const;

	private:
		CommandFactory *commandFactory = nullptr;
		std::string commandPath;
		CompilerSwitches switches;
	};
}

#endif

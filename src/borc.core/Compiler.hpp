
#ifndef __BORC_MODEL_BUILDCOMPILER_HPP__
#define __BORC_MODEL_BUILDCOMPILER_HPP__

#include <vector>
#include <iostream>
#include <filesystem>
#include "Predef.h"

namespace borc::model {
	class Project;
	class Module;
	class CommandFactory;

	struct CompilerSwitches {
		std::string compile;
		std::string objectFileOutput;
		std::string includeDebug;
		std::string zeroOptimization;
		std::string includePath;

		CompilerSwitches() {}
	};

	//! Compiler default configuration
	struct CompilerConfiguration {
		std::vector<std::string> flags;
		std::vector<std::string> systemIncludePaths;
	};

	struct CompileOptions {
		std::vector<std::string> includePaths;
	};

	class Compiler {
	public:
		explicit Compiler(
			CommandFactory *commandFactory, 
			const std::string &commandPath, 
			const CompilerSwitches &switches, 
			const CompilerConfiguration &configuration
		);

		std::string compile(const Project *project, const Module *module, const std::string &file, const CompileOptions &options) const;

	private:
		CommandFactory *commandFactory = nullptr;
		std::string commandPath;
		CompilerSwitches switches;
		CompilerConfiguration configuration;
	};
}

#endif

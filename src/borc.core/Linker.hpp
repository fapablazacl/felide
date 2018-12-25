
#ifndef __BORC_MODEL_LINKER_HPP__
#define __BORC_MODEL_LINKER_HPP__

#include <string>
#include <vector>

namespace borc::model {
	class CommandFactory;
	class Project;
	class Module;

	struct LinkerSwitches {
		std::string buildSharedLibrary;
		std::string moduleOutput;
		std::string importLibrary;
		std::string importLibraryPath;
	};

	struct LinkerConfiguration {
		std::vector<std::string> importLibraries;
	};

	class Linker {
	public:
		explicit Linker(CommandFactory *commandFactory, const std::string &commandPath, const LinkerSwitches &switches);

		std::string link(const Project *project, const Module *module, const std::vector<std::string> &objectFiles) const;

	private:
		std::vector<std::string> computeImportLibrariesOptions(const Project *project, const Module *module) const;

	private:
		CommandFactory *commandFactory = nullptr;
		std::string commandPath;
		LinkerSwitches switches;
	};
}

#endif

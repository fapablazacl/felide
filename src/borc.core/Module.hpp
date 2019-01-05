
#ifndef __BORC_MODEL_MODULE_HPP__
#define __BORC_MODEL_MODULE_HPP__

#include <string>
#include <vector>
#include <filesystem>
#include "Predef.h"

namespace borc::model {
	class Project;

	enum class ModuleType {
		Library,
		Executable
	};

	inline std::string toString(const ModuleType type) {
		switch (type) {
		case ModuleType::Executable:
			return "executable";

		case ModuleType::Library:
			return "library";

		default:
			return "<unknown ModuleType>";
		}
	}

	class Project;
	class Source;
	class Module {
	public:
		Module(Project *parent, const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files, const std::vector<Module*> &dependencies);

		~Module();

		std::string getName() const;

		std::string getPartialPath() const;

		std::vector<std::string> getFiles() const;

		std::vector<Source*> getSources() const;

		ModuleType getType() const;

		const Project *getParentProject() const;

		std::vector<Module*> getDependencies() const;

		std::filesystem::path getOutputPath() const;

		std::filesystem::path getPath() const;

		std::filesystem::path getOutputFilePath() const;

	private:
		//! parent project of the module
		Project *parentProject = nullptr;

		//! name of the target
		std::string name;

		//! the type of the module
		ModuleType type = ModuleType::Executable;

		//! relative path to the parent project
		std::string partialPath;

		//! list of files that compose the module
		std::vector<std::string> files;

		//! list of module libraries that this module depends on
		std::vector<Module*> dependencies;

		std::vector<std::unique_ptr<Source>> sources;
	};
}

#endif

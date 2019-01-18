
#ifndef __BORC_MODEL_PROJECT_HPP__
#define __BORC_MODEL_PROJECT_HPP__

#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include "Predef.h"

namespace borc {

	enum class ModuleType;
	class Module;
	class Project {
	public:
		Project(const std::string &name, const std::string &fullPath);

		Module* addModule(const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files);

		Module* addModule(const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files, const std::vector<Module*> &dependencies);

		std::string getName() const;

		std::filesystem::path getFullPath() const;

		std::vector<const Module*> getModules() const;

		std::filesystem::path computeOutputPath() const;

	private:
		//! The name of the project
		std::string name;

		//! The full path to the project directory
		std::string fullPath;

		//! The list of software modules this project has
		std::vector<std::unique_ptr<Module>> modules;
	};
}

#endif

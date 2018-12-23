
#ifndef __BORC_MODEL_MODULE_HPP__
#define __BORC_MODEL_MODULE_HPP__

#include <string>
#include <vector>
#include <filesystem>

// TODO: Trasladar cabecera en la implementacion del modulo
#include "Project.hpp"

namespace borc::model {
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
	class Module {
	public:
		Module(Project *parent, const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files, const std::vector<Module*> &dependencies) {
			this->parentProject = parent;
			this->name = name;
			this->type = type;
			this->path = path;
			this->files = files;
			this->dependencies = dependencies;
		}

		std::string getName() const {
			return name;
		}

		std::string getPath() const {
			return path;
		}

		std::vector<std::string> getFiles() const {
			return files;
		}

		ModuleType getType() const {
			return type;
		}

		const Project *getParentProject() const {
			return parentProject;
		}

		std::vector<Module*> getDependencies() const {
			return dependencies;
		}

		std::filesystem::path computeOutputPath() const {
			return this->parentProject->computeOutputPath() / this->getPath();
		}

		std::filesystem::path computeFullPath() const {
			return this->parentProject->getFullPath() / this->getPath();
		}

		std::filesystem::path computeOutputPathFile() const {
			std::string moduleFileName = this->getName();

			if (this->getType() == ModuleType::Library) {
				// moduleFileName = "lib" + module->getName() + ".dylib";
				// moduleFileName = "lib" + moduleFileName + ".so";
				moduleFileName = moduleFileName + ".dll";
			}

			return this->computeOutputPath() / std::filesystem::path(moduleFileName);
		}

	private:
		//! parent project of the module
		Project *parentProject = nullptr;

		//! name of the target
		std::string name;

		//! the type of the module
		ModuleType type = ModuleType::Executable;

		//! relative path to the parent project
		std::string path;

		//! list of files that compose the module
		std::vector<std::string> files;

		//! list of module libraries that this module depends on
		std::vector<Module*> dependencies;
	};
}

#endif

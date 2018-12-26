
#include "Module.hpp"
#include "Project.hpp"

namespace borc::model {
	Module::Module(Project *parent, const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files, const std::vector<Module*> &dependencies) {
		this->parentProject = parent;
		this->name = name;
		this->type = type;
		this->path = path;
		this->files = files;
		this->dependencies = dependencies;
	}

	std::string Module::getName() const {
		return name;
	}

	std::string Module::getPath() const {
		return path;
	}

	std::vector<std::string> Module::getFiles() const {
		return files;
	}

	ModuleType Module::getType() const {
		return type;
	}

	const Project *Module::getParentProject() const {
		return parentProject;
	}

	std::vector<Module*> Module::getDependencies() const {
		return dependencies;
	}

	std::filesystem::path Module::computeOutputPath() const {
		return this->parentProject->computeOutputPath() / this->getPath();
	}

	std::filesystem::path Module::computeFullPath() const {
		return this->parentProject->getFullPath() / this->getPath();
	}

	std::filesystem::path Module::computeOutputPathFile() const {
		std::string moduleFileName = this->getName();

		if (this->getType() == ModuleType::Library) {
			// moduleFileName = "lib" + module->getName() + ".dylib";
			// moduleFileName = "lib" + moduleFileName + ".so";
			moduleFileName = moduleFileName + ".dll";
		} else {
			// TODO: Add check for OS-dependent names and suffixes
			moduleFileName = moduleFileName + ".exe";
		}

		return this->computeOutputPath() / std::filesystem::path(moduleFileName);
	}
}

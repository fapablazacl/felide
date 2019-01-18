
#include "Project.hpp"
#include "Module.hpp"

namespace borc {
	Project::Project(const std::string &name, const std::string &fullPath) {
		this->name = name;
		this->fullPath = fullPath;
	}

	Module* Project::addModule(const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files) {
		return this->addModule(name, type, path, files, {});
	}

	Module* Project::addModule(const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files, const std::vector<Module*> &dependencies) {
		auto module = new Module(this, name, type, path, files, dependencies);

		modules.emplace_back(module);

		return module;
	}

	std::string Project::getName() const {
		return name;
	}

	std::filesystem::path Project::getFullPath() const {
		return std::filesystem::path(fullPath);
	}

	std::vector<const Module*> Project::getModules() const {
		std::vector<const Module*> modules;

		for (const auto &module : this->modules) {
			modules.push_back(module.get());
		}

		return modules;
	}

	std::filesystem::path Project::computeOutputPath() const {
		return std::filesystem::path(this->getFullPath()) / std::filesystem::path(".borc");
	}
}

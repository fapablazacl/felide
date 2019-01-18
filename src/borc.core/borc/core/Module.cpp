
#include "Module.hpp"
#include "Project.hpp"
#include "Source.hpp"

#include <algorithm>

namespace borc {
	Module::Module(Project *parent, const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files, const std::vector<Module*> &dependencies) {
		this->parentProject = parent;
		this->name = name;
		this->type = type;
		this->partialPath = path;
		this->files = files;
		this->dependencies = dependencies;

		std::transform(files.begin(), files.end(), std::back_inserter(sources), [this](const auto& file) {
			return std::make_unique<Source>(file, this);
		});
	}

	Module::~Module() {}

	std::string Module::getName() const {
		return name;
	}

	std::string Module::getPartialPath() const {
		return partialPath;
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

	std::filesystem::path Module::getOutputPath() const {
		return this->parentProject->computeOutputPath() / this->getPartialPath();
	}

	std::filesystem::path Module::getPath() const {
		return this->parentProject->getFullPath() / this->getPartialPath();
	}

	std::filesystem::path Module::getOutputFilePath() const {
		std::string moduleFileName = this->getName();

		if (this->getType() == ModuleType::Library) {
			// moduleFileName = "lib" + module->getName() + ".dylib";
			// moduleFileName = "lib" + moduleFileName + ".so";
			moduleFileName = moduleFileName + ".dll";
		} else {
			// TODO: Add check for OS-dependent names and suffixes
			moduleFileName = moduleFileName + ".exe";
		}

		return this->getOutputPath() / std::filesystem::path(moduleFileName);
	}

	std::vector<Source*> Module::getSources() const {
		std::vector<Source*> sourcePointers;

		std::transform(sources.begin(), sources.end(), std::back_inserter(sourcePointers), [](auto &source) {
			return source.get();
		});

		return sourcePointers;
	}
}

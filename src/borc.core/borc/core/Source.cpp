
#include "Source.hpp"
#include "Module.hpp"

#include <cassert>
#include <filesystem>

namespace borc::model {
	Source::Source(const std::filesystem::path &partialFilePath, const Module *parentModule) {
		this->parentModule = parentModule;
		this->partialFilePath = partialFilePath;
	}

	const Module* Source::getParentModule() const {
		return parentModule;
	}

	std::filesystem::path Source::getFilePath() const {
		return parentModule->getPath() / partialFilePath;
	}

	std::filesystem::path Source::getPartialFilePath() const {
		return partialFilePath;
	}
}

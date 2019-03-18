
#include "Source.hpp"
#include "Module.hpp"

#include <cassert>
#include <boost/filesystem.hpp>

namespace borc {
	Source::Source(const boost::filesystem::path &partialFilePath, const Module *parentModule) {
		this->parentModule = parentModule;
		this->partialFilePath = partialFilePath;
	}

	const Module* Source::getParentModule() const {
		return parentModule;
	}

	boost::filesystem::path Source::getFilePath() const {
		return parentModule->getPath() / partialFilePath;
	}

	boost::filesystem::path Source::getPartialFilePath() const {
		return partialFilePath;
	}
}

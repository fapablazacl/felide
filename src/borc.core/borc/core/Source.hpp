
#ifndef __BORC_MODEL_SOURCE_HPP__
#define __BORC_MODEL_SOURCE_HPP__

#include <string>
#include <vector>
#include <filesystem>
#include "Predef.h"

namespace borc::model {
	class AbstractSource {
	public:
		virtual ~AbstractSource() {}

		virtual std::filesystem::path getFilePath() const = 0;
	};

	class Module;
	class Source : public AbstractSource {
	public:
		explicit Source(const std::filesystem::path &partialFilePath, const Module *parentModule);

		const Module* getParentModule() const;

		virtual std::filesystem::path getFilePath() const override;

		std::filesystem::path getPartialFilePath() const;

	private:
		std::filesystem::path partialFilePath;
		const Module *parentModule = nullptr;
	};
}

#endif

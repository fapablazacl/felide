
#ifndef __BORC_MODEL_SOURCE_HPP__
#define __BORC_MODEL_SOURCE_HPP__

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "Predef.h"

namespace borc {
	class AbstractSource {
	public:
		virtual ~AbstractSource() {}

		virtual boost::filesystem::path getFilePath() const = 0;
	};

	class Module;
	class Source : public AbstractSource {
	public:
		explicit Source(const boost::filesystem::path &partialFilePath, const Module *parentModule);

		const Module* getParentModule() const;

		virtual boost::filesystem::path getFilePath() const override;

		boost::filesystem::path getPartialFilePath() const;

	private:
		boost::filesystem::path partialFilePath;
		const Module *parentModule = nullptr;
	};
}

#endif

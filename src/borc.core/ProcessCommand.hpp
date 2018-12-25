
#ifndef __BORC_MODEL_PROCESSCOMMAND_HPP__
#define __BORC_MODEL_PROCESSCOMMAND_HPP__

#include "Command.hpp"
#include <string>
#include <vector>

namespace borc::model {
	class ProcessCommand : public Command {
	public:
		explicit ProcessCommand(const std::string &base);

		explicit ProcessCommand(const std::string &base, const std::vector<std::string> &options);

		virtual void execute() override;

		virtual void addOption(const std::string &option) override;

	private:
		const std::string _base;
		std::vector<std::string> _options;
	};
}

#endif

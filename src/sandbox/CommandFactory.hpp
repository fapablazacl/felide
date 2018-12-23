
#ifndef __BORC_MODEL_COMMANDFACTORY_HPP__
#define __BORC_MODEL_COMMANDFACTORY_HPP__

#include "SystemCommand.hpp"

namespace borc::model {
	class CommandFactory {
	public:
		Command* createCommand(const std::string &base, const std::vector<std::string> &options = {}) {
			auto command = new SystemCommand(base, options);

			_cachedCommands.emplace_back(command);

			return command;
		}

	private:
		std::vector<std::unique_ptr<Command>> _cachedCommands;
	};
}

#endif

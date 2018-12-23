
#ifndef __BORC_MODEL_SYSTEMCOMMAND_HPP__
#define __BORC_MODEL_SYSTEMCOMMAND_HPP__

#include "Command.hpp"
#include <string>
#include <vector>

namespace borc::model {
	class SystemCommand : public Command {
	public:
		explicit SystemCommand(const std::string &base)
			: _base(base) {}

		explicit SystemCommand(const std::string &base, const std::vector<std::string> &options)
			: _base(base), _options(options) {}

		virtual void execute() override {
			const std::string systemCommand = _base + " " + join(_options, " ");

			std::cout << systemCommand << std::endl;

			const int exitCode = std::system(systemCommand.c_str());

			if (exitCode != 0) {
				throw std::runtime_error("The command returned an erroneous exit code: " + std::to_string(exitCode));
			}
		}

		virtual void addOption(const std::string &option) override {
			_options.push_back(option);
		}

	private:
		const std::string _base;
		std::vector<std::string> _options;
	};
}

#endif

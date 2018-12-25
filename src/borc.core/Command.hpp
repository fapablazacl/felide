
#ifndef __BORC_MODEL_COMMAND_HPP__
#define __BORC_MODEL_COMMAND_HPP__

#include <string>

namespace borc::model {
	class Command {
	public:
		virtual ~Command() {}

		virtual void execute() = 0;

		virtual void addOption(const std::string &option) = 0;

		template<typename Iterator>
		void addOptionRange(Iterator begin, Iterator end) {
			Iterator it = begin;

			while (it != end) {
				this->addOption(*it);
				it++;
			}
		}
	};
}

#endif

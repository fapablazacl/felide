
#include "ActionContext.hpp"

#include <boost/algorithm/string.hpp>

namespace felide {
    std::string instanceTemplate(const CommandTemplate &commandTemplate, const ActionContext &context) {
        CommandTemplate command = commandTemplate;

        for (const auto &pair : context) {
            const std::string &key = pair.first;
            const std::string &value = pair.second;

            command = boost::replace_all_copy(command, key, value);
        }

        return command;
    }
}

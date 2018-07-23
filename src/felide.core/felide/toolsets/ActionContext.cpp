
#include "ActionContext.hpp"

#include <felide/util/Strings.hpp>

namespace felide {
    std::string instanceTemplate(const CommandTemplate &commandTemplate, const ActionContext &context) {
        CommandTemplate command = commandTemplate;

        for (const auto &pair : context) {
            const std::string &key = pair.first;
            const std::string &value = pair.second;

            command = replace(command, key, value);
        }

        return command;
    }
}

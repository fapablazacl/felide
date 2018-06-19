
#include "CommandTask.hpp"
#include <cstdlib>
#include <stdexcept>

namespace borc {
    CommandTask::CommandTask(const std::string &command) : m_command(command) {}

    CommandTask::~CommandTask() {}
        
    void CommandTask::perform() {
        const int result = std::system(m_command.c_str());

        if (result != 0) {
            std::string msg;

            msg += "Command ";
            msg += "'" + m_command + "'";
            msg += " exited with error code ";
            msg += result;

            throw std::runtime_error(msg);
        }
    }

    std::string CommandTask::toString() const {
        return "CommandTask::toString";
    }
}

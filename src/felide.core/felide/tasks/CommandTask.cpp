
#include "CommandTask.hpp"
#include <cstdlib>
#include <stdexcept>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace felide {
    CommandTask::CommandTask(const std::string &command) : m_command(command) {}

    CommandTask::~CommandTask() {}
        
    void CommandTask::perform() {
        const int result = std::system(m_command.c_str());

        if (result != 0) {
            std::string msg;

            msg += "Command ";
            msg += "'" + m_command + "'";
            msg += " exited with error code ";
            msg += std::to_string(result);

            throw std::runtime_error(msg);
        }
    }

    std::string CommandTask::toString() const {
        return m_command;
    }
}

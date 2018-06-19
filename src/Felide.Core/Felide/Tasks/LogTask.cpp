
#include "LogTask.hpp"

#include <iostream>

namespace borc {
    LogTask::LogTask(const std::string &command) 
        : m_command(command) {}
    
    LogTask::~LogTask() {}
        
    void LogTask::perform() {
        std::cout << m_command << std::endl;
    }

    std::string LogTask::toString() const {
        return m_command;
    }
}

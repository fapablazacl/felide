
#ifndef __BORC_COMMANDTASK_HPP__
#define __BORC_COMMANDTASK_HPP__

#include "Task.hpp"

namespace borc {
    class CommandTask : public Task {
    public:
        CommandTask(const std::string &command);
        
        virtual ~CommandTask();
        
        virtual void perform() override;

        virtual std::string toString() const override;

    private:
        std::string m_command;
    };
}

#endif

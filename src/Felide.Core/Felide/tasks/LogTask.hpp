
#ifndef __BORC_LOGTASK_HPP__
#define __BORC_LOGTASK_HPP__

#include "Task.hpp"

namespace borc {
    class LogTask : public Task {
    public:
        LogTask(const std::string &command);
        
        virtual ~LogTask();
        
        virtual void perform() override;

        virtual std::string toString() const override;

    private:
        std::string m_command;
    };
}

#endif

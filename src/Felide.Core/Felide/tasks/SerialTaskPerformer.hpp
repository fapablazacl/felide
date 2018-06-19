
#ifndef __borc_serialtaskperformer_hpp__
#define __borc_serialtaskperformer_hpp__

#include "TaskPerformer.hpp"

#include <vector>

namespace borc {
    class SerialTaskPerformer : public TaskPerformer {
    public:
        virtual ~SerialTaskPerformer();

        virtual void appendTask(std::unique_ptr<Task> task) override;

        virtual void perform() override;

    private:
        std::vector<std::unique_ptr<Task>> m_tasks;
    };
}

#endif

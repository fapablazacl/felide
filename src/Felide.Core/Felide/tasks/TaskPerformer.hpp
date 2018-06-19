
#ifndef __borc_taskperformer_hpp__
#define __borc_taskperformer_hpp__

#include <memory>

namespace borc {
    class Task;
    class TaskPerformer {
    public:
        virtual ~TaskPerformer();

        virtual void appendTask(std::unique_ptr<Task> task) = 0;

        virtual void perform() = 0;
    };
}

#endif

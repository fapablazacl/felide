
#ifndef __borc_tasktree_hpp__
#define __borc_tasktree_hpp__

#include "TaskNode.hpp"

namespace borc {
    /**
     * @brief A single task dependency hierarchy
     */    
    class TaskTree {
    public:
        explicit TaskTree();

        ~TaskTree();

        void visit(std::function<void(Task*)> fn);

    private:
        std::unique_ptr<TaskNode> m_root;
    };
}

#endif

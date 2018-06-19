
#ifndef __borc_tasknodevisitor_hpp__
#define __borc_tasknodevisitor_hpp__

#include <functional>
#include <memory>

namespace borc {
    class Task;
    
    template<typename T>
    class TreeNode;

    /**
     * @brief A task node visitor that performs the specified complete hierarchy.
     */    
    class TaskNodeVisitor {
    public:
        virtual ~TaskNodeVisitor() {}

        virtual void visit(TreeNode<Task> *root, std::function<void(Task*)> fn) = 0;

    public:
        static std::unique_ptr<TaskNodeVisitor> create();
    };
}

#endif

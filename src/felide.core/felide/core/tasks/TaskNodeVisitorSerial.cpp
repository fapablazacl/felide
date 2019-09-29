
#include <cassert>
#include <felide/core/TreeNode.hpp>
#include <felide/core/tasks/TaskNodeVisitorSerial.hpp>
#include <felide/core/tasks/Task.hpp>

namespace felide {
    TaskNodeVisitorSerial::~TaskNodeVisitorSerial() {}

    void TaskNodeVisitorSerial::visit(TreeNode<Task> *nodeTask, std::function<void(Task*)> fn) {
        assert(nodeTask);

        for (auto &child : *nodeTask) {
            this->visit(child.get(), fn);
        }

        fn(nodeTask->getData());
    }
}

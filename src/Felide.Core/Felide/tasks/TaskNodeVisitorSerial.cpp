
#include <cassert>
#include <borc/TreeNode.hpp>
#include <borc/tasks/TaskNodeVisitorSerial.hpp>
#include <borc/tasks/Task.hpp>

namespace borc {
    TaskNodeVisitorSerial::~TaskNodeVisitorSerial() {}

    void TaskNodeVisitorSerial::visit(TreeNode<Task> *nodeTask, std::function<void(Task*)> fn) {
        assert(nodeTask);

        for (auto &child : *nodeTask) {
            this->visit(child.get(), fn);
        }

        fn(nodeTask->getData());
    }
}

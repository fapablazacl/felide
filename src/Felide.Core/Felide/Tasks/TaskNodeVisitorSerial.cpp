
#include <cassert>
#include <Felide/TreeNode.hpp>
#include <Felide/Tasks/TaskNodeVisitorSerial.hpp>
#include <Felide/Tasks/Task.hpp>

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


#include <cassert>
#include <felide/TreeNode.hpp>
#include <felide/tasks/TaskNodeVisitorSerial.hpp>
#include <felide/tasks/Task.hpp>

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

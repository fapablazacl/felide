
#include "TaskNodeVisitor.hpp"

#include "TaskNodeVisitorSerial.hpp"

namespace borc {
    std::unique_ptr<TaskNodeVisitor> TaskNodeVisitor::create() {
        return std::make_unique<TaskNodeVisitorSerial>();
    }
}

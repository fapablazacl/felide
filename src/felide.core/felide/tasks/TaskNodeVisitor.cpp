
#include "TaskNodeVisitor.hpp"

#include "TaskNodeVisitorSerial.hpp"

namespace felide {
    std::unique_ptr<TaskNodeVisitor> TaskNodeVisitor::create() {
        return std::make_unique<TaskNodeVisitorSerial>();
    }
}

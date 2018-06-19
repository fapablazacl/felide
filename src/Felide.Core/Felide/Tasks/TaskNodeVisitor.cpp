
#include "TaskNodeVisitor.hpp"

#include "TaskNodeVisitorSerial.hpp"

namespace Felide {
    std::unique_ptr<TaskNodeVisitor> TaskNodeVisitor::create() {
        return std::make_unique<TaskNodeVisitorSerial>();
    }
}

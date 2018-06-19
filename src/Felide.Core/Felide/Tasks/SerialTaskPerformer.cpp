
#include "SerialTaskPerformer.hpp"
#include "Task.hpp"

namespace borc {
    SerialTaskPerformer::~SerialTaskPerformer() {}

    void SerialTaskPerformer::appendTask(std::unique_ptr<Task> task) {
        m_tasks.push_back(std::move(task));
    }

    void SerialTaskPerformer::perform() {
        for (auto &task : m_tasks) {
            task->perform();
        }

        m_tasks.clear();
    }
}

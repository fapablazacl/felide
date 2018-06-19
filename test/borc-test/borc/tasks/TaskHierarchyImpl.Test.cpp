
#include "TaskHierarchyImpl.hpp"
#include "Task.hpp"

namespace borc {
    TaskHierarchyImpl::TaskHierarchyImpl() {}

    TaskHierarchyImpl::~TaskHierarchyImpl() {}

    Task* TaskHierarchyImpl::addTask(std::unique_ptr<Task> task) {
        Task *taskPtr = task.get();

        m_tasks.push_back(std::move(task));

        return taskPtr;
    }

    TaskHierarchyImpl* TaskHierarchyImpl::setTaskDependency(Task *task, Task* dependency) {
        m_taskDependencies[task].push_back(dependency);
        return this;
    }

    std::vector<Task*> TaskHierarchyImpl::getTaskDependencies(Task *task) const {
        auto taskIterator = m_taskDependencies.find(task);

        if (taskIterator != m_taskDependencies.end()) {
            return taskIterator->second;
        } else {
            return std::vector<Task*>();
        }
    }
}

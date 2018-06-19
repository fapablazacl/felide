
#ifndef __borc_project_hpp__
#define __borc_project_hpp__

#include <string>
#include <vector>
#include <memory>

namespace borc {
    enum class TargetAction;

    class TaskPerformer;
    class Target;
    class ModuleTarget;

    template<typename T>
    class TreeNode;

    class Task;

    /**
     * @brief Project class.
     */
    class Project {
    public:
        virtual ~Project() {}

        /**
         * @brief Get a vector of the supported Targets for the project 
         */
        virtual std::vector<Target*> getTargets() const = 0;

        /**
         * @brief Utility method that creates a new child target.
         */
        template<typename TargetImpl>
        TargetImpl* createTarget() {
            return static_cast<TargetImpl*>(this->addTarget(TargetImpl::create(this)));
        }

        /**
         * @brief Get the name of the project
         */
        virtual std::string getName() const = 0;

        /**
         * @brief Set the name of the project
         */
        virtual Project* setName(const std::string &name) = 0;

        /**
         * @brief Get the root path
         */
        virtual std::string getPath() const = 0;

        /**
         * @brief Get the build path for the project
         */
        virtual std::string getBuildPath() const = 0;

        /**
         * @brief Set the root path of the project
         */
        virtual Project* setPath(const std::string &path) = 0;

        /**
         * @brief Setups the project, preparing internal data.
         * 
         * Prepare the internal directory hierarchy, and the internal data structures for build project files
         */
        virtual Project* setup() = 0;

        /**
         * @brief Generate the task tree in order to perform the requested action
         */
        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action) = 0;
        
    private:        
        /**
         * @brief Add a new target, prexisting target, linked to this project. 
         *
         * Intented to be called by borc::Project::createTarget<TargetImpl>
         */
        virtual Target* addTarget(std::unique_ptr<Target> target) = 0;

    public:
        /**
         * @brief Creates a new, empty project
         */
        static std::unique_ptr<Project> create(const std::string &name, const std::string &path="");
    };
}

#endif

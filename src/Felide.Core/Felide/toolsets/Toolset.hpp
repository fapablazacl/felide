
#ifndef __borc_toolchain_hpp__
#define __borc_toolchain_hpp__

#include <cstddef>

#include <vector>
#include <memory>

namespace borc {
    class Project;
    class Compiler;
    class Linker;
    class Task;

    class Source;
    class ModuleTarget;
    enum class TargetAction;

    template<typename T>
    class TreeNode;

    class Task;

    class Toolset {
    public:
        virtual ~Toolset();

        /**
         * @brief Checks that the specified action can be applied on the supplied source
         */
        virtual bool checkAction(const TargetAction action, const Source *source) const = 0;

        /**
         * @brief Create the build task hierarchy needed to perform the specified action on the specified source
         */
        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action, const Source *source) = 0;

        /**
         * @brief Create the build task hierarchy needed to perform the specified action on the specified module target
         */
        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action, const ModuleTarget *target) = 0;
    };
}

#endif


#ifndef __borc_linker_hpp__
#define __borc_linker_hpp__

#include <string>
#include <vector>
#include <memory>

namespace borc {
    template<typename T>
    class TreeNode;

    class Task;
    class Source;
    class Target;

    class Linker {
    public:
        virtual ~Linker();

        /**
         * @brief Return true the supplied target is linkable by this linker, and false otherwise.
         */
        virtual bool isLinkable(const Target *target) const = 0;

        /**
         * @brief Get the physical name of the command (example: "cl" for Visual C++).
         */
        virtual std::string getToolName() const = 0;

        /**
         * @brief Get the physical location, in disk, of the path of the compiler.
         */
        virtual std::string getPath() const = 0;
        
        /**
         * @brief Creates a task wich will link the specified target at a later stage.
         */
        virtual std::unique_ptr<TreeNode<Task>> createTask(const Target *target, const std::vector<std::string> &objectFiles) = 0;
    };
}

#endif 

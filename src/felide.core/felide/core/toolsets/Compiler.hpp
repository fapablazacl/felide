
#ifndef __borc_compiler_hpp__
#define __borc_compiler_hpp__

#include <string>
#include <map>
#include <memory>

#include <felide/core/FileTypeRegistry.hpp>

#include "ActionContext.hpp"

namespace felide {
    template<typename T>
    class TreeNode;

    class Task;
    class Source;
    class FileTypeRegistry;

    struct CompilerDescription;

    class Compiler {
    public:
        virtual ~Compiler();

        /**
         * @brief Return true the supplied source is compilable by this compiler, and false otherwise.
         */
        virtual bool isCompilable(const Source *source) const = 0;

        /**
         * @brief Get the physical name of the command (example: "cl" for Visual C++).
         */
        virtual std::string getToolName() const = 0;

        /**
         * @brief Get the physical location, in disk, of the path of the compiler.
         */
        virtual std::string getPath() const = 0;

        /**
         * @brief Creates a task hierarchy wich will build the specified source file at a later stage.
         */
        virtual std::unique_ptr<TreeNode<Task>> createTask(const Source *source, const ActionContext &context) = 0;

        virtual CompilerDescription getDescription() const = 0;
    };
}

#endif 
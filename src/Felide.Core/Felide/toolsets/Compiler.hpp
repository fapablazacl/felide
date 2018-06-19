
#ifndef __borc_compiler_hpp__
#define __borc_compiler_hpp__

#include <string>
#include <memory>

#include <borc/FileTypeRegistry.hpp>

namespace borc {
    template<typename T>
    class TreeNode;

    class Task;
    class Source;
    class FileTypeRegistry;

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
        virtual std::unique_ptr<TreeNode<Task>> createTask(const Source *source) = 0;
    };
}

#endif 

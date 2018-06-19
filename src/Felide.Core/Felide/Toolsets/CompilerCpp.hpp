
#ifndef __borc_compilerimpl_hpp__
#define __borc_compilerimpl_hpp__

#include "Compiler.hpp"

#include <set>

#include <vector>

namespace borc {
    struct CompilerConfigCpp {
        //! The symbol used for compiler switches
        std::string switchSymbol;

        //! The name of the executable command
        std::string command;

        //! Installation path
        std::string path;

        //! System include paths
        std::vector<std::string> includePaths; 

        //! System library paths
        std::vector<std::string> libraryPaths;
    };

    /**
     * @brief Default compiler implementation
     */
    class CompilerCpp : public Compiler {
    public:
        explicit CompilerCpp(const FileTypeRegistry *registry, const std::string &toolName, const std::set<const FileType*> &types);

        explicit CompilerCpp(const FileTypeRegistry *registry, const std::string &toolName, const std::set<const FileType*> &types, const std::string &path);

        virtual ~CompilerCpp();

        virtual bool isCompilable(const Source *source) const override;

        virtual std::string getToolName() const override;

        virtual std::string getPath() const override;
        
        virtual std::unique_ptr<TreeNode<Task>> createTask(const Source *source) override;

    private:
        std::string m_toolName;
        std::string m_path;
        const FileTypeRegistry *m_registry;

        std::set<const FileType*> m_supportedTypes;

        std::string m_switchSymbol;
    };
}

#endif 

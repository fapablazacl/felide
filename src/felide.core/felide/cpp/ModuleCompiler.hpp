
#ifndef __borc_compilerimpl_hpp__
#define __borc_compilerimpl_hpp__

#include <felide/toolsets/Compiler.hpp>

#include <set>
#include <vector>

namespace felide {
    /**
     * @brief Default compiler implementation
     */
    class ModuleCompiler : public Compiler {
    public:
        explicit ModuleCompiler(const FileTypeRegistry *registry, const std::string &toolName, const std::set<const FileType*> &types);

        explicit ModuleCompiler(const FileTypeRegistry *registry, const std::string &toolName, const std::set<const FileType*> &types, const std::string &path);

        virtual ~ModuleCompiler();

        virtual bool isCompilable(const Source *source) const override;

        virtual std::string getToolName() const override;

        virtual std::string getPath() const override;
        
        virtual std::unique_ptr<TreeNode<Task>> createTask(const Source *source) override;

        virtual std::string computeOutputSourceName(const Source *source) const override;

    private:
        std::string m_toolName;
        std::string m_path;
        const FileTypeRegistry *m_registry;

        std::set<const FileType*> m_supportedTypes;

        std::string m_switchSymbol;
    };
}

#endif 

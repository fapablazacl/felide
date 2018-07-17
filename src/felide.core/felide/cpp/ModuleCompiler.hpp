
#ifndef __borc_compilerimpl_hpp__
#define __borc_compilerimpl_hpp__

#include <felide/toolsets/Compiler.hpp>
#include <felide/FileTypeRegistry.hpp>

#include <set>
#include <vector>
#include <map>

namespace felide {
    struct CompilerDescription {
        std::string compileTemplate;
        std::vector<std::string> inputExtensions;
        std::string outputExtension;

        //! Map from VariableKey to specific compiler option
        std::map<std::string, std::string> keyOptionMap;
    };

    class ModuleToolset;

    /**
     * @brief Default compiler implementation
     */
    class ModuleCompiler : public Compiler {
    public:
        explicit ModuleCompiler(const ModuleToolset *toolset, const CompilerDescription &description);

        virtual ~ModuleCompiler();

        virtual bool isCompilable(const Source *source) const override;

        virtual std::string getToolName() const override;

        virtual std::string getPath() const override;
        
        virtual std::unique_ptr<TreeNode<Task>> createTask(const Source *source, const CompilerActionContext &context) override;

        virtual std::string computeOutputSourceName(const Source *source) const override;

    private:
        std::string computeOutputPath(const Source *source) const;

    private:
        const ModuleToolset *m_toolset = nullptr;
        CompilerDescription m_description;
        std::unique_ptr<FileTypeRegistry> m_supportedFileTypes;
    };
}

#endif 

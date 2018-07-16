
#ifndef __borc_compilerimpl_hpp__
#define __borc_compilerimpl_hpp__

#include <felide/toolsets/Compiler.hpp>
#include <felide/FileTypeRegistry.hpp>

#include <set>
#include <vector>

namespace felide {
    struct CompilerDescription {
        std::string compileTemplate;
        std::vector<std::string> inputExtensions;
        std::string outputExtension;
    };

    /**
     * @brief Default compiler implementation
     */
    class ModuleCompiler : public Compiler {
    public:
        explicit ModuleCompiler(const CompilerDescription &description);

        virtual ~ModuleCompiler();

        virtual bool isCompilable(const Source *source) const override;

        virtual std::string getToolName() const override;

        virtual std::string getPath() const override;
        
        virtual std::unique_ptr<TreeNode<Task>> createTask(const Source *source) override;

        virtual std::string computeOutputSourceName(const Source *source) const override;

    private:
        CompilerDescription m_description;
        std::unique_ptr<FileTypeRegistry> m_supportedFileTypes;
    };
}

#endif 

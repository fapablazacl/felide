
#ifndef __borc_linkerimpl_hpp__
#define __borc_linkerimpl_hpp__

#include <felide/toolsets/Linker.hpp>
#include <felide/toolsets/ActionContext.hpp>

#include <string>
#include <memory>

namespace felide {
    class Task;

    class Source;
    class Target;

    struct LinkerDescription {
        std::string linkTemplate;
        std::string inputExtension;
        std::string outputExtension;
    };

    class ModuleToolset;

    class ModuleLinker : public Linker {
    public:
        explicit ModuleLinker(const ModuleToolset *toolset, const LinkerDescription &description);

        virtual ~ModuleLinker();

        virtual bool isLinkable(const Target *target) const override;

        virtual std::string getToolName() const override;

        virtual std::string getPath() const override;
        
        virtual std::unique_ptr<TreeNode<Task>> createTask(const Target *target, const std::vector<std::string> &objectFiles, const ActionContext &context) override;

    private:
        const ModuleToolset *m_toolset;
        LinkerDescription m_description;
        std::string m_toolName;
        std::string m_path;
    };
}

#endif 


#ifndef __borc_toolchainimpl_hpp__
#define __borc_toolchainimpl_hpp__

#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include <felide/toolsets/Toolset.hpp>

namespace felide {
    struct CompilerDescription;
    struct LinkerDescription;

    class ModuleToolset : public Toolset {
    public:
        static std::unique_ptr<ModuleToolset> create (
            const std::vector<CompilerDescription> &compilerDescriptions, 
            const std::vector<LinkerDescription> &linkerDescriptions
        );
    };
}

#endif 

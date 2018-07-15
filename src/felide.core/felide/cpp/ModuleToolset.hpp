
#ifndef __borc_toolchainimpl_hpp__
#define __borc_toolchainimpl_hpp__

#include <felide/toolsets/Toolset.hpp>

#include <cstddef>
#include <vector>
#include <memory>

namespace felide {
    class Target;
    class Source;
    class FileTypeRegistry;

    class FileType;

    class ModuleToolset : public Toolset {
    public:
        static std::unique_ptr<ModuleToolset> create(FileTypeRegistry *registry);
    };
}

#endif 

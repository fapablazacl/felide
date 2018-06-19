
#ifndef __borc_toolchainimpl_hpp__
#define __borc_toolchainimpl_hpp__

#include "Toolset.hpp"

#include <cstddef>
#include <vector>
#include <memory>

namespace borc {
    class Target;
    class Source;
    class FileTypeRegistry;

    class FileType;

    class ToolsetCpp : public Toolset {
    public:
        static std::unique_ptr<ToolsetCpp> create(FileTypeRegistry *registry);
    };
}

#endif 


#ifndef __borc_moduletargettype_hpp__
#define __borc_moduletargettype_hpp__

#include <string>

namespace borc {
    enum class ModuleTargetType {
        Program = 1,
        Library = 2
    };

    extern std::string to_string(const ModuleTargetType type);
}

#endif

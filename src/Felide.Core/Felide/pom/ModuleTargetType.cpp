
#include "ModuleTargetType.hpp"

#include <stdexcept>

namespace borc {
    std::string to_string(const ModuleTargetType type) {
        switch (type) {
        case ModuleTargetType::Program: return "ModuleTargetType::Program";
        case ModuleTargetType::Library: return "ModuleTargetType::Library";
        default: throw std::invalid_argument("Unknown target type");
        }
    }
}

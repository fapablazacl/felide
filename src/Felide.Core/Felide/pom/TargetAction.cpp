
#include "TargetAction.hpp"

#include <stdexcept>

namespace borc {
    std::string to_string(const TargetAction action) {
        switch (action) {
            case TargetAction::Build: return "TargetAction::Build";
            default: throw std::invalid_argument("Unknown target action");
        }
    }
}

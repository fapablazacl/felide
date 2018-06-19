
#ifndef __borc_targetaction_hpp__
#define __borc_targetaction_hpp__

#include <string>

namespace borc {
    enum class TargetAction {
        Build = 1
    };

    extern std::string to_string(const TargetAction action);
}

#endif

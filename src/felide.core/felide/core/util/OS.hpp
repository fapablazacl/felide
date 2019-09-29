
#ifndef __FELIDE_UTIL_OS_HPP__
#define __FELIDE_UTIL_OS_HPP__

#include <felide/core/Predef.hpp>

namespace felide {
    enum OS {
        Unknown,
        Windows,
        Mac,
        Linux
    };

    extern OS FELIDE_API getCurrentOS();
}

#endif

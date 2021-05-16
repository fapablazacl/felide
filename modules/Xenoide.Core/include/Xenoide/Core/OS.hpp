
#ifndef __XENOIDE_UTIL_OS_HPP__
#define __XENOIDE_UTIL_OS_HPP__

#include <Xenoide/Core/Predef.hpp>

namespace felide {
    enum OS {
        Unknown,
        Windows,
        Mac,
        Linux
    };

    extern OS getCurrentOS();
}

#endif

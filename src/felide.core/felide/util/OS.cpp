
#include "OS.hpp"

namespace felide {
    OS FELIDE_API getCurrentOS() {
#if defined(_WINDOWS)
        return OS::Windows;
#elif defined(__linux__)
        return OS::Linux;
#else 
        return OS::Unknown;
#endif
    }
}

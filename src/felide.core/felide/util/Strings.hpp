/**
 *  @file Strings.hpp
 *  @brief Utility functions for strings
 */

#ifndef __felide_util_strings_hpp__
#define __felide_util_strings_hpp__

#include <string>
#include <vector>

namespace felide {
    extern std::string join(const std::vector<std::string> &strings, const std::string &separator);
}

#endif

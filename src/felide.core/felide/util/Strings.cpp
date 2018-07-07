
#include "Strings.hpp"

namespace felide {
    std::string join(const std::vector<std::string> &strings, const std::string &separator) {
        if (strings.size() == 0) {
            return "";
        }

        std::string result;

        for (std::size_t i=0; i<strings.size(); i++) {
            result += strings[i];

            if (i == strings.size() - 1) {
                result += separator;
            }
        }

        return result;
    }
}

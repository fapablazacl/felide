
#ifndef __FELIDE_UI_FILEFILTER_HPP__
#define __FELIDE_UI_FILEFILTER_HPP__

#include <string>
#include <vector>

namespace felide {
    struct FileFilter {
        std::string description;
        std::vector<std::string> wildcards;

        ~FileFilter();
    };
} 

#endif

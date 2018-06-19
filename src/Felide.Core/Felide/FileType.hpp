
#ifndef __borc_filetype_hpp__
#define __borc_filetype_hpp__

#include <string>
#include <vector>

namespace borc {
    /**
     * @brief A generic file type
     */
    class FileType {
    public:
        std::string name;
        std::vector<std::string> extensions;

        // bool operator == (const FileType &rhs) const;
        // bool operator != (const FileType &rhs) const;

        bool check(const std::string &extension) const;
    };
}

#endif

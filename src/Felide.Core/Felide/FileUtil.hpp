
#ifndef __FELIDE_FILEUTIL_HPP__
#define __FELIDE_FILEUTIL_HPP__

#include <string>

namespace felide {
    class FileUtil {
    private:
        FileUtil() = delete;
        ~FileUtil() = delete;

    public:
        static std::string load(const std::string &filename);

        static void save(const std::string &filename, const std::string &content);
    };
}

#endif

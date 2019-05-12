
#ifndef __FELIDE_UI_FILESERVICE_HPP__
#define __FELIDE_UI_FILESERVICE_HPP__

#include <memory>
#include <string>
#include <boost/filesystem/path.hpp>

namespace felide {
    class FileService {
    public:
        virtual ~FileService() = 0;

        virtual std::string load(const boost::filesystem::path &filePath) = 0;

        virtual void save(const boost::filesystem::path &filePath, const std::string &content) = 0;

        virtual void touch(const boost::filesystem::path &filePath) = 0;

    public:
        static std::unique_ptr<FileService> create();
    };
}

#endif

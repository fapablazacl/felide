
#include "FileService.hpp"
#include "FileUtil.hpp"

#include <fstream>

namespace felide {
    class FileServiceImpl : public FileService {
    public:
        FileServiceImpl() {}

        virtual ~FileServiceImpl() {}

        virtual std::string load(const boost::filesystem::path &filePath) override {
            return FileUtil::load(filePath.string());
        }

        virtual void save(const boost::filesystem::path &filePath, const std::string &content) override {
            FileUtil::save(filePath.string(), content);
        }

        virtual void touch(const boost::filesystem::path &filePath) override {
            std::ofstream os;
            os.open(filePath.string().c_str(), std::ios_base::out);
            os.close();
        }
    };
}

namespace felide {
    std::unique_ptr<FileService> FileService::create() {
        return std::make_unique<FileServiceImpl>();
    }
}

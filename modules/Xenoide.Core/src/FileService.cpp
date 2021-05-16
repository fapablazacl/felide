
#include <Xenoide/Core/FileService.hpp>
#include <fstream>

namespace Xenoide {
    class FileServiceImpl : public FileService {
    public:
        FileServiceImpl() {}

        virtual ~FileServiceImpl() {}

        virtual std::string load(const boost::filesystem::path &filePath) override {
            typedef std::istreambuf_iterator<char> fstream_iterator;

            std::fstream fs;

            fs.open(filePath.string().c_str(), std::ios_base::in);
            if (!fs.is_open()) {
                throw std::runtime_error("Couldn't open the file '" + filePath.string() + "'.");
            }

            fs.seekg(0);

            std::string content;
            content.assign(fstream_iterator(fs), fstream_iterator());

            return content;
        }

        virtual void save(const boost::filesystem::path &filePath, const std::string &content) override {
            std::fstream fs;

            fs.open(filePath.string().c_str(), std::ios_base::out);
            if (!fs.is_open()) {
                throw std::runtime_error("The file " + filePath.string() + "could't be opened");
            }

            if (content.size() > 0) {
                fs.write(content.c_str(), content.size());
            } else {
                fs.write("", 1);
            }
        }


        virtual void touch(const boost::filesystem::path &filePath) override {
            std::ofstream os;
            os.open(filePath.string().c_str(), std::ios_base::out);
            os.close();
        }
    };
}

namespace Xenoide {
    FileService::~FileService() {}

    std::unique_ptr<FileService> FileService::create() {
        return std::make_unique<FileServiceImpl>();
    }
}

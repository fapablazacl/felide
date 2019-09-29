
#include "DirectoryTask.hpp"

#include <boost/filesystem.hpp>

namespace felide {
    DirectoryTask::DirectoryTask(const std::string &directory) {
        m_directory = directory;
    }
    
    void DirectoryTask::perform() {
        namespace fs = boost::filesystem;

        fs::path path = m_directory;

        fs::create_directories(path);

        if (!fs::exists(m_directory)) {
            throw std::runtime_error("Couldn't create the specified directory");
        }
    }

    std::string DirectoryTask::toString() const {
        return "DirectoryTask::toString";
    }
}

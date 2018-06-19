
#include "DirectoryTask.hpp"

#include <experimental/filesystem>

namespace borc {
    DirectoryTask::DirectoryTask(const std::string &directory) {
        m_directory = directory;
    }
    
    void DirectoryTask::perform() {
        namespace fs = boost::filesystem;

        fs::path path = m_directory;

        fs::create_directory(path);

        if (!fs::exists(m_directory)) {
            throw std::runtime_error("Couldn't create the specified directory");
        }
    }

    std::string DirectoryTask::toString() const {
        return "DirectoryTask::toString";
    }
}

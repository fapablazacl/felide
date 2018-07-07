
#include "Source.hpp"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace felide {
    Source::Source(const std::string &filePath, const Target *target) {
        m_filePath = filePath;
        m_target = target;
    }

    Source::~Source() {}

    std::string Source::getExtension() const {
        return fs::path(m_filePath).extension();
    }

    std::string Source::getFileTitle() const {
        return fs::path(m_filePath).stem().string();
    }
    
    std::string Source::getFileName() const {
        return fs::path(m_filePath).filename().string();
    }

    std::string Source::getFilePath() const {
        return m_filePath;
    }

    const Target* Source::getTarget() const {
        return m_target;
    }
}

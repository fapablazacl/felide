
#include "Source.hpp"

#include <felide/pom/Target.hpp>
#include <felide/pom/Project.hpp>
#include <felide/util/Strings.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace felide {
    Source::Source(const std::string &filePath, const Target *target) {
        m_filePath = filePath;
        m_target = target;
    }

    Source::~Source() {}

    std::string Source::getExtension() const {
        return fs::path(m_filePath).extension().string();
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

    std::string Source::computeOutputFileName(const std::string &extension) const {
        const fs::path result = fs::path(this->getFileName() + extension);
        return result.string();
    }

    std::string Source::computeOutputDirectory(const std::string &relativePrefix) const {
        const fs::path sourcePath = fs::path(this->getFilePath()).parent_path();
        const fs::path projectPath = this->getTarget()->getProject()->getPath();
        const fs::path sourceRelPath = replace(sourcePath.string(), projectPath.string(), "");
        const fs::path buildPath = relativePrefix;

        const fs::path result = projectPath / buildPath / sourceRelPath;

        return result.string();
    }
}

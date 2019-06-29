
#ifndef __FELIDE_CMAKEPROJECT_HPP__
#define __FELIDE_CMAKEPROJECT_HPP__

#include <string>
#include <map>
#include <boost/filesystem/path.hpp>

namespace felide {
    struct CMakeBuildConfiguration {
        std::string generator;
        std::string buildType;
        std::map<std::string, std::string> variables;
    };

    struct CompilerDescription;
    class CompilerDetector;

    /**
    * @brief Handles a CMake project with a collection of associated Build configuration
    */
    class CMakeProject {
    public:
        CMakeProject(const boost::filesystem::path &projectFolder, CompilerDetector *compilerDetector);

        void build(const std::string &buildType);

        void configure(const std::string &buildType);

    private:
        void configureImpl(const boost::filesystem::path &buildFolder, const CMakeBuildConfiguration &configuration);

        boost::filesystem::path getProjectFolder() const;

        const boost::filesystem::path makeBuildFolder(const CompilerDescription &compilerDesc, const std::string &buildType) const;

    private:
        boost::filesystem::path projectFolder;
        CompilerDetector *compilerDetector = nullptr;
    };
}

#endif

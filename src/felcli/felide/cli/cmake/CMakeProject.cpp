
#include "CMakeProject.hpp"
#include "../CompilerDetector.hpp"

#include <iostream>

#include <boost/filesystem/path.hpp>
#include <boost/process.hpp>

namespace felide {
    CMakeProject::CMakeProject(const boost::filesystem::path &projectFolder, CompilerDetector *compilerDetector)
        : projectFolder(projectFolder), compilerDetector(compilerDetector) {}

    void CMakeProject::build(const std::string &buildType) {
        const boost::filesystem::path projectFolder = this->getProjectFolder();
        const CompilerDescription compilerDesc = compilerDetector->detect();
        const boost::filesystem::path buildFolder = this->makeBuildFolder(compilerDesc, buildType);

        boost::filesystem::path makePath = boost::process::search_path("make");

        boost::process::child childProcess {
            boost::process::start_dir (buildFolder),
            makePath
        };

        childProcess.wait();

        if (childProcess.exit_code() != 0) {
            throw std::runtime_error(
                "Some error(s) ocurred during the build of the build type '" + buildType + "'"
            );
        }
    }

    void CMakeProject::configure(const std::string &buildType) {
        const CompilerDescription compilerDesc = compilerDetector->detect();

        std::cout << "Configuring build    " << buildType << " ..." << std::endl;
        CMakeBuildConfiguration config;

        config.generator = "Unix Makefiles";
        config.buildType = buildType;

        const boost::filesystem::path buildFolder = this->makeBuildFolder(compilerDesc, buildType);

        this->configureImpl(buildFolder, config);
        
        std::cout << "Build folder configuration done." << std::endl;
    }

    void CMakeProject::configureImpl(const boost::filesystem::path &buildFolder, const CMakeBuildConfiguration &configuration) {
        boost::filesystem::create_directories(buildFolder);
        boost::filesystem::path cmakePath = boost::process::search_path("cmake");
        boost::process::ipstream pipeStream;
        boost::process::child childProcess {
            boost::process::start_dir (buildFolder),
            cmakePath, 
            projectFolder,
            "-DCMAKE_BUILD_TYPE=" + configuration.buildType, 
            boost::process::std_out > boost::process::null
        };

        childProcess.wait();

        if (childProcess.exit_code() != 0) {
            throw std::runtime_error(
                "Some error(s) ocurred during the configuration of the build type '" + 
                configuration.buildType + "'"
            );
        }
    }

    boost::filesystem::path CMakeProject::getProjectFolder() const {
        return projectFolder;
    }

    const boost::filesystem::path CMakeProject::makeBuildFolder(const CompilerDescription &compilerDesc, const std::string &buildType) const {
        return projectFolder / ".borc-cmake" / (compilerDesc.key + "-" + compilerDesc.version.toString()) / buildType;
    }
}


#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/process.hpp>

#include <felide/Version.hpp>

struct CompilerDescription {
    std::string key;
    std::string name;
    felide::Version version;
};

/**
 * @brief Detects some details from a certain compiler
 */
class CompilerDetector {
public:    
    virtual ~CompilerDetector() {}

    virtual CompilerDescription detect() const = 0;
};

class GnuCompilerDetector : public CompilerDetector {
public:
    virtual CompilerDescription detect() const override {
        const std::vector<std::string> specLines = this->invokeGCCv();
        const CompilerDescription compilerDesc = this->createDescriptionFromSpecLines(specLines);

        return compilerDesc;
    }

private:
    CompilerDescription createDescriptionFromSpecLines(const std::vector<std::string> &specLines) const {
        CompilerDescription compilerDesc;

        compilerDesc.key = "gcc";
        compilerDesc.name = "GNU Compiler Collection";
        compilerDesc.version = this->parseVersion(specLines[6]);

        return compilerDesc;
    }

    std::vector<std::string> invokeGCCv() const {
        boost::process::ipstream pipeStream;
        boost::process::child childProcess {"gcc -v", boost::process::std_err > pipeStream};

        std::string line;
        std::vector<std::string> specs;

        while (pipeStream && std::getline(pipeStream, line) && !line.empty()) {
            specs.push_back(line);
        }

        childProcess.wait();

        return specs;
    }

    std::string parseProperty(const std::string &propertyLine) const {
        return propertyLine;
    }

    felide::Version parseVersion(const std::string &versionLine) const {
        std::vector<std::string> parts;

        boost::split(parts, versionLine, boost::is_any_of(" "));

        return felide::Version::parse(parts[2]);
    }
};

struct CMakeBuildConfiguration {
    std::string generator;
    std::string buildType;
    std::map<std::string, std::string> variables;
};

static bool isCMakeProject(const boost::filesystem::path &projectFolder) {
    return boost::filesystem::exists(projectFolder / "CMakeLists.txt");
}

/**
 * @brief Handles a CMake project with a collection of associated Build configuration
 */
class CMakeProject {
public:
    CMakeProject(const boost::filesystem::path &projectFolder, CompilerDetector *compilerDetector)
        : projectFolder(projectFolder), compilerDetector(compilerDetector) {}

    void build(const std::string &buildType) {
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

    void configure(const std::string &buildType) {
        const CompilerDescription compilerDesc = compilerDetector->detect();

        std::cout << "Configuring build    " << buildType << " ..." << std::endl;
        CMakeBuildConfiguration config;

        config.generator = "Unix Makefiles";
        config.buildType = buildType;

        const boost::filesystem::path buildFolder = this->makeBuildFolder(compilerDesc, buildType);

        this->configureImpl(buildFolder, config);
        
        std::cout << "Build folder configuration done." << std::endl;
    }

private:
    void configureImpl(const boost::filesystem::path &buildFolder, const CMakeBuildConfiguration &configuration) {
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

    boost::filesystem::path getProjectFolder() const {
        return projectFolder;
    }

    const boost::filesystem::path makeBuildFolder(const CompilerDescription &compilerDesc, const std::string &buildType) const {
        return projectFolder / ".borc-cmake" / (compilerDesc.key + "-" + compilerDesc.version.toString()) / buildType;
    }

private:
    boost::filesystem::path projectFolder;
    CompilerDetector *compilerDetector = nullptr;
};

/**
 * @brief Controller that handles CMake projects.
 */
class CliCMakeController {
public:
    CliCMakeController(CompilerDetector *compilerDetector) {
        this->compilerDetector = compilerDetector;
    }

    void dispatch(const std::string &subcommand, const std::vector<std::string> &params) {
		if (subcommand == "--help") {
			this->showHelp();
		} else if (subcommand == "configure") {
			this->configure(params);
		} else if (subcommand == "build") {
			this->build(params);
		}else {
            throw std::runtime_error("Unknown command '" + subcommand + "' specified.");
        }
    }

private:
    void showHelp() {
        const std::string helpString = R"(
Syntax:
    felcli subcommand --options

Available subcommands:
    setup Setup a specific toolchain for use in the current project
    run   Run an executable, optionally debugging it

For specific use for a subcommand, use the --help switch. For example:
    felcli setup --help
)";
        std::cout << helpString;
    }

    void configure(const std::vector<std::string> &params) {
        if (! isCMakeProject(boost::filesystem::current_path())) {
            throw std::runtime_error("Only CMake projects are supported for now");
        }

        if (params.size() == 0) {
            throw std::runtime_error("Missing build configuration (Debug, Release)");
        }

        CMakeProject project {boost::filesystem::current_path(), compilerDetector};

        project.configure(params[0]);
    }

    void build(const std::vector<std::string> &params) {
        if (! isCMakeProject(boost::filesystem::current_path())) {
            throw std::runtime_error("Only CMake projects are supported for now");
        }

        if (params.size() == 0) {
            throw std::runtime_error("Missing build configuration (Debug, Release)");
        }

        CMakeProject project {boost::filesystem::current_path(), compilerDetector};

        project.build(params[0]);
    }

private:
    CompilerDetector *compilerDetector = nullptr;
};

int main(int argc, char *argv[]) {
    try {
		if (argc < 2) {
			throw std::runtime_error("No options specified. Use borc --help for help.");
		}

		GnuCompilerDetector compilerDetector;
		CliCMakeController controller {&compilerDetector};

		const std::string subcommand = argv[1];

        std::vector<std::string> params;
        for (int i=2; i<argc; i++) {
            params.push_back(argv[i]);
        }
        
        controller.dispatch(subcommand, params);

		return 0;
    } catch (const std::exception &exp) {
        std::cerr << "Error: " << exp.what() << std::endl;

        return 1;    
    }
}

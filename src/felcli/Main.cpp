
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

/**
 * @brief Handles a CMake project with a collection of associated Build configuration
 */
class CMakeProject {
public:
    CMakeProject(const boost::filesystem::path &sourceDirectory) {
        this->sourceDirectory = sourceDirectory;
    }

    void configure(const boost::filesystem::path &buildFolder, const CMakeBuildConfiguration &configuration) {
        boost::filesystem::create_directories(buildFolder);
        boost::filesystem::path cmakePath = boost::process::search_path("cmake");
        boost::process::ipstream pipeStream;
        boost::process::child childProcess {
            boost::process::start_dir (buildFolder),
            cmakePath, 
            sourceDirectory,
            "-DCMAKE_BUILD_TYPE=" + configuration.buildType, 
            // boost::process::start_dir = (buildFolder / "lala"),
            boost::process::std_out > boost::process::null
        };

        childProcess.wait();

        if (childProcess.exit_code() == 0) {
            buildConfigurationMap[buildFolder] = configuration;
		} else {
            throw std::runtime_error(
                "Some error(s) ocurred during the configuration of the build type '" + 
                 configuration.buildType + "'"
            );
        }
    }

public:
    static std::unique_ptr<CMakeProject> create(const boost::filesystem::path &sourceDirectory) {
        return std::make_unique<CMakeProject>(sourceDirectory);
    }

private:
    boost::filesystem::path sourceDirectory;
    std::map<boost::filesystem::path, CMakeBuildConfiguration> buildConfigurationMap;
};

/**
 * @brief Controller that handles CMake projects.
 */
class CliCMakeController {
public:
    CliCMakeController(CompilerDetector *compilerDetector) {
        this->compilerDetector = compilerDetector;
    }

    void dispatch(const std::string &subcommand) {
		if (subcommand == "--help") {
			this->showHelp();
		} else if (subcommand == "setup") {
			this->setup();
		} else {
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

    void setup() {
        const boost::filesystem::path projectFolder = boost::filesystem::current_path();

        if (!boost::filesystem::exists(projectFolder / "CMakeLists.txt")) {
            throw std::runtime_error("Error: No CMake project detected on current folder.");
        }

        const CompilerDescription compilerDesc = compilerDetector->detect();

        const std::vector<std::string> buildTypes = {
            "Debug", "Release"
        };

        CMakeProject project {projectFolder};

        std::cout << "Configuring build" << std::endl;

        for (const std::string &buildType : buildTypes) {
            std::cout << "   " << buildType << " ..." << std::endl;

            CMakeBuildConfiguration config;

            config.generator = "Unix Makefiles";
            config.buildType = buildType;

            const boost::filesystem::path buildFolder = projectFolder / ".borc-cmake" / (compilerDesc.key + "-" + compilerDesc.version.toString()) / buildType;

            project.configure(buildFolder, config);
        }

        std::cout << "Build folder configuration done." << std::endl;
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

        controller.dispatch(subcommand);

		return 0;
    } catch (const std::exception &exp) {
        std::cerr << "Error: " << exp.what() << std::endl;

        return 1;    
    }
}

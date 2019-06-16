
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/filesystem/path.hpp>
#include <boost/process.hpp>

#include <felide/Version.hpp>

struct CompilerDescription {
    std::string key;
    std::string name;
    std::string target;
    std::string threadModel;
    felide::Version version;
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

    void test() {
        boost::process::ipstream pipeStream;
        boost::process::child childProcess {"gcc --version", boost::process::std_out > pipeStream};

        std::string line;

        while (pipeStream && std::getline(pipeStream, line) && !line.empty()) {
            std::cout << "LINE: " << line << std::endl;
        }

        childProcess.wait();

    }

    void configureBuildDirectory(boost::filesystem::path directory, const CMakeBuildConfiguration &configuration) {
        buildConfigurationMap[directory] = configuration;
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
    int showHelp() {
        std::cout << "Syntax:" << std::endl;
        std::cout << "    borc subcommand --options" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Available subcommands:" << std::endl;

        for (const SubcommandDesc &sd : subcommands) {
            std::cout << "    " << sd.switch_ << ": " << sd.description << std::endl;
        }

        std::cout << std::endl;
        std::cout << "For specific use for a subcommand, use the --help switch, like:" << std::endl;
        std::cout << "    borc setup --help" << std::endl;

        return 0;
    }

    int setup() {
        return 0;
    }

private:
    struct SubcommandDesc {
        std::string switch_;
        std::string description;
    };

    const std::vector<SubcommandDesc> subcommands = {
        {"build", "Builds all the modules for the current project"},
        {"setup", "Setup a specific toolchain for use in the current project"},
        {"run", "Run an executable, optionally debugging it"}
    };
};

int main(int argc, char *argv[]) {
    CMakeProject project{boost::filesystem::current_path()};

    project.test();

    if (argc < 2) {
        std::cout << "Borc Build System 0.0" << std::endl;
        std::cout << "Error: No options specified. Use borc --help for help." << std::endl;

        return 1;
    }

    CliCMakeController controller;

    const std::string subcommand = argv[1];

    if (subcommand == "--help") {
        return controller.showHelp();
    }

    return 0;
}

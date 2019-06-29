
#include "CliCMakeController.hpp"

#include "CMakeProject.hpp"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

namespace felide {
    CliCMakeController::CliCMakeController(CompilerDetector *compilerDetector) {
        this->compilerDetector = compilerDetector;
    }

    void CliCMakeController::dispatch(const std::string &subcommand, const std::vector<std::string> &params) {
        if (subcommand == "--help") {
            this->showHelp();
        } else if (subcommand == "configure") {
            this->configure(params);
        } else if (subcommand == "build") {
            this->build(params);
        } else {
            throw std::runtime_error("Unknown command '" + subcommand + "' specified.");
        }
    }

    void CliCMakeController::showHelp() {
        const std::string helpString = R"(
Syntax:
    felcli subcommand --options

Available subcommands:
    configure   Setup a specific toolchain for use in the current project
    build       Build all the targets within the current project
    run         Run an executable, optionally debugging it

For specific use for a subcommand, use the --help switch. For example:
    felcli setup --help
)";
        std::cout << helpString;
    }

    void CliCMakeController::configure(const std::vector<std::string> &params) {
        if (! this->isCMakeProject(boost::filesystem::current_path())) {
            throw std::runtime_error("Only CMake projects are supported for now");
        }

        if (params.size() == 0) {
            throw std::runtime_error("Missing build configuration (Debug, Release)");
        }

        CMakeProject project {boost::filesystem::current_path(), compilerDetector};

        project.configure(params[0]);
    }

    void CliCMakeController::build(const std::vector<std::string> &params) {
        if (! this->isCMakeProject(boost::filesystem::current_path())) {
            throw std::runtime_error("Only CMake projects are supported for now");
        }

        if (params.size() == 0) {
            throw std::runtime_error("Missing build configuration (Debug, Release)");
        }

        CMakeProject project {boost::filesystem::current_path(), compilerDetector};

        project.build(params[0]);
    }

    bool CliCMakeController::isCMakeProject(const boost::filesystem::path &projectFolder) const {
        return boost::filesystem::exists(projectFolder / "CMakeLists.txt");
    }
}

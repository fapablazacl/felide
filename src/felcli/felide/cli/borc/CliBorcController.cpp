
#include "CliBorcController.hpp"

#include <iostream>

namespace felide {
    CliBorcController::CliBorcController(CompilerEnumeratorService *compilerEnumeratorService) : compilerEnumeratorService{compilerEnumeratorService} {

    }

    void CliBorcController::dispatch(const std::string &subcommand, const std::vector<std::string> &params) {
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

    void CliBorcController::showHelp() {
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

    void CliBorcController::configure(const std::vector<std::string> &params) {
        // writes the build information (compiler, etc) inside the build directory
    }

    void CliBorcController::build(const std::vector<std::string> &params) {

    }
}

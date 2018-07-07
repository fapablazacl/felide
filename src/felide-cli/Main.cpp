
#include <iostream>
#include <cxxopts.hpp>

#include "CliController.hpp"

int main(int argc, char *argv[]) {
    cxxopts::Options options("felide-cli", "Command Line Interface for managing build, testing and packaging");

    try {
        options.add_options()
            ("b,build", "Build using the current Toolset")
            ("c,clean", "Cleans the local build directory")
            ("h,help", "Shows this message")
        ;

        auto result = options.parse(argc, argv);

        std::cout << options.help() << std::endl;
        return 0;

    } catch (const cxxopts::OptionParseException &exp) {
        std::cout << exp.what() << std::endl;
        return 1;
    }
}

/*
#include <iostream>
#include <list>
#include <stdexcept>
#include <boost/program_options.hpp>
#include <experimental/filesystem>

#include "ConsoleApp.hpp"

namespace fs = std::experimental::filesystem;
namespace po = boost::program_options;

int dispatch(const po::variables_map &vm, const po::options_description &desc);

int main(int argc, char **argv) {
    try {
        auto desc = po::options_description("Allowed options");

        desc.add_options()
            ("init,i", "setup an initial project")
            ("build,b", "build the current project")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        return dispatch(vm, desc);

    } catch (const std::runtime_error &exp) {
        std::cout << "The following error occurred:" << std::endl;
        std::cout << exp.what() << std::endl;

        return 1;
    } catch (const std::exception &exp) {
        std::cout << "The following unexcepted error occurred:" << std::endl;
        std::cout << exp.what() << std::endl;

        return 2;
    } catch (...) {
        std::cout << "FATAL unknown error occurred." << std::endl;
        return 3;
    }
}

static std::unique_ptr<felide::ConsoleApp> createApp() {
    fs::path borcfile = fs::current_path() / "main.borc";

    if (!fs::exists(borcfile)) {
        throw std::runtime_error("A borcfile doesn't exist in the current path");
    }

    auto consoleApp = felide::ConsoleApp::create(borcfile.string());

    return consoleApp;
}

int dispatch(const po::variables_map &vm, const po::options_description &desc) {
    if (vm.count("init")) {
        
        
    } else if (vm.count("build")) {
        auto consoleApp = createApp();

        consoleApp->build("");
    } else {
        auto consoleApp = createApp();

        consoleApp->list();
    }

    return 0;
}
*/
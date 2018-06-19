
#include <iostream>
#include <list>
#include <stdexcept>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "ConsoleApp.hpp"

namespace fs = boost::filesystem;
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

static std::unique_ptr<borc::ConsoleApp> createApp() {
    fs::path borcfile = fs::current_path() / "main.borc";

    if (!fs::exists(borcfile)) {
        throw std::runtime_error("A borcfile doesn't exist in the current path");
    }

    auto consoleApp = borc::ConsoleApp::create(borcfile.string());

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

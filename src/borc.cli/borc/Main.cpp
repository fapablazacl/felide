
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <borc/cli/ProjectController.hpp>
#include <borc/core/Module.hpp>
#include <borc/core/Project.hpp>
#include <borc/core/ProjectFactory.hpp>
#include <borc/core/Toolchain.hpp>
#include <borc/core/ToolchainFactory.hpp>

namespace fs = boost::filesystem;

std::string getFullPath() {
    return (fs::current_path() / "Package.borc.json").string();
    // return "/home/fapablaza/Desktop/devwarecl/felide/Package.borc.json";
}

int main(int argc, char **argv) {
    namespace po = boost::program_options;

    using namespace borc;

    po::options_description desc("Allowed options");

    desc.add_options()
        ("build", po::value<std::string>(), "Build using the current Toolset")
        ("clean", "Cleans the local build directory")
        ("help", "Shows this message")
    ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;

        return 1;
    } else if (vm.count("build")) {
        const std::string fullPath = getFullPath();
        const auto projectFactory = ProjectFactory{};
        const auto project = projectFactory.createProject(fullPath);

        const auto toolchainFactory = ToolchainFactory::create();
        const auto toolchain = toolchainFactory->createToolchain(ToolchainFamily::GCC);

        ProjectController controller {project.get(), toolchain.get()};

        const std::string moduleName = vm["build"].as<std::string>();

        if (moduleName == "") {
            std::cout << "--build option must have a valid module Name" << std::endl;
            return 1;
        }

        controller.build(moduleName);

        return 0;
    } else if (vm.count("run")) {

    }

    std::cout << "No specified option. Try again with the --help option"  << std::endl;
    
    return 0;
}

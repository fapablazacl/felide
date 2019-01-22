
#include <string>
#include <boost/program_options.hpp>

#include <borc/cli/CliController.hpp>
#include <borc/core/Module.hpp>
#include <borc/core/Project.hpp>
#include <borc/core/ProjectFactory.hpp>
#include <borc/core/Toolchain.hpp>
#include <borc/core/ToolchainFactory.hpp>

#define XSTR(a) STR(a)
#define STR(a) #a

std::string getFullPath() {
    return XSTR(PROJECT_SOURCE_DIR);
}

int main(int argc, char **argv) {
    using namespace borc;

    const std::string fullPath = getFullPath();
    const auto projectFactory = ProjectFactory{};
    const auto project = projectFactory.createProject(fullPath);

    const auto toolchainFactory = ToolchainFactory::create();
    const auto toolchain = toolchainFactory->createToolchain(ToolchainFamily::GCC);

    CliController controller {project.get(), toolchain.get()};

    boost::program_options::options_description options("Alowed options:");

    options.add_options()
        ("b,build", "Build using the current Toolset")
        ("c,clean", "Cleans the local build directory")
        ("h,help", "Shows this message")
    ;

    return 0;
}

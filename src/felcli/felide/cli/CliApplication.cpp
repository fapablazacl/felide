
#include "CliApplication.hpp"
#include "CliController.hpp"

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

namespace felide {
    static const char s_AppTitle[] = "felide-cli";
    static const char s_AppDescription[] = "Command Line Interface for managing build, testing and packaging";

    class CliApplicationImpl : public CliApplication {
    public:
        explicit CliApplicationImpl(int argc, char **argv) : m_options("Allowed options:") {
            m_argc = argc;
            m_argv = argv;

            m_options.add_options()
                ("b,build", "Build using the current Toolset")
                ("c,clean", "Cleans the local build directory")
                ("h,help", "Shows this message")
            ;

            m_controller = CliController::create();
        }

        virtual ~CliApplicationImpl() {}

        virtual void run() override {
            po::variables_map vm;
            po::store(po::parse_command_line(m_argc, m_argv, m_options), vm);
            po::notify(vm);

            if (vm.count("build")) {
                m_controller->build();
            } else {
                std::cout << m_options << std::endl;
            }
        }
    
    private:
        po::options_description m_options;
        int m_argc = 0;
        char **m_argv = nullptr;
        std::unique_ptr<CliController> m_controller;
    };

    std::unique_ptr<CliApplication> CliApplication::create(int argc, char **argv) {
        return std::make_unique<CliApplicationImpl>(argc, argv);
    }
}


/*
#include <iostream>
#include <list>
#include <stdexcept>

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
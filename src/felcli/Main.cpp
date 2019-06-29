
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "felide/cli/GnuCompilerDetector.hpp"
#include "felide/cli/cmake/CliCMakeController.hpp"

int main(int argc, char *argv[]) {
    try {
		if (argc < 2) {
			throw std::runtime_error("No options specified. Use borc --help for help.");
		}

		felide::GnuCompilerDetector compilerDetector;
		felide::CliCMakeController controller {&compilerDetector};

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

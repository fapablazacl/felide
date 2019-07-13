
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "felide/cli/GnuCompilerDetector.hpp"
#include "felide/cli/cmake/CliCMakeController.hpp"

static std::vector<std::string> makeStringVectorFromArgs(int argc, char *argv[], const int offset) {
    std::vector<std::string> params;
    
    for (int i=offset; i<argc; i++) {
        params.push_back(argv[i]);
    }
    
    return params;
}

int main(int argc, char *argv[]) {
    try {
		if (argc < 2) {
			throw std::runtime_error("No options specified. Use borc --help for help.");
		}

		felide::GnuCompilerDetector compilerDetector;
		felide::CliCMakeController controller {&compilerDetector};

		const std::string subcommand = argv[1];
        const std::vector<std::string> params = makeStringVectorFromArgs(argc, argv, 2);
        
        controller.dispatch(subcommand, params);

		return 0;
    } catch (const std::exception &exp) {
        std::cerr << "Error: " << exp.what() << std::endl;

        return 1;    
    }
}

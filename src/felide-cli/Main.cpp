
#include <stdexcept>
#include <iostream>
#include "felide/cli/CliApplication.hpp"

int main(int argc, char **argv) {
    try {
        auto app = felide::CliApplication::create(argc, argv);

        app->run();

        return 0;
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
        return 1;
    }
}

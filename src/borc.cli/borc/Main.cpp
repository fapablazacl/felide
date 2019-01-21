
#include <string>
#include <borc/cli/CliController.hpp>

#define XSTR(a) STR(a)
#define STR(a) #a

std::string getFullPath() {
    return XSTR(PROJECT_SOURCE_DIR);
}

int main(int argc, char **argv) {
    using namespace borc;

    const std::string fullPath = getFullPath();

    return 0;
}

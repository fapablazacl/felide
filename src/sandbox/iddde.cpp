
#include <string>
#include <vector>

namespace felide::model {
    struct Version {
        int major;
        int minor;
        int revision;
    };

    enum class LanguageId {
        cpp
    };

    struct Language {
        LanguageId id;
        std::vector<std::string> dialects;
    };

    struct Target {
        std::string name;
        std::string path;
        Language *language;
        std::vector<std::string> files;
    };

    struct Project {
        std::string name;
        std::string absolutePath;
        std::vector<Target> targets;
    };

    struct Compiler {
        
    };

    struct Linker {
        
    };

    struct Toolchain {
        std::string name;
        Version version;
        std::string installationPath;

        std::vector<Compiler> compilers;
        std::vector<Linker> linkers;
    };
}

int main(int argc, char **argv) {

    return 0;
}

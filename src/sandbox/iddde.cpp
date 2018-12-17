
#include <string>
#include <vector>
#include <map>
#include <memory>

// Project Model for C/C++ projects
namespace borc::model {
    enum class ModuleType {
        Libary,
        Executable
    };

    class Project;

    class Module {
    public:
        Module(Project *parent, const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files) {
            this->parentProject = parent;
            this->name = name;
            this->type = type;
            this->path = path;
            this->files = files;
        }

        Module(Project *parent, const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files, const std::vector<Module*> &dependencies) {
            this->parentProject = parent;
            this->name = name;
            this->type = type;
            this->path = path;
            this->files = files;
            this->dependencies = dependencies;
        }

    private:
        //! parent project of the module
        Project *parentProject = nullptr;

        //! name of the target
        std::string name;

        //! the type of the module
        ModuleType type = ModuleType::Executable;

        //! relative path to the parent project
        std::string path;

        //! list of files that compose the module
        std::vector<std::string> files;

        //! list of module libraries that this module depends on
        std::vector<Module*> dependencies;
    };

    class Project {
    public:

    private:
        //! The name of the project
        std::string name;

        //! The full path to the project directory
        std::string fullPath;

        //! The list of software modules this project has
        std::vector<std::unique_ptr<Module>> modules;
    };

    class Compiler {
    public:
        
    };

    class Linker {
    public:
        
    };

    class Toolchain {
    public:
        //! The name displayed to the user 
        std::string name;

        //! Installation path
        std::string path;

        //! List of compilers
        std::vector<Compiler> compilers;

        //! List of linkers
        std::vector<Linker> linkers;
    };

    class BuildService {
    public:

    };
}

int main(int argc, char **argv) {

    return 0;
}

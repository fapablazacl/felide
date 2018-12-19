
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <filesystem>
#include <regex>

// Project Model for C/C++ projects
namespace borc::model {
    enum class ModuleType {
        Library,
        Executable
    };

    inline std::string toString(const ModuleType type) {
        switch (type) {
            case ModuleType::Executable: 
                return "executable";

            case ModuleType::Library:
                return "library";

            default:
                return "<unknown ModuleType>";
        }
    }

    class Project;

    class Module {
    public:
        Module(Project *parent, const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files, const std::vector<Module*> &dependencies) {
            this->parentProject = parent;
            this->name = name;
            this->type = type;
            this->path = path;
            this->files = files;
            this->dependencies = dependencies;
        }

        std::string getName() const {
            return name;
        }

        std::string getPath() const {
            return path;
        }

        std::vector<std::string> getFiles() const {
            return files;
        }

        ModuleType getType() const {
            return type;
        }

        const Project *getParentProject() const {
            return parentProject;
        }

        std::vector<Module*> getDependencies() const {
            return dependencies;
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
        Project(const std::string &name, const std::string &fullPath) {
            this->name = name;
            this->fullPath = fullPath;
        }

        Module* addModule(const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files) {
            return this->addModule(name, type, path, files, {});
        }
        
        Module* addModule(const std::string &name, ModuleType type, const std::string &path, const std::vector<std::string> &files, const std::vector<Module*> &dependencies) {
            auto module = new Module(this, name, type, path, files, dependencies);

            modules.emplace_back(module);

            return module;
        }

        std::string getName() const {
            return name;
        }

        std::string getFullPath() const {
            return fullPath;
        }

        std::vector<const Module*> getModules() const {
            std::vector<const Module*> modules;

            for (const auto &module : this->modules) {
                modules.push_back(module.get());
            }

            return modules;
        }

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
        std::string compile(const Project *project, const Module *module, const std::string &file) const {
            std::cout << "    " << file  << " ..." << std::endl;
            return file + ".obj";
        }
    };

    class Linker {
    public:
        std::string link(const Project *project, const Module *module, const std::vector<std::string> &objectFiles) const {
            const std::string moduleTypeStr = toString(module->getType());
            std::cout << "Linking " << moduleTypeStr << " module " << module->getName() << " ..." << std::endl;

            if (module->getType() == ModuleType::Library) {
                return "lib" + module->getName() + ".a";
            } else {
                return module->getName();
            }
        }
    };

    class BuildService {
    private:
        Compiler compiler;
        Linker linker;

        //! list of extension wildcards that will trigger a source file compilation 
        const std::vector<std::string> compilerWildcards = {
            "*.c", "*.cpp", "*.c++", "*.cc", "*.cxx", 
        };

    public:
        void buildProject(const Project *project) {
            auto modules = project->getModules();

            int builtModules = 0;

            for (const Module *module : modules) {
                std::cout << "Building module " << module->getName() << " ..." << std::endl;

                const auto files = module->getFiles();

                std::vector<std::string> objectFiles;

                for (const std::string &file : files) {
                    if (!this->isFileCompilable(file)) {
                        continue;
                    }

                    const std::string objectFile = compiler.compile(project, module, file);
                    objectFiles.push_back(objectFile);
                }

                linker.link(project, module, objectFiles);

                builtModules++;
            }

            std::cout << "Built " << builtModules << " module(s)." << std::endl;
        }

    private:
        bool isFileCompilable(const std::string &file) const {
            namespace fs = std::filesystem;
            const std::string ext = "*" + fs::path(file).extension().string();

            auto it = std::find(compilerWildcards.begin(), compilerWildcards.end(), ext);

            return it != compilerWildcards.end();
        }
    };
}

#define XSTR(a) STR(a)
#define STR(a) #a

int main(int argc, char **argv) {
    using namespace borc::model;

    const std::string fullPath = XSTR(PROJECT_SOURCE_DIR);

    Project borcProject{"borc", fullPath};

    Module *borcCoreModule = borcProject.addModule("borc.core", ModuleType::Library, "borc.core", {
        "BuildService.hpp", "BuildService.cpp",
        "Module.hpp", "Module.cpp",
        "Project.hpp", "Project.cpp",
        "Compiler.hpp", "Compiler.cpp",
        "Linker.hpp", "Linker.cpp"
    });

    Module *borcCliModule = borcProject.addModule("borc.cli", ModuleType::Executable, "borc.cli", {
        "Main.cpp"
    }, {borcCoreModule});

    BuildService buildService;

    buildService.buildProject(&borcProject);

    return 0;
}

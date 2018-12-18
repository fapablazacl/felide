
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>

// Project Model for C/C++ projects
namespace borc::model {
    enum class ModuleType {
        Libary,
        Executable
    };

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


    class BuildService {
    public:
        void buildProject(const Project *project) {
            auto modules = project->getModules();

            for (const Module *module : modules) {
                const std::string moduleName = module->getName();
                std::cout << "Building module " << moduleName << " ..." << std::endl;

                const auto files = module->getFiles();

                for (const std::string &file : files) {
                    std::cout << "    " << file  << "..." << std::endl;
                }

                std::cout << "Linking module " << moduleName << " ..." << std::endl;
                std::cout << "Built 1 module." << std::endl;
            }
        }
    };
}

#define XSTR(a) STR(a)
#define STR(a) #a

int main(int argc, char **argv) {
    using namespace borc::model;

    const std::string fullPath = XSTR(PROJECT_SOURCE_DIR);

    Project borcProject{"borc", fullPath};

    Module *borcCliModule = borcProject.addModule("borc.cli", ModuleType::Executable, "borc.cli", {
        "Main.cpp"
    });

    BuildService buildService;

    buildService.buildProject(&borcProject);

    return 0;
}

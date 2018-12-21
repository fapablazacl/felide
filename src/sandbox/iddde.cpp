
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <filesystem>
#include <regex>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>

namespace fs = std::filesystem;

// Project Model for C/C++
namespace borc::model {
    std::string join(const std::vector<std::string> &strings, const std::string &separator) {
        std::string str;

        for (const std::string &string : strings) {
            str += string;
            str += separator;
        }

        return str;
    }

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

    inline std::string computeModuleFileName(const Module *module) {
        if (module->getType() == ModuleType::Library) {
            // return "lib" + module->getName() + ".dylib";
            return "lib" + module->getName() + ".so";
        } else {
            return module->getName();
        }
    }

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

    class Command {
    public:
        explicit Command(const std::string &base) 
            : _base(base) {}

        explicit Command(const std::string &base, const std::vector<std::string> &options) 
            : _base(base), _options(options) {}

        void execute() {
            const std::string systemCommand = _base + " " + join(_options, " ");
            const int exitCode = std::system(systemCommand.c_str());

            if (exitCode != 0) {                
                throw std::runtime_error("The command returned an erroneous exit code: " + std::to_string(exitCode));
            }
        }

        void addOption(const std::string &option) {
            _options.push_back(option);
        }

        template<typename Iterator>
        void addOptionRange(Iterator begin, Iterator end) {
            _options.insert(_options.begin(), begin, end);
        }

    private:
        const std::string _base;
        std::vector<std::string> _options;
    };

    class Compiler {
    private:
        std::string commandPath;

    public:
        explicit Compiler(const std::string &commandPath) {
            this->commandPath = commandPath;
        }

        std::string compile(const Project *project, const Module *module, const std::string &file) const {
            const fs::path sourceFilePath = this->computeSourceFilePath(project, module, file);
            const fs::path objectFilePath = this->computeObjectFilePath(project, module, file);

            std::cout << "    " << file  << " ..." << std::endl;

            Command command {
                commandPath, {
                    "-O0", "-g", "-c", sourceFilePath.string(),
                    "-o" + objectFilePath.string(),
                }
            };

            command.execute();

            // const std::string cmd = commandPath + " -O0 -g -c " + sourceFilePath.string() + " -o" + objectFilePath.string();
            // std::system(cmd.c_str());
            // std::cout << cmd << std::endl;

            return objectFilePath;
        }

    private:
        fs::path computeSourceFilePath(const Project *project, const Module *module, const std::string &file) const {
            return fs::path(project->getFullPath()) / fs::path(module->getPath()) / fs::path(file);
        }

        fs::path computeObjectFilePath(const Project *project, const Module *module, const std::string &file) const {
            return fs::path(project->getFullPath()) / fs::path(".borc") / fs::path(module->getPath()) / fs::path(file +  ".obj");
        }
    };

    class Linker {
    private:
        std::string commandPath;

    public:
        explicit Linker(const std::string &commandPath) {
            this->commandPath = commandPath;
        }

        std::string link(const Project *project, const Module *module, const std::vector<std::string> &objectFiles) const {
            std::cout << "Linking " << toString(module->getType()) << " module " << module->getName() << " ..." << std::endl;

            const std::string outputModuleFilePath = this->computeModuleOutputFilePath(project, module).string();
            const auto librariesOptions = this->computeImportLibrariesOptions(project, module);

            Command command { commandPath };

            if (module->getType() == ModuleType::Library) {
                command.addOption("-shared");
            }
            
            command.addOptionRange(objectFiles.begin(), objectFiles.end());
            command.addOptionRange(librariesOptions.begin(), librariesOptions.end());
            command.addOption("-o" + outputModuleFilePath);

            // std::string sharedOption = module->getType() == ModuleType::Library ? " -shared " : " ";
            // const std::string cmd = commandPath + sharedOption + objectFilesStr + " -o" + outputModuleFilePath + " " + librariesOptions;
            // std::cout << cmd << std::endl;
            // std::system(cmd.c_str());

            return outputModuleFilePath;
        }

    private:
        std::vector<std::string> computeImportLibrariesOptions(const Project *project, const Module *module) const {
            std::vector<std::string> options = {
                "-lstdc++", "-lstdc++fs"
            };

            const auto dependencies = module->getDependencies();

            for (const Module *dependency : dependencies) {
                const std::string importLibrary = dependency->getName();
                options.push_back("-l" + importLibrary);

                const std::string importLibraryDir = this->computeModuleOutputPath(project, dependency);
                options.push_back("-L" + importLibraryDir);
            }

            return options;
        }

        fs::path computeModuleOutputPath(const Project *project, const Module *module) const {
            return fs::path(project->getFullPath()) / fs::path(".borc") / fs::path(module->getPath());
        }

        fs::path computeModuleOutputFilePath(const Project *project, const Module *module) const {
            return this->computeModuleOutputPath(project, module) / fs::path(computeModuleFileName(module));
        }
    };

    class BuildService {
    private:
        Compiler compiler;
        Linker linker;

        //! list of extension wildcards that will trigger a source file compilation with the current compiler
        const std::vector<std::string> compilerWildcards = {
            "*.c", "*.cpp", "*.c++", "*.cc", "*.cxx", 
        };

    public:
        explicit BuildService(const std::string &commandPath) 
            : compiler(commandPath), linker(commandPath) {}

        void buildProject(const Project *project) {
            auto modules = project->getModules();

            int builtModules = 0;

            for (const Module *module : modules) {
                std::cout << "Building module " << module->getName() << " ..." << std::endl;

                const auto files = module->getFiles();

                std::vector<std::string> objectFiles;
                std::copy_if(files.begin(), files.end(), std::back_inserter(objectFiles), [&](const auto &file) {
                    return this->isFileCompilable(file);
                });

                std::transform(objectFiles.begin(), objectFiles.end(), objectFiles.begin(), [&](const auto &file) {
                    return this->compiler.compile(project, module, file);
                });

                linker.link(project, module, objectFiles);

                builtModules++;
            }

            std::cout << "Built " << builtModules << " module(s)." << std::endl;
        }

    private:
        bool isFileCompilable(const std::string &file) const {
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

    Module *borcCoreModule = borcProject.addModule("borc.core", ModuleType::Library, "src/borc.core", {
        "BuildService.hpp", 
        "BuildService.cpp",
        "Module.hpp", 
        "Module.cpp",
        "Project.hpp", 
        "Project.cpp",
        "Compiler.hpp", 
        "Compiler.cpp",
        "Linker.hpp", 
        "Linker.cpp"
    });

    Module *borcCliModule = borcProject.addModule("borc.cli", ModuleType::Executable, "src/borc.cli", {
        "Main.cpp"
    }, {borcCoreModule});

    // const std::string commandPath = "/usr/local/Cellar/gcc/8.2.0/bin/gcc-8";
    const std::string commandPath = "gcc";

    BuildService buildService(commandPath);
    buildService.buildProject(&borcProject);

    return 0;
}

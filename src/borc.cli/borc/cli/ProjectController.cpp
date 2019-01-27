
#include "ProjectController.hpp"

#include <iostream>
#include <algorithm>
#include <borc/core/Module.hpp>
#include <borc/core/Project.hpp>
#include <borc/dag/NodeRepository.hpp>
#include <borc/dag/BuildGraphGenerator.hpp>

namespace borc {
    ProjectController::ProjectController(Project *project, Toolchain *toolchain) {
        this->project = project;
        this->toolchain = toolchain;
    }

    ProjectController::~ProjectController() {}

    void ProjectController::build(const std::string &moduleName) {
        NodeRepository nodeRepository;
        BuildGraphGenerator buildGraphGenerator {&nodeRepository, toolchain};

        auto modules = project->getModules();

        auto moduleIt = std::find_if(modules.begin(), modules.end(), [moduleName](auto module) {
            return module->getName() == moduleName;
        });

        if (moduleIt == modules.end()) {
            std::cout << "Module " << moduleName << " not found" << std::endl;
            return;
        }

        const Module *module = *moduleIt;

        // compute build generation graph
        auto moduleNode = buildGraphGenerator.generateGraph(module);

        return;
        
        /*
        auto borcCliModuleNode = buildGraphGenerator.generateGraph(borcCliModule);
        auto borcCoreModuleNode = buildGraphGenerator.generateGraph(borcCoreModule);
        */
        
        // BuildService buildService = serviceFactory.createBuildService();
        // buildService.buildProject(&borcProject);

        // RunService runService = serviceFactory.createRunService();
        // runService.runModule(borcCliModule);
    }

    void ProjectController::clean() {
        std::cout << "ProjectController::clean" << std::endl;
    }

    void ProjectController::run() {
        std::cout << "ProjectController::run" << std::endl;
    }
}

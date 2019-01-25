
#include "CliController.hpp"

#include <iostream>
#include <borc/core/Module.hpp>
#include <borc/core/Project.hpp>
#include <borc/dag/NodeRepository.hpp>
#include <borc/dag/BuildGraphGenerator.hpp>

namespace borc {
    CliController::CliController(Project *project, Toolchain *toolchain) {
        this->project = project;
        this->toolchain = toolchain;
    }

    CliController::~CliController() {}

    void CliController::build(const std::string &moduleName) {
        NodeRepository nodeRepository;
        BuildGraphGenerator buildGraphGenerator {&nodeRepository, toolchain};

        const Module *module = nullptr;

        for (auto *module_ : project->getModules()) {
            if (module_->getName() == moduleName) {
                module = module_;
                break;
            }
        }

        if (!module) {
            std::cout << "Module " << moduleName << " not found" << std::endl;
            return;
        }
        
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

    void CliController::clean() {
        std::cout << "CliController::clean" << std::endl;
    }

    void CliController::run() {
        std::cout << "CliController::run" << std::endl;
    }
}

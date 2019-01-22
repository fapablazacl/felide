
#include "CliController.hpp"

#include <iostream>
#include <borc/dag/NodeRepository.hpp>
#include <borc/dag/BuildGraphGenerator.hpp>

namespace borc {
    CliController::CliController(Project *project, Toolchain *toolchain) {
        this->project = project;
        this->toolchain = toolchain;
    }

    CliController::~CliController() {}

    void CliController::build() {
        std::cout << "CliController::build" << std::endl;

        NodeRepository nodeRepository;
        BuildGraphGenerator buildGraphGenerator {&nodeRepository, toolchain};

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

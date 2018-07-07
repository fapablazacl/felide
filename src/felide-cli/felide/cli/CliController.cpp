
#include "CliController.hpp"

#include <iostream>
#include <felide/FileTypeRegistry.hpp>
#include <felide/TreeNode.hpp>
#include <felide/pom/Project.hpp>
#include <felide/pom/Target.hpp>
#include <felide/pom/TargetAction.hpp>
#include <felide/pom/Source.hpp>
#include <felide/pom/ProjectParserYaml.hpp>
#include <felide/tasks/Task.hpp>
#include <felide/tasks/TaskNodeVisitor.hpp>
#include <felide/toolsets/cpp/ToolsetCpp.hpp>

namespace felide {
    class CliControllerImpl : public CliController {
    public:
        explicit CliControllerImpl() {
            // m_path = path;
            m_registry = FileTypeRegistry::create();
            m_toolset = ToolsetCpp::create(m_registry.get());
        }

        virtual void list() override {
            auto project = this->parseProject();
            auto targets = project->getTargets();

            std::cout << "Available targets:" << std::endl;

            for (Target *target : targets) {
                std::cout << "  * " << target->getName() << std::endl;
            }
        }
        
        virtual void build() override {
            auto project = this->parseProject(); 
            auto taskTree = project->createTask(TargetAction::Build);
            auto taskVisitor = TaskNodeVisitor::create();
    
            taskVisitor->visit(taskTree.get(), [](Task *task) {
                if (task) {
                    task->perform();
                }
            });
        }

        virtual void init() override {
            throw std::runtime_error("The init action isn't implemented yet!");
        }

    private:
        std::unique_ptr<Project> parseProject() {
            auto parser = ProjectParserYaml::create();
            auto project = parser->parse(m_path);

            auto targets = project->getTargets();
            for (Target* target : targets) {
                target->setToolset(m_toolset.get());
            }

            return project;
        }

    private:
        std::string m_path;
        std::unique_ptr<FileTypeRegistry> m_registry;
        std::unique_ptr<ToolsetCpp> m_toolset;
    };

    std::unique_ptr<CliController> CliController::create() {
        return std::make_unique<CliControllerImpl>();
    }
}

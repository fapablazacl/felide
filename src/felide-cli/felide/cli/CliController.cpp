
#include "CliController.hpp"

#include <iostream>
#include <experimental/filesystem>
#include <felide/FileTypeRegistry.hpp>
#include <felide/TreeNode.hpp>
#include <felide/pom/Project.hpp>
#include <felide/pom/Target.hpp>
#include <felide/pom/TargetAction.hpp>
#include <felide/pom/Source.hpp>
#include <felide/pom/ProjectParserYaml.hpp>
#include <felide/tasks/Task.hpp>
#include <felide/tasks/TaskNodeVisitor.hpp>
#include <felide/cpp/ModuleToolset.hpp>

namespace fs = std::experimental::filesystem;

namespace felide {
    class CliControllerImpl : public CliController {
    public:
        explicit CliControllerImpl() {
            m_registry = FileTypeRegistry::create();

            if (m_path == "") {
                m_path = fs::current_path() / "project.borc";
            }

            if (!fs::exists(m_path)) {
                throw std::runtime_error("Error: supplied project file 'project.borc' doesn't exists");
            }

            m_toolset = ModuleToolset::create(m_path, {
                
            });
        }

        virtual void list() override {
            auto project = this->deserializeProject();
            auto targets = project->getTargets();

            std::cout << "Available targets:" << std::endl;

            for (Target *target : targets) {
                std::cout << "  * " << target->getName() << std::endl;
            }
        }
        
        virtual void build() override {
            // 1. Parse the current directory and find a Borcfile.
            auto project = this->deserializeProject(); 
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
        std::unique_ptr<Project> deserializeProject() {
            auto parser = ProjectParserYaml::create();
            auto project = parser->parse(m_path);
            auto targets = project->getTargets();

            for (Target* target : targets) {
                target->setToolset(m_toolset.get());
            }

            return project;
        }

    private:
        fs::path m_path;
        std::unique_ptr<FileTypeRegistry> m_registry;
        std::unique_ptr<ModuleToolset> m_toolset;
    };

    std::unique_ptr<CliController> CliController::create() {
        return std::make_unique<CliControllerImpl>();
    }
}

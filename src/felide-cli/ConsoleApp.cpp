
#include "ConsoleApp.hpp"

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
#include <felide/toolsets/ToolsetCpp.hpp>

namespace felide {
    class ConsoleAppImpl : public ConsoleApp {
    public:
        explicit ConsoleAppImpl(const std::string &path) {
            m_path = path;
            m_registry = felide::FileTypeRegistry::create();
            m_toolset = felide::ToolsetCpp::create(m_registry.get());
        }

        virtual void list() override {
            auto project = this->parseProject();
            auto targets = project->getTargets();

            std::cout << "Available targets:" << std::endl;

            for (Target *target : targets) {
                std::cout << "  * " << target->getName() << std::endl;
            }
        }
        
        virtual void build(const std::string &targetName) override {
            auto project = this->parseProject(); 
            auto taskTree = project->createTask(felide::TargetAction::Build);
            auto taskVisitor = felide::TaskNodeVisitor::create();
    
            taskVisitor->visit(taskTree.get(), [](felide::Task *task) {
                if (task) {
                    task->perform();
                }
            });
        }

        virtual void init() override {
            throw std::runtime_error("The init action isn't implemented yet!");
        }

    private:
        std::unique_ptr<felide::Project> parseProject() {
            auto parser = felide::ProjectParserYaml::create();
            auto project = parser->parse(m_path);
    
            auto targets = project->getTargets();
            for (felide::Target* target : targets) {
                target->setToolset(m_toolset.get());
            }

            return project;
        }

    private:
        std::string m_path;
        std::unique_ptr<felide::FileTypeRegistry> m_registry;
        std::unique_ptr<felide::ToolsetCpp> m_toolset;
    };

    std::unique_ptr<ConsoleApp> ConsoleApp::create(const std::string &path) {
        return std::make_unique<ConsoleAppImpl>(path);
    }
}


#include "ConsoleApp.hpp"

#include <iostream>
#include <Felide/FileTypeRegistry.hpp>
#include <Felide/TreeNode.hpp>
#include <Felide/POM/Project.hpp>
#include <Felide/POM/Target.hpp>
#include <Felide/POM/TargetAction.hpp>
#include <Felide/POM/Source.hpp>
#include <Felide/POM/ProjectParserYaml.hpp>
#include <Felide/Tasks/Task.hpp>
#include <Felide/Tasks/TaskNodeVisitor.hpp>
#include <Felide/Toolsets/ToolsetCpp.hpp>

namespace borc {
    class ConsoleAppImpl : public ConsoleApp {
    public:
        explicit ConsoleAppImpl(const std::string &path) {
            m_path = path;
            m_registry = borc::FileTypeRegistry::create();
            m_toolset = borc::ToolsetCpp::create(m_registry.get());
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
            auto taskTree = project->createTask(borc::TargetAction::Build);
            auto taskVisitor = borc::TaskNodeVisitor::create();
    
            taskVisitor->visit(taskTree.get(), [](borc::Task *task) {
                if (task) {
                    task->perform();
                }
            });
        }

        virtual void init() override {
            throw std::runtime_error("The init action isn't implemented yet!");
        }

    private:
        std::unique_ptr<borc::Project> parseProject() {
            auto parser = borc::ProjectParserYaml::create();
            auto project = parser->parse(m_path);
    
            auto targets = project->getTargets();
            for (borc::Target* target : targets) {
                target->setToolset(m_toolset.get());
            }

            return project;
        }

    private:
        std::string m_path;
        std::unique_ptr<borc::FileTypeRegistry> m_registry;
        std::unique_ptr<borc::ToolsetCpp> m_toolset;
    };

    std::unique_ptr<ConsoleApp> ConsoleApp::create(const std::string &path) {
        return std::make_unique<ConsoleAppImpl>(path);
    }
}

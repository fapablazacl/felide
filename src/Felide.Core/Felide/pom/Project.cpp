
#include "Project.hpp"

#include <stdexcept>
#include <boost/filesystem.hpp>
#include <borc/TreeNode.hpp>
#include <borc/pom/TargetAction.hpp>
#include <borc/pom/ModuleTarget.hpp>
#include <borc/pom/Source.hpp>
#include <borc/tasks/Task.hpp>

namespace fs = boost::filesystem;

namespace borc {
    class ProjectImpl : public Project {
    public:
        explicit ProjectImpl(const std::string name, const std::string &path) {
            this->setName(name)->setPath(path);
        }
    
        virtual ~ProjectImpl() {}
    
        virtual std::vector<Target*> getTargets() const override {
            std::vector<Target*> targets;
            
            for (auto &target : m_targets) {
                targets.push_back(target.get());
            }
    
            return targets;
        }
    
        virtual Target* addTarget(std::unique_ptr<Target> targetPtr) override {
            assert(targetPtr->getProject() == this);

            auto target = targetPtr.release();

            m_targets.emplace_back(target);

            return target;
        }
    
        virtual std::string getName() const override {
            return m_name;
        }
    
        virtual Project* setName(const std::string &name) override {
            // TODO: Add validation
            m_name = name;

            return this;
        }

        virtual std::string getPath() const override {
            return m_path;
        }
    
        virtual Project* setPath(const std::string &path) override {
            // TODO: Add validation
            m_path = path;

            return this;
        }

        virtual Project* setup() override {
            if (!fs::is_directory(m_path)) {
                throw std::runtime_error("The current project path doesn't exist");
            }
            
            if (!fs::create_directory(this->getBuildPath())) {
                throw std::runtime_error("Couldn't create the .borc internal directory.");
            }

            return this;
        }

        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action) override {
            if (action == TargetAction::Build) {
                return this->createBuildTask();
            } else {
                throw std::runtime_error("Unsupported Action");
            }
        }

        virtual std::string getBuildPath() const override {
            return (fs::path(m_path) / ".borc").string();
        }

    private:
        std::unique_ptr<TreeNode<Task>> createBuildTask()  {
            // TODO: Take into account dependency management
            auto taskNode = std::make_unique<TreeNode<Task>>();

            for (auto &target : m_targets) {
                taskNode->insertChild(target->createTask(TargetAction::Build));
            }

            return taskNode;
        }

    private:
        std::string m_name;
        std::string m_path;
        std::vector<std::unique_ptr<Target>> m_targets;
    };

    std::unique_ptr<Project> Project::create(const std::string &name, const std::string &path) {
        return std::make_unique<ProjectImpl>(name, path);
    }
}

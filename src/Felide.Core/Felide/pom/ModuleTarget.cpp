
#include "ModuleTarget.hpp"

#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <borc/TreeNode.hpp>
#include <borc/Language.hpp>
#include <borc/pom/ModuleTargetType.hpp>
#include <borc/pom/Project.hpp>
#include <borc/pom/Source.hpp>
#include <borc/pom/TargetAction.hpp>
#include <borc/toolsets/Toolset.hpp>
#include <borc/tasks/Task.hpp>

namespace borc {

    enum class ModuleTargetSourceManagerStorage {
        Implicit, 
        Explicit
    };

    class ModuleTargetSourceManager {
    public:
        virtual ~ModuleTargetSourceManager() {}

        virtual ModuleTargetSourceManagerStorage getStorage() const = 0;

        virtual std::vector<const Source*> getSources() const = 0;
    };

    class ModuleTargetImpl : public ModuleTarget {
    public:
        explicit ModuleTargetImpl(Project *project) : m_project(project) {}

        virtual ~ModuleTargetImpl() {}

        virtual Project* getProject() const override {
            return m_project;
        }

        virtual ModuleTargetImpl* setName(const std::string &name) override {
            m_name = name;

            return this;
        }

        virtual std::string getName() const override {
            return m_name;
        }

        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action) override {
            if (!m_toolset) {
                throw std::runtime_error("This project doesn't have a toolset");
            }

            auto targetTaskNode = m_toolset->createTask(action, this);

            
            std::vector<Source> sources = this->getSources();
            for (Source &source : sources) {
                // TODO: Fix this definition of use of the concept of 'sources'
                if (!m_toolset->checkAction(action, &source)) {
                    continue;
                }

                auto sourceTaskNode = m_toolset->createTask(action, &source);

                targetTaskNode->insertChild(std::move(sourceTaskNode));
            }

            return targetTaskNode;
        }

        virtual std::vector<TargetAction> supportedActions() const override {
            return {TargetAction::Build};
        }

        virtual Language* getLanguage() const override {
            return m_language;
        }

        virtual ModuleTarget* setLanguage(Language *language) override {
            m_language = language;

            return this;
        }

        virtual ModuleTarget* setToolset(Toolset *toolset) override {
            m_toolset = toolset;

            return this;
        }

        virtual Toolset* getToolset() override {
            return m_toolset;
        }

        virtual std::string getPath() const override {
            return m_path;
        }

        virtual ModuleTargetImpl* setPath(const std::string &path) override {
            m_path = path;

            return this;
        }

        virtual ModuleTargetImpl* setType(const ModuleTargetType type) override {
            m_type = type;

            return this;
        }

        virtual ModuleTargetType getType() const override {
            return m_type;
        }

        virtual ModuleTargetImpl* addDependency(const Target *target) override {
            m_deps.push_back(target);

            return this;
        }

        virtual std::vector<const Target*> getDependencies() const override {
            return m_deps;
        }

        virtual std::vector<Source> getSources() const override {
            namespace fs = boost::filesystem;

            std::vector<Source> sources;

            fs::path fullpath = fs::path(m_project->getPath()) / fs::path(m_path);

            if (!fs::is_directory(fullpath)) {
                // TODO: Add target name and directory relative path
                throw std::runtime_error("The target directory isn't a directory");
            }

            for (auto &entry : boost::make_iterator_range(fs::recursive_directory_iterator(fullpath), {})) {
                fs::path sourcePath = entry.path();

                if (fs::is_directory(sourcePath)) {
                    continue;
                }

                sources.push_back(Source{sourcePath.string(), this});
            }

            return sources;
        }

    private:
        std::string m_name;
        std::string m_path;
        std::vector<const Target*> m_deps;
        Project *m_project = nullptr;
        Language *m_language = nullptr;
        Toolset *m_toolset = nullptr;
        ModuleTargetType m_type = ModuleTargetType::Program;
    };

    std::unique_ptr<ModuleTarget> ModuleTarget::create(Project *project) {
        return std::make_unique<ModuleTargetImpl>(project);
    }
}

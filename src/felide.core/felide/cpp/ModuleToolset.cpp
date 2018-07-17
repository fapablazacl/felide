
#include "ModuleToolset.hpp"
#include "ModuleCompiler.hpp"
#include "ModuleLinker.hpp"

#include <cassert>
#include <algorithm>
#include <iostream>
#include <stdexcept>

#include <felide/FileTypeRegistry.hpp>
#include <felide/TreeNode.hpp>
#include <felide/tasks/Task.hpp>
#include <felide/pom/Project.hpp>
#include <felide/pom/ModuleTarget.hpp>
#include <felide/pom/Source.hpp>
#include <felide/pom/TargetAction.hpp>

namespace felide {
    class ModuleToolsetImpl : public ModuleToolset {
    public:
        explicit ModuleToolsetImpl (const std::string &buildPath, const std::vector<CompilerDescription> &compilerDescriptions, const std::vector<LinkerDescription> &linkerDescriptions) {
            m_buildPath = buildPath;

            for (const auto &desc : compilerDescriptions) {
                m_compilers.emplace_back(new ModuleCompiler(this, desc));
            }

            for (const auto &desc : linkerDescriptions) {
                m_linkers.emplace_back(new ModuleLinker(this, desc));
            }
        }
    
        virtual ~ModuleToolsetImpl() {}

        virtual bool checkAction(const TargetAction action, const Source *source) const override {
            assert(source);

            if (action != TargetAction::Build) {
                throw std::runtime_error("Unsupported target action");   
            }

            return this->findCompiler(source);
        }

        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action, const Source *source, const CompilerActionContext &context) override {
            assert(source);

            if (!this->checkAction(action, source)) {
                throw std::runtime_error("Couldn't find a suitable compiler for " + source->getFileName());
            } 

            Compiler *compiler = this->findCompiler(source);

            return compiler->createTask(source, context);
        }

        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action, const ModuleTarget *target) override {
            assert(target);

            if (action != TargetAction::Build) {
                throw std::runtime_error("Unsupported target action");   
            }

            Linker* linker = this->findLinker(target);
            if (!linker) {
                throw std::runtime_error("Couldn't find a suitable linker");   
            }

            return linker->createTask(target, {"test"});
        }

        virtual std::string getBuildPath() const override {
            return m_buildPath;
        }

    private:
        Compiler *findCompiler(const Source *source) const {
            assert(source);

            for (auto &compiler : m_compilers) {
                if (compiler->isCompilable(source)) {
                    return compiler.get();
                }
            }

            return nullptr;
        }

        Linker* findLinker(const ModuleTarget *target) const {
            for (auto &linker : m_linkers) {
                if (linker->isLinkable(target)) {
                    return linker.get();
                }
            }

            return nullptr;
        }

    private:
        std::string m_buildPath;
        std::vector<std::unique_ptr<Compiler>> m_compilers;
        std::vector<std::unique_ptr<Linker>> m_linkers;
    };

    std::unique_ptr<ModuleToolset> ModuleToolset::create (
        const std::string &buildPath,
        const std::vector<CompilerDescription> &compilerDescriptions, 
        const std::vector<LinkerDescription> &linkerDescriptions) {

        return std::make_unique<ModuleToolsetImpl>(buildPath, compilerDescriptions, linkerDescriptions);
    }
}


#include "ModuleToolset.hpp"
#include "ModuleCompiler.hpp"
#include "ModuleLinker.hpp"

#include <cassert>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <boost/filesystem.hpp>

#include <felide/core/FileTypeRegistry.hpp>
#include <felide/core/TreeNode.hpp>
#include <felide/core/tasks/Task.hpp>
#include <felide/core/pom/Project.hpp>
#include <felide/core/pom/ModuleTarget.hpp>
#include <felide/core/pom/Source.hpp>
#include <felide/core/pom/TargetAction.hpp>

namespace fs = boost::filesystem;

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

        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action, const Source *source, const ActionContext &context) override {
            assert(source);

            if (!this->checkAction(action, source)) {
                throw std::runtime_error("Couldn't find a suitable compiler for " + source->getFileName());
            } 

            Compiler *compiler = this->findCompiler(source);

            return compiler->createTask(source, context);
        }

        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action, const ModuleTarget *target, const ActionContext &context) override {
            assert(target);

            if (action != TargetAction::Build) {
                throw std::runtime_error("Unsupported target action");   
            }

            Linker* linker = this->findLinker(target);
            if (!linker) {
                throw std::runtime_error("Couldn't find a suitable linker");   
            }

            std::vector<std::string> objectFiles;
            for (const Source& source : target->getSources()) {
                const Compiler *compiler = this->findCompiler(&source);

                if (!compiler) {
                    continue;
                }

                const CompilerDescription description = compiler->getDescription();

                const fs::path outputPath = source.computeOutputDirectory(this->getBuildPath());
                const fs::path targetFile = outputPath /  source.computeOutputFileName(description.outputExtension);

                objectFiles.push_back(targetFile.string());
            }

            return linker->createTask(target, objectFiles, context);
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
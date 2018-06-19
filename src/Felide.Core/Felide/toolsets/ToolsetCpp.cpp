
#include "ToolsetCpp.hpp"

#include <cassert>
#include <algorithm>
#include <iostream>
#include <stdexcept>

#include <borc/FileTypeRegistry.hpp>
#include <borc/TreeNode.hpp>
#include <borc/tasks/Task.hpp>
#include <borc/pom/Project.hpp>
#include <borc/pom/ModuleTarget.hpp>
#include <borc/pom/Source.hpp>
#include <borc/pom/TargetAction.hpp>
#include <borc/toolsets/CompilerCpp.hpp>
#include <borc/toolsets/LinkerCpp.hpp>

namespace borc {
    class ToolsetCppImpl : public ToolsetCpp {
    public:
        explicit ToolsetCppImpl(FileTypeRegistry *registry) {
            assert(registry);

            m_c_sourceFile = registry->addFileType("C Source File", {".c"});
            m_c_headerFile = registry->addFileType("C Header File", {".h"});
            m_cpp_sourceFile = registry->addFileType("C++ Source File", {".cpp", ".cxx", ".cc", ".c++"});
            m_cpp_headerFile = registry->addFileType("C++ Header File", {".hpp", ".hxx", ".hh", ".h++"});

            m_compilers.emplace_back(new CompilerCpp(registry, "cl", {m_c_sourceFile, m_cpp_sourceFile}));
            m_linkers.emplace_back(new LinkerCpp("link"));
        }
    
        virtual ~ToolsetCppImpl() {}

        virtual bool checkAction(const TargetAction action, const Source *source) const override {
            assert(source);

            if (action != TargetAction::Build) {
                throw std::runtime_error("Unsupported target action");   
            }

            return this->findCompiler(source);
        }

        virtual std::unique_ptr<TreeNode<Task>> createTask(const TargetAction action, const Source *source) override {
            assert(source);

            if (!this->checkAction(action, source)) {
                throw std::runtime_error("Couldn't find a suitable compiler for " + source->getFileName());
            } 

            Compiler *compiler = this->findCompiler(source);

            return compiler->createTask(source);
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
        std::vector<std::unique_ptr<Compiler>> m_compilers;
        std::vector<std::unique_ptr<Linker>> m_linkers;

        const FileType *m_c_sourceFile = nullptr;
        const FileType *m_c_headerFile = nullptr;
        const FileType *m_cpp_sourceFile = nullptr;
        const FileType *m_cpp_headerFile = nullptr;
    };

    std::unique_ptr<ToolsetCpp> ToolsetCpp::create(FileTypeRegistry *registry) {
        return std::make_unique<ToolsetCppImpl>(registry);
    }
}

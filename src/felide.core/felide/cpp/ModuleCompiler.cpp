
#include "ModuleCompiler.hpp"

#include <cassert>
#include <memory>
#include <experimental/filesystem>

#include <fmt/format.h>
#include <felide/util/Strings.hpp>

#include <felide/TreeNode.hpp>
#include <felide/tasks/Task.hpp>
#include <felide/tasks/LogTask.hpp>
#include <felide/pom/Source.hpp>

namespace fs = std::experimental::filesystem;

namespace felide {
    const std::string FELIDE_INPUT_FILE = "${InputFile}";
    const std::string FELIDE_OUTPUT_FILE = "${OutputFile}";

    ModuleCompiler::ModuleCompiler(const CompilerDescription &description) {
        m_description = description;

        m_supportedFileTypes = FileTypeRegistry::create();
        m_supportedFileTypes->addFileType("Compiler Language", m_description.inputExtensions);
    }

    ModuleCompiler::~ModuleCompiler() {}

    bool ModuleCompiler::isCompilable(const Source *source) const {
        assert(source);

        return m_supportedFileTypes->getFileType(source) != nullptr;
    }

    std::string ModuleCompiler::getToolName() const {
        return "<Not Implemented>";
    }

    std::string ModuleCompiler::getPath() const {
        return "<Not Implemented>";
    }

    std::unique_ptr<TreeNode<Task>> ModuleCompiler::createTask(const Source *source) {
        assert(source);

        const fs::path sourceFile = source->getFilePath();
        const fs::path targetFile = this->computeOutputSourceName(source);

        std::string command = m_description.compileTemplate;
        command = replace(command, FELIDE_INPUT_FILE, sourceFile.string());
        command = replace(command, FELIDE_OUTPUT_FILE, targetFile.string());

        return TreeNode<Task>::create(std::move(std::make_unique<LogTask>(command)));
    }

    std::string ModuleCompiler::computeOutputSourceName(const Source *source) const {
        const fs::path sourceFile = source->getFilePath();
        const fs::path targetFile = sourceFile.parent_path() / fs::path(source->getFileTitle() + m_description.outputExtension);

        return targetFile.string();
    }
}

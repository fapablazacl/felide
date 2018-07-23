
#include "ModuleCompiler.hpp"
#include "ModuleToolset.hpp"

#include <cassert>
#include <memory>
#include <experimental/filesystem>

#include <felide/util/Strings.hpp>

#include <felide/TreeNode.hpp>
#include <felide/tasks/CommandTask.hpp>
#include <felide/tasks/DirectoryTask.hpp>
#include <felide/tasks/LogTask.hpp>
#include <felide/pom/Source.hpp>
#include <felide/pom/Target.hpp>
#include <felide/pom/Project.hpp>

namespace fs = std::experimental::filesystem;

namespace felide {
    // TODO: Move these definitions to the compiler configuration structures
    const std::string FELIDE_INPUT_FILE = "${InputFile}";
    const std::string FELIDE_OUTPUT_FILE = "${OutputFile}";

    ModuleCompiler::ModuleCompiler(const ModuleToolset *toolset, const CompilerDescription &description) {
        m_toolset = toolset;
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

    std::unique_ptr<TreeNode<Task>> ModuleCompiler::createTask(const Source *source, const ActionContext &context) {
        assert(source);

        const fs::path sourceFile = source->getFilePath();
        const fs::path outputPath = source->computeOutputDirectory(m_toolset->getBuildPath());
        const fs::path targetFile = outputPath /  source->computeOutputFileName(m_description.outputExtension);
        
        std::string command = m_description.compileTemplate;
        command = replace(command, FELIDE_INPUT_FILE, sourceFile.string());
        command = replace(command, FELIDE_OUTPUT_FILE, targetFile.string());

        for (const auto &pair : context) {
            const std::string &key = pair.first;
            const std::string &value = pair.second;
            const std::string &option = m_description.keyOptionMap[key];

            command = replace(command, key, option + " " + value);
        }

        auto taskNode = TreeNode<Task>::create();
        taskNode->createChild(std::make_unique<DirectoryTask>(outputPath.string()));
        taskNode->createChild(std::make_unique<CommandTask>(command));

        return taskNode;
    }
}

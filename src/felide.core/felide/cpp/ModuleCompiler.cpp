
#include "ModuleCompiler.hpp"

#include <cassert>
#include <memory>
#include <experimental/filesystem>

#include <fmt/format.h>

#include <felide/TreeNode.hpp>
#include <felide/tasks/Task.hpp>
#include <felide/tasks/LogTask.hpp>
#include <felide/pom/Source.hpp>

namespace fs = std::experimental::filesystem;

namespace felide {
    ModuleCompiler::ModuleCompiler(const FileTypeRegistry *registry, const std::string &toolName, const std::set<const FileType*> &types) {
        assert(registry);

        m_registry = registry;
        m_toolName = toolName;
        m_supportedTypes = types;
    }

    ModuleCompiler::ModuleCompiler(const FileTypeRegistry *registry, const std::string &toolName, const std::set<const FileType*> &types, const std::string &path) {
        assert(registry);

        m_registry = registry;
        m_toolName = toolName;
        m_supportedTypes = types;
        m_path = path;
    }

    ModuleCompiler::~ModuleCompiler() {}

    bool ModuleCompiler::isCompilable(const Source *source) const {
        assert(source);

        const FileType *fileType = m_registry->getFileType(source);

        return m_supportedTypes.find(fileType) != m_supportedTypes.end();
    }

    std::string ModuleCompiler::getToolName() const {
        return m_toolName;
    }

    std::string ModuleCompiler::getPath() const {
        return m_path;
    }

    std::unique_ptr<TreeNode<Task>> ModuleCompiler::createTask(const Source *source) {
        assert(source);

        const std::string commandTemplate = "{0} {1} /O0 /c /o {2}";

        const fs::path sourceFile = source->getFilePath();
        const fs::path targetFile = this->computeOutputSourceName(source);

        const std::string cmd = fmt::format(commandTemplate, m_toolName, sourceFile.string(), targetFile.string());

        return TreeNode<Task>::create(std::move(std::make_unique<LogTask>(cmd)));
    }

    std::string ModuleCompiler::computeOutputSourceName(const Source *source) const {
        const fs::path sourceFile = source->getFilePath();
        const fs::path targetFile = fs::path(source->getFilePath()).parent_path() / fs::path(source->getFileTitle() + ".obj");

        return targetFile.string();
    }
}

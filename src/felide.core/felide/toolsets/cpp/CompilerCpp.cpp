
#include "CompilerCpp.hpp"

#include <cassert>
#include <memory>
#include <experimental/filesystem>

#include <fmt/format.h>

#include <felide/TreeNode.hpp>
#include <felide/tasks/Task.hpp>
#include <felide/tasks/LogTask.hpp>
#include <felide/pom/Source.hpp>

namespace felide {
    CompilerCpp::CompilerCpp(const FileTypeRegistry *registry, const std::string &toolName, const std::set<const FileType*> &types) {
        assert(registry);

        m_registry = registry;
        m_toolName = toolName;
        m_supportedTypes = types;
    }

    CompilerCpp::CompilerCpp(const FileTypeRegistry *registry, const std::string &toolName, const std::set<const FileType*> &types, const std::string &path) {
        assert(registry);

        m_registry = registry;
        m_toolName = toolName;
        m_supportedTypes = types;
        m_path = path;
    }

    CompilerCpp::~CompilerCpp() {}

    bool CompilerCpp::isCompilable(const Source *source) const {
        assert(source);

        const FileType *fileType = m_registry->getFileType(source);

        return m_supportedTypes.find(fileType) != m_supportedTypes.end();
    }

    std::string CompilerCpp::getToolName() const {
        return m_toolName;
    }

    std::string CompilerCpp::getPath() const {
        return m_path;
    }

    std::unique_ptr<TreeNode<Task>> CompilerCpp::createTask(const Source *source) {
        assert(source);

        namespace fs = std::experimental::filesystem;

        const std::string commandTemplate = "{0} {1} /O0 /c /o {2}";

        const fs::path sourceFile = source->getFilePath();
        const fs::path targetFile = fs::path(source->getFilePath()).parent_path() / fs::path(source->getFileTitle() + ".obj");

        const std::string cmd = fmt::format(commandTemplate, m_toolName, sourceFile.string(), targetFile.string());

        return TreeNode<Task>::create(std::move(std::make_unique<LogTask>(cmd)));
    }
}
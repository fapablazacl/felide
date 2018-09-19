
set (target "felide.core")

set (sources
    "felide/Core.hpp"
    "felide/Core.cpp"
    "felide/Version.hpp"
    "felide/Version.cpp"
	"felide/Language.hpp"
	"felide/Language.cpp"
	"felide/FileType.hpp"
    "felide/FileType.cpp"
	"felide/FileTypeRegistry.hpp"
    "felide/FileTypeRegistry.cpp"
	"felide/TreeNode.hpp"
    "felide/TreeNode.cpp"

    "felide/util/FileUtil.cpp"
	"felide/util/FileUtil.hpp"
    "felide/util/Strings.hpp"
    "felide/util/Strings.cpp"

    "felide/tasks/Task.hpp"
    "felide/tasks/Task.cpp"
    "felide/tasks/DirectoryTask.hpp"
    "felide/tasks/DirectoryTask.cpp"
	"felide/tasks/TaskNodeVisitor.hpp"
    "felide/tasks/TaskNodeVisitor.cpp"
	"felide/tasks/TaskNodeVisitorSerial.hpp"
    "felide/tasks/TaskNodeVisitorSerial.cpp"
    "felide/tasks/LogTask.hpp"
    "felide/tasks/LogTask.cpp"
    "felide/tasks/CommandTask.hpp"
    "felide/tasks/CommandTask.cpp"

	"felide/pom/TargetAction.hpp"
    "felide/pom/TargetAction.cpp"
	"felide/pom/Target.hpp"
    "felide/pom/Target.cpp"
	"felide/pom/ModuleTarget.hpp"
    "felide/pom/ModuleTarget.cpp"
	"felide/pom/ModuleTargetType.hpp"
    "felide/pom/ModuleTargetType.cpp"
    "felide/pom/Project.hpp"
    "felide/pom/Project.cpp"
    "felide/pom/Source.hpp"
    "felide/pom/Source.cpp"
    "felide/pom/ProjectParser.hpp"
    "felide/pom/ProjectParser.cpp"
    "felide/pom/ProjectParserMock.hpp"
    "felide/pom/ProjectParserMock.cpp"
    "felide/pom/ProjectParserYaml.hpp"
    "felide/pom/ProjectParserYaml.cpp"

    "felide/toolsets/ActionContext.hpp"
    "felide/toolsets/ActionContext.cpp"
    "felide/toolsets/Compiler.hpp"
    "felide/toolsets/Compiler.cpp"
    "felide/toolsets/Linker.hpp"
    "felide/toolsets/Linker.cpp"
    "felide/toolsets/Toolset.hpp"
    "felide/toolsets/Toolset.cpp"

    "felide/cpp/ModuleCompiler.hpp"
    "felide/cpp/ModuleCompiler.cpp"
	"felide/cpp/ModuleLinker.hpp"
    "felide/cpp/ModuleLinker.cpp"
	"felide/cpp/ModuleToolset.hpp"
    "felide/cpp/ModuleToolset.cpp"

    "felide/ui/EditorModel.hpp"
    "felide/ui/EditorModel.cpp"
    "felide/ui/MainWindowModel.hpp"
    "felide/ui/MainWindowModel.cpp"
    "felide/ui/MainWindowPresenter.hpp"
    "felide/ui/MainWindowPresenter.cpp"
    "felide/ui/MainWindowView.hpp"
    "felide/ui/MainWindowView.cpp"
    "felide/ui/Menu.hpp"
    "felide/ui/Menu.cpp"
    "felide/ui/EditorView.hpp"
    "felide/ui/EditorView.cpp"
    "felide/ui/EditorManagerView.hpp"
    "felide/ui/EditorManagerView.cpp"
    "felide/ui/DialogManagerView.hpp"
    "felide/ui/DialogManagerView.cpp"
    "felide/ui/FolderBrowserView.hpp"
    "felide/ui/FolderBrowserView.cpp"
)

add_library (${target} SHARED
	${sources}
)

target_link_libraries (
    ${target} 
    fmt
    ${Boost_LIBRARIES}
)

install(TARGETS ${target} DESTINATION "bin")


set (target "felide.core")

set (sources
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
    "felide/FileUtil.cpp"
	"felide/FileUtil.hpp"

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

    "felide/toolsets/Compiler.hpp"
    "felide/toolsets/Compiler.cpp"
    "felide/toolsets/Linker.hpp"
    "felide/toolsets/Linker.cpp"
    "felide/toolsets/Toolset.hpp"
    "felide/toolsets/Toolset.cpp"

    "felide/toolsets/cpp/CompilerCpp.hpp"
    "felide/toolsets/cpp/CompilerCpp.cpp"
	"felide/toolsets/cpp/LinkerCpp.hpp"
    "felide/toolsets/cpp/LinkerCpp.cpp"
	"felide/toolsets/cpp/ToolsetCpp.hpp"
    "felide/toolsets/cpp/ToolsetCpp.cpp"
)

add_library (${target} 
	${sources}
)

target_link_libraries (
    ${target} 
    fmt
)

install(TARGETS ${target} DESTINATION "bin")

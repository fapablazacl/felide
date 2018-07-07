
set (target "felide.core")
set (src )

set (src_felide
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
)

set (src_felide_tasks
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
)

set (src_felide_pom
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
)

set (src_felide_toolset
    "felide/toolsets/Compiler.hpp"
    "felide/toolsets/Compiler.cpp"
	"felide/toolsets/CompilerCpp.hpp"
    "felide/toolsets/CompilerCpp.cpp"
    "felide/toolsets/Linker.hpp"
    "felide/toolsets/Linker.cpp"
	"felide/toolsets/LinkerCpp.hpp"
    "felide/toolsets/LinkerCpp.cpp"
    "felide/toolsets/Toolset.hpp"
    "felide/toolsets/Toolset.cpp"
	"felide/toolsets/ToolsetCpp.hpp"
    "felide/toolsets/ToolsetCpp.cpp"
)

include_directories(${Boost_INCLUDE_DIRS})

source_group("\\"                   FILES ${src})
source_group("\\Felide"             FILES ${src_felide})
source_group("\\Felide\\Tasks"      FILES ${src_felide_tasks})
source_group("\\Felide\\POM"        FILES ${src_felide_pom})
source_group("\\Felide\\Toolsets"   FILES ${src_felide_toolset})

add_library (${target} 
	${src}
    ${src_felide}
    ${src_felide_tasks}
	${src_felide_pom}
    ${src_felide_toolset}
)

target_link_libraries (
    ${target} 
    fmt
)

install(TARGETS ${target} DESTINATION "bin")

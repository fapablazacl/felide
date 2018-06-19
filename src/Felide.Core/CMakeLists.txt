
# setup borc-core
include_directories("../Felide.Core/")

set (target "Felide.Core")
set (src )

set (src_felide
    "Felide/Version.hpp"
    "Felide/Version.cpp"
	"Felide/Language.hpp"
	"Felide/Language.cpp"
	"Felide/FileType.hpp"
    "Felide/FileType.cpp"
	"Felide/FileTypeRegistry.hpp"
    "Felide/FileTypeRegistry.cpp"
	"Felide/TreeNode.hpp"
    "Felide/TreeNode.cpp"
    "Felide/FileUtil.cpp"
	"Felide/FileUtil.hpp"
)

set (src_felide_tasks
    "Felide/Tasks/Task.hpp"
    "Felide/Tasks/Task.cpp"
    "Felide/Tasks/DirectoryTask.hpp"
    "Felide/Tasks/DirectoryTask.cpp"
	"Felide/Tasks/TaskNodeVisitor.hpp"
    "Felide/Tasks/TaskNodeVisitor.cpp"
	"Felide/Tasks/TaskNodeVisitorSerial.hpp"
    "Felide/Tasks/TaskNodeVisitorSerial.cpp"
    "Felide/Tasks/LogTask.hpp"
    "Felide/Tasks/LogTask.cpp"
    "Felide/Tasks/CommandTask.hpp"
    "Felide/Tasks/CommandTask.cpp"
)

set (src_felide_pom
	"Felide/POM/TargetAction.hpp"
    "Felide/POM/TargetAction.cpp"
	"Felide/POM/Target.hpp"
    "Felide/POM/Target.cpp"

	"Felide/POM/ModuleTarget.hpp"
    "Felide/POM/ModuleTarget.cpp"
	"Felide/POM/ModuleTargetType.hpp"
    "Felide/POM/ModuleTargetType.cpp"

    "Felide/POM/Project.hpp"
    "Felide/POM/Project.cpp"
    "Felide/POM/Source.hpp"
    "Felide/POM/Source.cpp"
    "Felide/POM/ProjectParser.hpp"
    "Felide/POM/ProjectParser.cpp"
    "Felide/POM/ProjectParserMock.hpp"
    "Felide/POM/ProjectParserMock.cpp"
    "Felide/POM/ProjectParserYaml.hpp"
    "Felide/POM/ProjectParserYaml.cpp"
)

set (src_felide_toolset
    "Felide/Toolsets/Compiler.hpp"
    "Felide/Toolsets/Compiler.cpp"
	"Felide/Toolsets/CompilerCpp.hpp"
    "Felide/Toolsets/CompilerCpp.cpp"
    "Felide/Toolsets/Linker.hpp"
    "Felide/Toolsets/Linker.cpp"
	"Felide/Toolsets/LinkerCpp.hpp"
    "Felide/Toolsets/LinkerCpp.cpp"
    "Felide/Toolsets/Toolset.hpp"
    "Felide/Toolsets/Toolset.cpp"
	"Felide/Toolsets/ToolsetCpp.hpp"
    "Felide/Toolsets/ToolsetCpp.cpp"
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

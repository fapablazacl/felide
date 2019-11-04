
set (target "felide.core")

set (sources_felide
    "felide/core/Predef.hpp"
    "felide/core/Core.hpp"
    "felide/core/Core.cpp"
    "felide/core/Version.hpp"
    "felide/core/Version.cpp"
    "felide/core/Language.hpp"
    "felide/core/Language.cpp"
    "felide/core/FileType.hpp"
    "felide/core/FileType.cpp"
    "felide/core/FileTypeRegistry.hpp"
    "felide/core/FileTypeRegistry.cpp"
    "felide/core/TreeNode.hpp"
    "felide/core/TreeNode.cpp"
) 

set (sources_felide_util
    "felide/core/util/FileService.cpp"
    "felide/core/util/FileService.hpp"
    "felide/core/util/FolderService.cpp"
    "felide/core/util/FolderService.hpp"
    "felide/core/util/OS.hpp"
    "felide/core/util/OS.cpp"
) 

set (sources_felide_tasks
    "felide/core/tasks/Task.hpp"
    "felide/core/tasks/Task.cpp"
    "felide/core/tasks/DirectoryTask.hpp"
    "felide/core/tasks/DirectoryTask.cpp"
    "felide/core/tasks/TaskNodeVisitor.hpp"
    "felide/core/tasks/TaskNodeVisitor.cpp"
    "felide/core/tasks/TaskNodeVisitorSerial.hpp"
    "felide/core/tasks/TaskNodeVisitorSerial.cpp"
    "felide/core/tasks/LogTask.hpp"
    "felide/core/tasks/LogTask.cpp"
    "felide/core/tasks/CommandTask.hpp"
    "felide/core/tasks/CommandTask.cpp"
) 

set (sources_felide_pom
    "felide/core/pom/TargetAction.hpp"
    "felide/core/pom/TargetAction.cpp"
    "felide/core/pom/Target.hpp"
    "felide/core/pom/Target.cpp"
    "felide/core/pom/ModuleTarget.hpp"
    "felide/core/pom/ModuleTarget.cpp"
    "felide/core/pom/ModuleTargetType.hpp"
    "felide/core/pom/ModuleTargetType.cpp"
    "felide/core/pom/Project.hpp"
    "felide/core/pom/Project.cpp"
    "felide/core/pom/Source.hpp"
    "felide/core/pom/Source.cpp"
    "felide/core/pom/ProjectParser.hpp"
    "felide/core/pom/ProjectParser.cpp"
    "felide/core/pom/ProjectParserMock.hpp"
    "felide/core/pom/ProjectParserMock.cpp"
    "felide/core/pom/ProjectParserJson.hpp"
    "felide/core/pom/ProjectParserJson.cpp"
    #"felide/core/pom/ProjectParserYaml.hpp"
    #"felide/core/pom/ProjectParserYaml.cpp"
) 

set (sources_felide_pom_models
    "felide/core/pom/models/PropertyImpl.hpp"
    "felide/core/pom/models/ProjectModel.hpp"
    "felide/core/pom/models/ProjectModel.cpp"
    "felide/core/pom/models/ModuleModel.hpp"
    "felide/core/pom/models/ModuleModel.cpp"
)

set (sources_felide_toolsets
    "felide/core/toolsets/ActionContext.hpp"
    "felide/core/toolsets/ActionContext.cpp"
    "felide/core/toolsets/Compiler.hpp"
    "felide/core/toolsets/Compiler.cpp"
    "felide/core/toolsets/Linker.hpp"
    "felide/core/toolsets/Linker.cpp"
    "felide/core/toolsets/Toolset.hpp"
    "felide/core/toolsets/Toolset.cpp"
) 

set (sources_felide_cpp
    "felide/core/cpp/ModuleCompiler.hpp"
    "felide/core/cpp/ModuleCompiler.cpp"
    "felide/core/cpp/ModuleLinker.hpp"
    "felide/core/cpp/ModuleLinker.cpp"
    "felide/core/cpp/ModuleToolset.hpp"
    "felide/core/cpp/ModuleToolset.cpp"
) 

set (sources_felide_system
    "felide/core/system/Plugin.hpp"
    "felide/core/system/Plugin.cpp"
    "felide/core/system/PluginManager.hpp"
    "felide/core/system/PluginManager.cpp"
    "felide/core/system/MessageBus.hpp"
    "felide/core/system/MessageBus.cpp"
    "felide/core/system/Component.hpp"
    "felide/core/system/Component.cpp"
)

source_group ("felide\\core"              FILES ${sources_felide})
source_group ("felide\\core\\util"        FILES ${sources_felide_util})
source_group ("felide\\core\\pom"         FILES ${sources_felide_pom})
source_group ("felide\\core\\pom\\models" FILES ${sources_felide_pom_models})
source_group ("felide\\core\\toolsets"    FILES ${sources_felide_toolsets})
source_group ("felide\\core\\tasks"       FILES ${sources_felide_tasks})
source_group ("felide\\core\\cpp"         FILES ${sources_felide_cpp})
source_group ("felide\\core\\system"      FILES ${sources_felide_system})

set (sources
    ${sources_felide}
    ${sources_felide_util}
    ${sources_felide_pom}
    ${sources_felide_pom_models}
    ${sources_felide_toolsets}
    ${sources_felide_tasks}
    ${sources_felide_cpp}
    ${sources_felide_system}
)

if (FELIDE_DYNAMIC_LINK)
	add_library (${target} SHARED ${sources})
else ()
    add_library (${target} ${sources})
endif()

target_compile_definitions (${target} PRIVATE "FELIDE_BUILD")

if (UNIX)
    set (DL_LIBRARY dl)
endif ()

target_link_libraries (
    ${target} 
    ${DL_LIBRARY}
    ${Boost_LIBRARIES}
)

install(TARGETS ${target} DESTINATION "lib")

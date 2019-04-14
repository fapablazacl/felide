
set (target "felide.core")

set (sources_felide
    "felide/Predef.hpp"
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
) 

set (sources_felide_util
    "felide/util/FileUtil.cpp"
    "felide/util/FileUtil.hpp"
    "felide/util/Strings.hpp"
    "felide/util/Strings.cpp"
    "felide/util/OS.hpp"
    "felide/util/OS.cpp"
) 

set (sources_felide_tasks
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

set (sources_felide_pom
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
    #"felide/pom/ProjectParserYaml.hpp"
    #"felide/pom/ProjectParserYaml.cpp"
) 

set (sources_felide_toolsets
    "felide/toolsets/ActionContext.hpp"
    "felide/toolsets/ActionContext.cpp"
    "felide/toolsets/Compiler.hpp"
    "felide/toolsets/Compiler.cpp"
    "felide/toolsets/Linker.hpp"
    "felide/toolsets/Linker.cpp"
    "felide/toolsets/Toolset.hpp"
    "felide/toolsets/Toolset.cpp"
) 

set (sources_felide_cpp
    "felide/cpp/ModuleCompiler.hpp"
    "felide/cpp/ModuleCompiler.cpp"
    "felide/cpp/ModuleLinker.hpp"
    "felide/cpp/ModuleLinker.cpp"
    "felide/cpp/ModuleToolset.hpp"
    "felide/cpp/ModuleToolset.cpp"
) 

set (sources_felide_ui
    "felide/ui/EditorModel.hpp"
    "felide/ui/EditorModel.cpp"
    "felide/ui/IDEFrameModel.hpp"
    "felide/ui/IDEFrameModel.cpp"
    "felide/ui/IDEFramePresenter.hpp"
    "felide/ui/IDEFramePresenter.cpp"
    "felide/ui/IDEFrame.hpp"
    "felide/ui/IDEFrame.cpp"
    "felide/ui/Menu.hpp"
    "felide/ui/Menu.cpp"
    "felide/ui/Editor.hpp"
    "felide/ui/Editor.cpp"
    "felide/ui/EditorManager.hpp"
    "felide/ui/EditorManager.cpp"
	"felide/ui/EditorManagerModel.hpp"
    "felide/ui/EditorManagerModel.cpp"
    "felide/ui/EditorManagerPresenter.hpp"
    "felide/ui/EditorManagerPresenter.cpp"
    "felide/ui/DialogManager.hpp"
    "felide/ui/DialogManager.cpp"
    "felide/ui/FolderBrowser.hpp"
    "felide/ui/FolderBrowser.cpp"
    "felide/ui/FolderBrowserPresenter.hpp"
    "felide/ui/FolderBrowserPresenter.cpp"
    "felide/ui/UIToolkit.hpp"
    "felide/ui/UIToolkit.cpp"
) 

set (sources_felide_system
    "felide/system/Plugin.hpp"
    "felide/system/Plugin.cpp"
    "felide/system/PluginManager.hpp"
    "felide/system/PluginManager.cpp"
)

source_group ("felide"              FILES ${sources_felide})
source_group ("felide\\util"        FILES ${sources_felide_util})
source_group ("felide\\pom"         FILES ${sources_felide_pom})
source_group ("felide\\toolsets"    FILES ${sources_felide_toolsets})
source_group ("felide\\tasks"       FILES ${sources_felide_tasks})
source_group ("felide\\cpp"         FILES ${sources_felide_cpp})
source_group ("felide\\ui"          FILES ${sources_felide_ui})
source_group ("felide\\system"      FILES ${sources_felide_system})

set (sources
    ${sources_felide}
    ${sources_felide_util}
    ${sources_felide_pom}
    ${sources_felide_toolsets}
    ${sources_felide_tasks}
    ${sources_felide_cpp}
    ${sources_felide_ui}
    ${sources_felide_system}
)

if (FELIDE_STATIC_LINK)
    add_library (${target} ${sources})
else ()
    add_library (${target} SHARED ${sources})
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

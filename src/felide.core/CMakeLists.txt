
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
	"felide/util/FileService.cpp"
    "felide/util/FileService.hpp"
	"felide/util/FolderService.cpp"
    "felide/util/FolderService.hpp"
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

set (sources_felide_ui_document
    "felide/ui/document/Document.hpp"
    "felide/ui/document/Document.cpp"
	"felide/ui/document/DocumentModel.hpp"
    "felide/ui/document/DocumentModel.cpp"
	"felide/ui/document/DocumentPresenter.hpp"
    "felide/ui/document/DocumentPresenter.cpp"
)

set (sources_felide_ui_documentmanager
    "felide/ui/document-manager/DocumentManager.hpp"
    "felide/ui/document-manager/DocumentManager.cpp"
	"felide/ui/document-manager/DocumentManagerModel.hpp"
    "felide/ui/document-manager/DocumentManagerModel.cpp"
    "felide/ui/document-manager/DocumentManagerPresenter.hpp"
    "felide/ui/document-manager/DocumentManagerPresenter.cpp"
)

set (sources_felide_ui_folderbrowser
    "felide/ui/folder-browser/FolderBrowser.hpp"
    "felide/ui/folder-browser/FolderBrowser.cpp"
    "felide/ui/folder-browser/FolderBrowserPresenter.hpp"
    "felide/ui/folder-browser/FolderBrowserPresenter.cpp"
	"felide/ui/folder-browser/FolderBrowserModel.hpp"
    "felide/ui/folder-browser/FolderBrowserModel.cpp"
)

set (sources_felide_ui_ideframe
    "felide/ui/ide-frame/IDEFrameModel.hpp"
    "felide/ui/ide-frame/IDEFrameModel.cpp"
    "felide/ui/ide-frame/IDEFramePresenter.hpp"
    "felide/ui/ide-frame/IDEFramePresenter.cpp"
    "felide/ui/ide-frame/IDEFrame.hpp"
    "felide/ui/ide-frame/IDEFrame.cpp"
)

set (sources_felide_ui_filesearchdialog
    "felide/ui/file-search-dialog/FileSearchDialogModel.hpp"
    "felide/ui/file-search-dialog/FileSearchDialogModel.cpp"
    "felide/ui/file-search-dialog/FileSearchDialogPresenter.hpp"
    "felide/ui/file-search-dialog/FileSearchDialogPresenter.cpp"
    "felide/ui/file-search-dialog/FileSearchDialog.hpp"
    "felide/ui/file-search-dialog/FileSearchDialog.cpp"
)

set (sources_felide_ui
	"felide/ui/DialogManager.hpp"
    "felide/ui/DialogManager.cpp"
    "felide/ui/Menu.hpp"
    "felide/ui/Menu.cpp"
    "felide/ui/MenuPanel.hpp"
    "felide/ui/MenuPanel.cpp"
    "felide/ui/FileFilter.hpp"
    "felide/ui/FileFilter.cpp"
    "felide/ui/UIToolkit.hpp"
    "felide/ui/UIToolkit.cpp"
) 

set (sources_felide_system
    "felide/system/Plugin.hpp"
    "felide/system/Plugin.cpp"
    "felide/system/PluginManager.hpp"
    "felide/system/PluginManager.cpp"
	"felide/system/MessageBus.hpp"
    "felide/system/MessageBus.cpp"
	"felide/system/Component.hpp"
    "felide/system/Component.cpp"
)

source_group ("felide"              FILES ${sources_felide})
source_group ("felide\\util"        FILES ${sources_felide_util})
source_group ("felide\\pom"         FILES ${sources_felide_pom})
source_group ("felide\\toolsets"    FILES ${sources_felide_toolsets})
source_group ("felide\\tasks"       FILES ${sources_felide_tasks})
source_group ("felide\\cpp"         FILES ${sources_felide_cpp})
source_group ("felide\\ui"          FILES ${sources_felide_ui})
source_group ("felide\\ui\\document"  			FILES ${sources_felide_ui_document})
source_group ("felide\\ui\\document-manager"	FILES ${sources_felide_ui_documentmanager})
source_group ("felide\\ui\\folder-browser"		FILES ${sources_felide_ui_folderbrowser})
source_group ("felide\\ui\\ide-frame"  			FILES ${sources_felide_ui_ideframe})
source_group ("felide\\ui\\file-search-dialog"  			FILES ${sources_felide_ui_filesearchdialog})

source_group ("felide\\system" FILES ${sources_felide_system})

set (sources
    ${sources_felide}
    ${sources_felide_util}
    ${sources_felide_pom}
    ${sources_felide_toolsets}
    ${sources_felide_tasks}
    ${sources_felide_cpp}
    ${sources_felide_ui}
	${sources_felide_ui_document}
	${sources_felide_ui_documentmanager}
	${sources_felide_ui_folderbrowser}
    ${sources_felide_ui_filesearchdialog}
	${sources_felide_ui_ideframe}
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

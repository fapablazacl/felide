
# setup borc-core
include_directories("../borc-core/")

set (target "borc-test")
set (sources 
    "Test.cpp"
)

set (sources_borc
    "borc/Version.Test.cpp"
    "borc/FileType.Test.cpp"
    "borc/FileTypeRegistry.Test.cpp"
    "borc/FileTypeRegistryImpl.Test.cpp"
)

set (sources_borc_tasks
    "borc/tasks/Task.Test.cpp"
    "borc/tasks/TaskNode.Test.cpp"
    "borc/tasks/TaskNodeVisitor.Test.cpp"
    "borc/tasks/TaskNodeVisitorSerial.Test.cpp"
    "borc/tasks/LogTask.Test.cpp"
    "borc/tasks/CommandTask.Test.cpp"
)

set (sources_borc_pom
    "borc/pom/Target.Test.cpp"
    "borc/pom/Project.Test.cpp"
    "borc/pom/Source.Test.cpp"
    "borc/pom/ProjectParser.Test.cpp"
    "borc/pom/ProjectParserMock.Test.cpp"
)

set (sources_borc_toolchains
    "borc/toolchains/Compiler.Test.cpp"
    "borc/toolchains/CompilerImpl.Test.cpp"
    "borc/toolchains/Linker.Test.cpp"
    "borc/toolchains/LinkerImpl.Test.cpp"
    "borc/toolchains/Toolchain.Test.cpp"
    "borc/toolchains/ToolchainImpl.Test.cpp"
    "borc/toolchains/ToolchainCpp.Test.cpp"
)

include_directories(${Boost_INCLUDE_DIRS})

source_group("\\"                   FILES ${sources})
source_group("\\borc"               FILES ${sources_borc})
source_group("\\borc\\tasks"        FILES ${sources_borc_tasks})
source_group("\\borc\\pom"          FILES ${sources_borc_pom})
source_group("\\borc\\toolchains"   FILES ${sources_borc_toolchains})

add_executable (${target} 
	${sources}
    ${sources_borc}
    ${sources_borc_tasks}
    ${sources_borc_cpp}
    ${sources_borc_toolchains}
)

target_link_libraries (
    ${target} 
    borc-core
    #yaml-cpp
    fmt
)

install(TARGETS ${target} DESTINATION "bin")


include_directories(.)

set (target "borc.cli")

set (sources_borc "borc/Main.cpp")

set (sources_borc_cli
	"borc/cli/CliController.hpp"
	"borc/cli/CliController.cpp"
)

set (sources_borc_core
	"borc/core/ProjectFactory.hpp"
	"borc/core/ProjectFactory.cpp"
	"borc/core/ServiceFactory.hpp"
	"borc/core/ServiceFactory.cpp"
	"borc/core/ServiceFactoryGCC.hpp"
	"borc/core/ServiceFactoryGCC.cpp"
	"borc/core/ServiceFactoryVC.hpp"
	"borc/core/ServiceFactoryVC.cpp"
	"borc/core/Toolchain.hpp"
	"borc/core/Toolchain.cpp"
	"borc/core/ToolchainFactory.hpp"
	"borc/core/ToolchainFactory.cpp"
)

set (sources_borc_dag
	"borc/dag/BuildGraphGenerator.hpp"
	"borc/dag/BuildGraphGenerator.cpp"
	"borc/dag/Node.hpp"
	"borc/dag/Node.cpp"
	"borc/dag/NodeRepository.hpp"
	"borc/dag/NodeRepository.cpp"
)

add_executable (${target} 
	${sources_borc} ${sources_borc_cli} ${sources_borc_core} ${sources_borc_dag}
)

target_link_libraries (${target} 
	borc.core 
	stdc++fs
)

install(TARGETS ${target} DESTINATION "bin")

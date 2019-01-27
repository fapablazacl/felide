
include_directories(.)

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set (target "borc.cli")

set (source_borc "Module.borc.json")

set (sources_borc "borc/Main.cpp")

set (sources_borc_cli
	"borc/cli/ProjectController.hpp"
	"borc/cli/ProjectController.cpp"
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

source_group(\\ FILES ${source_borc})
source_group(\\borc FILES ${sources_borc})
source_group(\\borc\\cli FILES ${sources_borc_cli})
source_group(\\borc\\core FILES ${sources_borc_core})
source_group(\\borc\\dag FILES ${sources_borc_dag})

add_executable (${target} 
	${source_borc} ${sources_borc} ${sources_borc_cli} ${sources_borc_core} ${sources_borc_dag}
)

if (NOT MSVC)
	set (stdcppfs "stdc++fs")
else()
	set (stdcppfs "")
endif()

target_link_libraries (${target} 
	borc.core
	${stdcppfs}
	${Boost_LIBRARIES}
)

install(TARGETS ${target} DESTINATION "bin")

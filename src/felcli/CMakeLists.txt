
set (target "felcli")

set (sources
	"Main.cpp"
)

set (felide_cli_sources
    "felide/cli/CliApplication.hpp"
    "felide/cli/CliApplication.cpp"
    "felide/cli/CliController.hpp"
    "felide/cli/CliController.cpp"
    "felide/cli/CompilerDetector.hpp"
    "felide/cli/CompilerDetector.cpp"
    "felide/cli/GnuCompilerDetector.hpp"
    "felide/cli/GnuCompilerDetector.cpp"
)

set (felide_cli_cmake_sources
    "felide/cli/cmake/CMakeProject.hpp"
    "felide/cli/cmake/CMakeProject.cpp"
    "felide/cli/cmake/CliCMakeController.hpp"
    "felide/cli/cmake/CliCMakeController.cpp"
)

source_group(\\ FILES ${sources})
source_group(\\felide\\cli FILES ${felide_cli_sources})
source_group(\\felide\\cli\\cmake FILES ${felide_cli_cmake_sources})

add_executable (
    ${target}
    ${sources}
    ${felide_cli_sources}
    ${felide_cli_cmake_sources}
)

if (UNIX)
    set (DL_LIBRARY dl pthread)
endif ()

target_link_libraries (
    ${target} 
    felide.core
    ${Boost_LIBRARIES}
    ${DL_LIBRARY}
)

install(TARGETS ${target} DESTINATION "bin")

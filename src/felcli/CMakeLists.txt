
set (target "felcli")
set (sources 
	"Main.cpp"
    "felide/cli/cmake/CMakeProject.hpp"
	"felide/cli/cmake/CMakeProject.cpp"
    "felide/cli/cmake/CliCMakeController.hpp"
	"felide/cli/cmake/CliCMakeController.cpp"
    "felide/cli/CliApplication.hpp"
	"felide/cli/CliApplication.cpp"
	"felide/cli/CliController.hpp"
	"felide/cli/CliController.cpp"
    "felide/cli/CompilerDetector.hpp"
	"felide/cli/CompilerDetector.cpp"
    "felide/cli/GnuCompilerDetector.hpp"
	"felide/cli/GnuCompilerDetector.cpp"
)

add_executable (${target} ${sources})

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

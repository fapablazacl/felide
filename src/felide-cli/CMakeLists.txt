
set (target "felide-cli")
set (sources 
	"Main.cpp"
    "felide/cli/CliApplication.hpp"
	"felide/cli/CliApplication.cpp"
	"felide/cli/CliController.hpp"
	"felide/cli/CliController.cpp"
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

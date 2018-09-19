
set (target "felide-cli")
set (sources 
	"Main.cpp"
    "felide/cli/CliApplication.hpp"
	"felide/cli/CliApplication.cpp"
	"felide/cli/CliController.hpp"
	"felide/cli/CliController.cpp"
)

add_executable (${target} ${sources})

target_link_libraries (
    ${target} 
    felide.core
    fmt
    stdc++fs
)

install(TARGETS ${target} DESTINATION "bin")

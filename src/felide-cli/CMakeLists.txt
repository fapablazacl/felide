
set (target "felide-cli")
set (sources 
	"Main.cpp"
	"CliController.hpp"
	"CliController.cpp"
)

source_group("\\" FILES ${sources})

add_executable (${target} ${sources})

target_link_libraries (
    ${target} 
    felide.core
    yaml-cpp
    fmt
    stdc++fs
)

install(TARGETS ${target} DESTINATION "bin")

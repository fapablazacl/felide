
include_directories("../Felide.Core/")

set (target "Felide.Console")
set (sources 
	"Main.cpp"
	"ConsoleApp.hpp"
	"ConsoleApp.cpp"
)

source_group("\\" FILES ${sources})

add_executable (${target} ${sources})

target_link_libraries (
    ${target} 
    Felide.Core
    yaml-cpp
    fmt
)

install(TARGETS ${target} DESTINATION "bin")

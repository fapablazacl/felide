
set (target "felide.sandbox")

set (sources 
    # "sandbox.cpp"
    "iddde.cpp"
	"Common.cpp" 
	"Common.hpp"
	"BuildService.cpp" 
	"BuildService.hpp" 
	"RunService.cpp" 
	"RunService.hpp" 
	"Command.cpp" 
	"Command.hpp" 
	"CommandFactory.cpp" 
	"CommandFactory.hpp" 
	"Compiler.cpp" 
	"Compiler.hpp" 
	"Linker.cpp" 
	"Linker.hpp" 
	"Module.cpp" 
	"Module.hpp" 
	"Project.cpp" 
	"Project.hpp" 
	"SystemCommand.cpp" 
	"SystemCommand.hpp" 
)

add_executable (${target} ${sources})

# target_link_libraries (${target} stdc++fs)

install(TARGETS ${target} DESTINATION "bin")

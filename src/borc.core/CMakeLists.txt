
set (target "borc.core")

set (sources 
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
	"SystemCommand.cpp" 
	"SystemCommand.hpp" 
	"ProcessCommand.cpp" 
	"ProcessCommand.hpp" 
	"Compiler.cpp" 
	"Compiler.hpp" 
	"Linker.cpp" 
	"Linker.hpp" 
	"Module.cpp" 
	"Module.hpp" 
	"Project.cpp" 
	"Project.hpp" 
	"win32/ProcessRedirector.cpp" 
	"win32/ProcessRedirector.hpp" 
)

add_library (${target} ${sources})

# target_link_libraries (${target} stdc++fs)

install(TARGETS ${target} DESTINATION "bin")

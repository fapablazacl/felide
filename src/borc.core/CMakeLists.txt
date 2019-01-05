
set (target "borc.core")

add_definitions(-DBORC_BUILD)

set (sources 
	"Predef.h"
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
	# "ProcessCommand.cpp" 
	# "ProcessCommand.hpp" 
	# "win32/ProcessRedirector.cpp" 
	# "win32/ProcessRedirector.hpp" 
	"SystemCommand.cpp" 
	"SystemCommand.hpp" 
	"Compiler.cpp" 
	"Compiler.hpp" 
	"Linker.cpp" 
	"Linker.hpp" 

	"Source.cpp" 
	"Source.hpp" 
	"Module.cpp" 
	"Module.hpp" 
	"Project.cpp" 
	"Project.hpp" 
)

add_library (${target} ${sources})

# target_link_libraries (${target} stdc++fs)

install(TARGETS ${target} DESTINATION "bin")

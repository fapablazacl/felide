
set (target "borc.core")

add_definitions(-DBORC_BUILD)

set (sources 
	"borc/core/Predef.h"
	"borc/core/Common.cpp" 
	"borc/core/Common.hpp"
	"borc/core/BuildService.cpp" 
	"borc/core/BuildService.hpp" 
	"borc/core/RunService.cpp" 
	"borc/core/RunService.hpp" 
	"borc/core/Command.cpp" 
	"borc/core/Command.hpp" 
	"borc/core/CommandFactory.cpp" 
	"borc/core/CommandFactory.hpp" 
	# "borc/core/ProcessCommand.cpp" 
	# "borc/core/ProcessCommand.hpp" 
	# "borc/core/win32/ProcessRedirector.cpp" 
	# "borc/core/win32/ProcessRedirector.hpp" 
	"borc/core/SystemCommand.cpp" 
	"borc/core/SystemCommand.hpp" 
	"borc/core/Compiler.cpp" 
	"borc/core/Compiler.hpp" 
	"borc/core/Linker.cpp" 
	"borc/core/Linker.hpp" 
	"borc/core/Source.cpp" 
	"borc/core/Source.hpp" 
	"borc/core/Module.cpp" 
	"borc/core/Module.hpp" 
	"borc/core/Project.cpp" 
	"borc/core/Project.hpp" 
	"borc/core/FileUtil.hpp" 
	"borc/core/FileUtil.cpp" 
)

source_group(\\borc\\core FILES ${sources})

add_library (${target} ${sources})

target_link_libraries(${target} ${Boost_LIBRARIES})

install(TARGETS ${target} DESTINATION "bin")

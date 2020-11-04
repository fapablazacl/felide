
set (target "felide.core")

set (sources_felide
    "felide/core/Predef.hpp"
    "felide/core/Version.hpp"
    "felide/core/Version.cpp"
) 

set (sources_felide_util
    "felide/core/util/FileService.cpp"
    "felide/core/util/FileService.hpp"
    "felide/core/util/FolderService.cpp"
    "felide/core/util/FolderService.hpp"
    "felide/core/util/OS.hpp"
    "felide/core/util/OS.cpp"
) 

source_group ("felide\\core"              FILES ${sources_felide})
source_group ("felide\\core\\util"        FILES ${sources_felide_util})

set (sources
    ${sources_felide}
    ${sources_felide_util}
)

if (FELIDE_DYNAMIC_LINK)
	add_library (${target} SHARED ${sources})
else ()
    add_library (${target} ${sources})
endif()

target_compile_definitions (${target} PRIVATE "FELIDE_BUILD")

if (UNIX)
    set (DL_LIBRARY dl)
endif ()

target_link_libraries (
    ${target} 
    ${DL_LIBRARY}
    ${Boost_LIBRARIES}
)

install(TARGETS ${target} DESTINATION "lib")

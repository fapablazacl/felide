
set (target "felide.core")

set (sources_felide
    "felide/core/Predef.hpp"
    "felide/core/Version.hpp"
    "felide/core/Version.cpp"
    "felide/core/FileService.cpp"
    "felide/core/FileService.hpp"
    "felide/core/FolderService.cpp"
    "felide/core/FolderService.hpp"
    "felide/core/OS.hpp"
    "felide/core/OS.cpp"
) 

source_group ("felide\\core" FILES ${sources_felide})

set (sources
    ${sources_felide}
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

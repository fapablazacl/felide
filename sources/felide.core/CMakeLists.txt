
set (target "felide.core")

set (sources
    "include/felide/core/Predef.hpp"
    "include/felide/core/Version.hpp"
    "include/felide/core/FileService.hpp"
    "include/felide/core/FolderService.hpp"
    "include/felide/core/OS.hpp"

    "src/OS.cpp"
    "src/FolderService.cpp"
    "src/Version.cpp"
    "src/FileService.cpp"
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

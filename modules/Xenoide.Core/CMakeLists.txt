
set (target "Xenoide.Core")

set (sources
    "include/Xenoide/Core/Predef.hpp"
    "include/Xenoide/Core/Version.hpp"
    "include/Xenoide/Core/FileService.hpp"
    "include/Xenoide/Core/FolderService.hpp"
    "include/Xenoide/Core/OS.hpp"

    "src/OS.cpp"
    "src/FolderService.cpp"
    "src/Version.cpp"
    "src/FileService.cpp"
) 

if (XENOIDE_DYNAMIC_LINK)
	add_library (${target} SHARED ${sources})
else ()
    add_library (${target} ${sources})
endif()

target_include_directories( ${target} PUBLIC "include/")
target_compile_definitions (${target} PRIVATE "XENOIDE_BUILD")

if (UNIX)
    set (DL_LIBRARY dl)
endif ()

target_link_libraries (
    ${target} 
    ${DL_LIBRARY}
    ${Boost_LIBRARIES}
)

install(TARGETS ${target} DESTINATION "lib")


set (target "felide.sandbox")
set (sources 
    "sandbox.cpp"
    "ProjectFile.cpp"
    "ProjectFile.hpp"
    "Project.cpp"
    "Project.hpp"
    "Workspace.cpp"
    "Workspace.hpp"
)

add_executable (${target} ${sources})

target_link_libraries (${target}     
    felide.core
    yaml-cpp
    fmt
    stdc++fs
)

install(TARGETS ${target} DESTINATION "bin")

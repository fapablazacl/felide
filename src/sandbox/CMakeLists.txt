
set (target "sandbox")
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

#target_link_libraries (${target} felide.core stdc++fs)

install(TARGETS ${target} DESTINATION "bin")

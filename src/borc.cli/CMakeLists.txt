
set (target "borc.cli")
set (sources "Main.cpp")

add_executable (${target} ${sources})

target_link_libraries (${target} borc.core stdc++fs)

install(TARGETS ${target} DESTINATION "bin")

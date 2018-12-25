
set (target "felide.sandbox")

set (sources 
    "sandbox.cpp"
)

add_executable (${target} ${sources})

# target_link_libraries (${target} stdc++fs)

install(TARGETS ${target} DESTINATION "bin")

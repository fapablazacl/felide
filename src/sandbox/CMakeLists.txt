
set (target "felide.sandbox")
set (sources 
    # "sandbox.cpp"
    "iddde.cpp"
)

add_executable (${target} ${sources})

target_link_libraries (${target}     
    felide.core stdc++fs
)

install(TARGETS ${target} DESTINATION "bin")


set (target "felide")

set (src_felide
    "Main.cpp"
)

add_executable(${target} WIN32
    ${src_felide}
)

target_link_libraries (
    ${target} 
    felide.core
)

install(TARGETS ${target} DESTINATION "bin")


set (target "felide")

set (sources
    "src/main.cpp"
)

add_executable(${target} WIN32
    ${sources}
)

target_link_libraries (
    ${target} 
    felide.core
    felide.gui.qt5
)

install(TARGETS ${target} DESTINATION "bin")

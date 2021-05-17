
set (target "Xenoide")

set (sources
    "src/main.cpp"
)

add_executable(${target} WIN32
    ${sources}
)

target_link_libraries (
    ${target} 
    Xenoide.Core
    Xenoide.Gui.Qt5
)

install(TARGETS ${target} DESTINATION "bin")

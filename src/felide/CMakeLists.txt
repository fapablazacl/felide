
set (target "felide")

set (src
    "main.cpp"
)

add_executable(${target} WIN32
    ${src}
)

target_link_libraries (
    ${target} 
    felide.core
    felide.gui.qt5
)

source_group ("" FILES ${src})

install(TARGETS ${target} DESTINATION "bin")

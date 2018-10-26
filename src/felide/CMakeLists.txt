
set (target "felide")

set (srcs
    "Main.cpp"
    "WinMain.cpp"
)

add_executable(${target} WIN32
    ${srcs}
)

target_link_libraries (
    ${target} 
    felide.core
)

source_group ("" FILES ${srcs})

install(TARGETS ${target} DESTINATION "bin")

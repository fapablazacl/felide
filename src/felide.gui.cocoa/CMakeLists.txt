
set (target felide.gui.cocoa)

set (sources Main.mm)

add_executable(${target} MACOSX_BUNDLE ${sources})

target_link_libraries(${target} "-framework Cocoa")

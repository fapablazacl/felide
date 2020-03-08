
set(MAIN_NIBFILE "MainMenu")
set(PRINCIPAL_CLASS "NSApplication")

set (target felide.gui.cocoa)

set (sources 
    main.m
    AppDelegate.h
    AppDelegate.m
)

add_executable(${target} MACOSX_BUNDLE ${sources})
set_target_properties(${target} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/src/felide.gui.cocoa/Info.plist"
)

target_link_libraries(${target} "-framework Cocoa")

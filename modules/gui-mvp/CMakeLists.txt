
set (target "gui-mvp")
set (sources
    "include/Xenoide/GUI/mvp/MainFrame.hpp"
	"include/Xenoide/GUI/mvp/DocumentManager.hpp"
	"include/Xenoide/GUI/mvp/Document.hpp"
	"include/Xenoide/GUI/mvp/FindReplace.hpp"

    "src/MainFrame.cpp"
    "src/DocumentManager.cpp"
    "src/Document.cpp"
    "src/FindReplace.cpp"
)

add_library (${target} ${sources})

target_include_directories(${target} PUBLIC "include")

target_link_libraries (
    ${target} 
    ${DL_LIBRARY}
    ${Boost_LIBRARIES}
    Xenoide.Core
	Xenoide.GUI
)

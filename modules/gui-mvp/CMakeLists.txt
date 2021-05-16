
set (target "gui-mvp")
set (sources
    "Xenoide/gui/mvp/MainFrame.hpp"
    "Xenoide/gui/mvp/MainFrame.cpp"
    "Xenoide/gui/mvp/DocumentManager.hpp"
    "Xenoide/gui/mvp/DocumentManager.cpp"
    "Xenoide/gui/mvp/Document.hpp"
    "Xenoide/gui/mvp/Document.cpp"
    "Xenoide/gui/mvp/FindReplace.hpp"
    "Xenoide/gui/mvp/FindReplace.cpp"
)

add_library (${target} ${sources})

target_link_libraries (
    ${target} 
    ${DL_LIBRARY}
    ${Boost_LIBRARIES}
    Xenoide.Core
	Xenoide.GUI
)

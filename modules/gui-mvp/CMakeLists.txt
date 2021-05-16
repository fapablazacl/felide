
set (target "gui-mvp")
set (sources
    "Xenoide/GUI/mvp/MainFrame.hpp"
    "Xenoide/GUI/mvp/MainFrame.cpp"
    "Xenoide/GUI/mvp/DocumentManager.hpp"
    "Xenoide/GUI/mvp/DocumentManager.cpp"
    "Xenoide/GUI/mvp/Document.hpp"
    "Xenoide/GUI/mvp/Document.cpp"
    "Xenoide/GUI/mvp/FindReplace.hpp"
    "Xenoide/GUI/mvp/FindReplace.cpp"
)

add_library (${target} ${sources})

target_link_libraries (
    ${target} 
    ${DL_LIBRARY}
    ${Boost_LIBRARIES}
    Xenoide.Core
	Xenoide.GUI
)

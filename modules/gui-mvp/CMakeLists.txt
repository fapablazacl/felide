
set (target "gui-mvp")
set (sources
    "felide/gui/mvp/MainFrame.hpp"
    "felide/gui/mvp/MainFrame.cpp"
    "felide/gui/mvp/DocumentManager.hpp"
    "felide/gui/mvp/DocumentManager.cpp"
    "felide/gui/mvp/Document.hpp"
    "felide/gui/mvp/Document.cpp"
    "felide/gui/mvp/FindReplace.hpp"
    "felide/gui/mvp/FindReplace.cpp"
)

add_library (${target} ${sources})

target_link_libraries (
    ${target} 
    ${DL_LIBRARY}
    ${Boost_LIBRARIES}
    Xenoide.Core
	Xenoide.GUI
)

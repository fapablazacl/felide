
set (target "felide")

set (src_felide
    "Main.cpp"

    "felide/ui/EditorModel.hpp"
    "felide/ui/EditorModel.cpp"
    "felide/ui/MainWindowModel.hpp"
    "felide/ui/MainWindowModel.cpp"
    "felide/ui/MainWindowPresenter.hpp"
    "felide/ui/MainWindowPresenter.cpp"
    "felide/ui/MainWindowView.hpp"
    "felide/ui/MainWindowView.cpp"
    "felide/ui/Menu.hpp"
    "felide/ui/Menu.cpp"
    "felide/ui/EditorView.hpp"
    "felide/ui/EditorView.cpp"
    "felide/ui/EditorManagerView.hpp"
    "felide/ui/EditorManagerView.cpp"
    "felide/ui/DialogManagerView.hpp"
    "felide/ui/DialogManagerView.cpp"
    "felide/ui/FolderBrowserView.hpp"
    "felide/ui/FolderBrowserView.cpp"
)

add_executable(${target} WIN32
    ${src_felide}
)

target_link_libraries (
    ${target} 
    felide.core
)

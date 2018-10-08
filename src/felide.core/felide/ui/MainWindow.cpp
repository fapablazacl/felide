
#include "MainWindow.hpp"

#include "MainWindowPresenter.hpp"
#include "Menu.hpp"

namespace felide {
    MainWindow::MainWindow(MainWindowPresenter *presenter) {
        m_presenter = presenter;

        m_menu = new Menu(Menu::menuBar({
            Menu::menu("&File", {
                Menu::action([this] () { m_presenter->fileNewTriggered(); }, "&New", {Modifier::Ctrl, Key::N}),
                Menu::separator(),
                Menu::action([this] () { m_presenter->fileOpenTriggered(); }, "&Open ...", {Modifier::Ctrl, Key::O}),
                Menu::action([this] () { m_presenter->fileOpenFolderTriggered(); }, "Open &Folder ...", {Modifier::CtrlShift, Key::O}),
                Menu::separator(),
                Menu::action([this] () { m_presenter->fileSaveTriggered(); }, "&Save", {Modifier::Ctrl, Key::S}),
                Menu::action([this] () { m_presenter->fileSaveAsTriggered(); }, "Sa&ve As ..."),
                Menu::action([this] () { m_presenter->fileSaveAllTriggered(); }, "Save &All"),
                Menu::separator(),
                Menu::action([this] () { m_presenter->fileCloseTriggered(); }, "&Close"),
                Menu::separator(),
                Menu::action([this] () { m_presenter->fileExitTriggered(); }, "&Exit")
            }),
            Menu::menu("&Edit", {
                Menu::action([this] () { m_presenter->editUndo(); }, "&Undo", {Modifier::Ctrl, Key::Z}),
                Menu::action([this] () { m_presenter->editRedo(); }, "&Redo", {Modifier::CtrlShift, Key::Z}),
                Menu::separator(),
                Menu::action([this] () { m_presenter->editCut(); }, "&Cut", {Modifier::Ctrl, Key::X}),
                Menu::action([this] () { m_presenter->editCopy(); }, "C&opy", {Modifier::Ctrl, Key::C}),
                Menu::action([this] () { m_presenter->editPaste(); }, "&Paste", {Modifier::Ctrl, Key::V}),
                Menu::separator(),
                Menu::action([] () {}, "Find ..."),
                Menu::action([] () {}, "Replace ..."),
            }),
            Menu::menu("&View", {
                Menu::action([] () {}, "&Output"), 
                Menu::action([] () {}, "&Workspace")
            }),
            Menu::menu("&Build", {
                Menu::action([] () {}, "&Clean"),
                Menu::action([] () {}, "&Execute")
            }),
            Menu::menu("&Help", {
                Menu::action([] () {}, "&About", {Key::F1})
            }),
        }));
    }

    MainWindow::~MainWindow() {
        delete m_menu;
    }
}


#include "IDEFrame.hpp"

#include "IDEFrameController.hpp"

#include <felide/ui/Menu.hpp>

namespace felide {
    IDEFrame::IDEFrame(IDEFrameController *presenter) {
        m_presenter = presenter;

        m_menu = new Menu(Menu::menuBar({
            Menu::menu("&File", {
                Menu::action([this] () { m_presenter->onFileNew(); }, "&New", {Modifier::Ctrl, Key::N}),
                Menu::separator(),
                Menu::action([this] () { m_presenter->onFileOpen(); }, "&Open ...", {Modifier::Ctrl, Key::O}),
                Menu::action([this] () { m_presenter->onFileOpenFolder(); }, "Open &Folder ...", {Modifier::CtrlShift, Key::O}),
                Menu::separator(),
                Menu::action([this] () { m_presenter->onFileSave(); }, "&Save", {Modifier::Ctrl, Key::S}),
                Menu::action([this] () { m_presenter->onFileSaveAs(); }, "Sa&ve As ..."),
                Menu::action([this] () { m_presenter->onFileSaveAll(); }, "Save &All"),
                Menu::separator(),
                Menu::action([this] () { m_presenter->onFileClose(); }, "&Close"),
                Menu::separator(),
                Menu::action([this] () { m_presenter->onFileExit(); }, "&Exit")
            }),
            Menu::menu("&Edit", {
                Menu::action([this] () { m_presenter->onEditUndo(); }, "&Undo", {Modifier::Ctrl, Key::Z}),
                Menu::action([this] () { m_presenter->onEditRedo(); }, "&Redo", {Modifier::CtrlShift, Key::Z}),
                Menu::separator(),
                Menu::action([this] () { m_presenter->onEditCut(); }, "&Cut", {Modifier::Ctrl, Key::X}),
                Menu::action([this] () { m_presenter->onEditCopy(); }, "C&opy", {Modifier::Ctrl, Key::C}),
                Menu::action([this] () { m_presenter->onEditPaste(); }, "&Paste", {Modifier::Ctrl, Key::V}),
                Menu::separator(),
                Menu::action([] () {}, "Find ..."),
                Menu::action([] () {}, "Replace ..."),
            }),
            Menu::menu("&View", {
                Menu::action([this] () { m_presenter->onViewFolderBrowser(); }, "&Folder Browser")
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

    IDEFrame::~IDEFrame() {
        delete m_menu;
    }
}

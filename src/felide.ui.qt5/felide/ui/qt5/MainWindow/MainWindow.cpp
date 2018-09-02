
#include "MainWindow.hpp"

#include <vector>
#include <functional>
#include "MainWindowPresenter.hpp"

namespace felide {
    static void setupMenu(QMenu *parentMenuPtr, const Menu &menu) {
        switch (menu.kind) {
            case MenuKind::SubMenu: {
                QMenu *menuPtr = parentMenuPtr->addMenu(menu.text.c_str());

                for (const Menu &childMenu : menu.childs) {
                    setupMenu(menuPtr, childMenu);
                }

                break;
            }

            case MenuKind::Action: {
                auto action = parentMenuPtr->addAction(menu.text.c_str(), nullptr, nullptr, QKeySequence(menu.shortcut.c_str()));

                if (menu.callback) {
                    QObject::connect(action, &QAction::triggered, menu.callback);
                }

                break;
            }

            case MenuKind::Separator: {
                parentMenuPtr->addSeparator();
                break;
            }
        }
    }

    static QMenuBar* createMenuBar(QWidget *parent, const Menu &menuBar) {
        auto menuBarPtr = new QMenuBar(parent);

        for (const Menu &menu : menuBar.childs) {
            QMenu *menuPtr = menuBarPtr->addMenu(menu.text.c_str());

            for (const Menu &childMenu : menu.childs) {
                setupMenu(menuPtr, childMenu);
            }
        }

        return menuBarPtr;
    }

    MainWindow::MainWindow() {
        presenter.attachView(this);

        this->setupMenuBar();
    }

    void MainWindow::setupMenuBar() {
        auto mainMenu = Menu::menuBar({
            Menu::menu("&File", {
                Menu::action([this] () { presenter.fileNew(); }, "&New", "Ctrl+N"),
                Menu::action([this] () { presenter.fileOpen(); }, "&Open"),
                Menu::action([this] () { presenter.fileSave(); }, "&Save"),
                Menu::action([this] () { presenter.fileSaveAs(); }, "Sa&ve As"),
                Menu::action([this] () { presenter.fileSaveAll(); }, "Save &All"),
                Menu::action([this] () { presenter.fileClose(); }, "&Close"),
                Menu::action([this] () { presenter.fileExit(); }, "&Exit")
            }),
            Menu::menu("&Edit", {
                Menu::action([] () {}, "&Undo"),
                Menu::action([] () {}, "&Redo"),
                Menu::action([] () {}, "&Cut"),
                Menu::action([] () {}, "C&opy"),
                Menu::action([] () {}, "&Paste")
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
                Menu::action([] () {}, "&About", "F1")
            }),
        });

        this->setMenuBar(createMenuBar(this, mainMenu));
    }
}

namespace felide {
    std::optional<std::string> MainWindow::openFileDialog(const FileDialogViewData &fileDialogData) {
        return nullptr;
    }

    std::optional<std::string> MainWindow::saveFileDialog(const FileDialogViewData &fileDialogData) {
        return nullptr;
    }

    EditorView* MainWindow::appendEditor() {
        return nullptr;
    }

    void MainWindow::removeEditor(const std::string &fileKey) {

    }

    std::map<std::string, EditorView*> MainWindow::getEditor(const std::string &fileKey) {
        return {};
    }

    EditorView* MainWindow::getCurrentEditor() {
        return nullptr;
    }
}

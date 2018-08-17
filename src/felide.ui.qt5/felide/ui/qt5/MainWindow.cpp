
#include "MainWindow.hpp"

#include <vector>

namespace felide {
    enum class MenuKind {
        SubMenu,
        Action,
        Separator
    };

    struct Menu {
        std::string text;
        std::string shortcut;
        std::vector<Menu> childs;
        MenuKind kind;

        static Menu menuBar(const std::vector<Menu> &childs) {
            Menu menu;

            menu.childs = childs;
            menu.kind = MenuKind::SubMenu;

            return menu;
        }

        static Menu menu(const std::string &text, const std::vector<Menu> &childs) {
            Menu menu;

            menu.text = text;
            menu.childs = childs;
            menu.kind = MenuKind::SubMenu;
            
            return menu;
        }

        static Menu action(const std::string &text, const std::string &shortcut="") {
            Menu menu;

            menu.text = text;
            menu.shortcut = shortcut;
            menu.kind = MenuKind::Action;

            return menu;
        }

        static Menu separator() {
            Menu menu;

            menu.kind = MenuKind::Separator;

            return menu;
        }
    };

    void setupMenu(QMenu *parentMenuPtr, const Menu &menu) {
        switch (menu.kind) {
            case MenuKind::SubMenu: {
                QMenu *menuPtr = parentMenuPtr->addMenu(menu.text.c_str());

                for (const Menu &childMenu : menu.childs) {
                    setupMenu(menuPtr, childMenu);
                }

                break;
            }

            case MenuKind::Action: {
                parentMenuPtr->addAction(menu.text.c_str(), nullptr, nullptr, QKeySequence(menu.shortcut.c_str()));
                break;
            }

            case MenuKind::Separator: {
                parentMenuPtr->addSeparator();
                break;
            }
        }
    }

    QMenuBar* createMenuBar(QWidget *parent, const Menu &menuBar) {
        auto menuBarPtr = new QMenuBar(parent);

        for (const Menu &menu : menuBar.childs) {
            QMenu *menuPtr = menuBarPtr->addMenu(menu.text.c_str());

            for (const Menu &childMenu : menu.childs) {
                setupMenu(menuPtr, childMenu);
            }
        }

        return menuBarPtr;
    }
    
    auto menuBar = Menu::menuBar({
        Menu::menu("&File", {
            Menu::action("&New", "Ctrl+N"),
            Menu::action("&Open"),
            Menu::action("&Save"),
            Menu::action("Sa&ve As"),
            Menu::action("Save &All"),
            Menu::action("&Close"),
            Menu::action("&Exit")
        }),
        Menu::menu("&Edit", {
            Menu::action("&Undo"),
            Menu::action("&Redo"),
            Menu::action("&Cut"),
            Menu::action("C&opy"),
            Menu::action("&Paste")
        }),
        Menu::menu("&View", {
            Menu::action("&Output"), 
            Menu::action("&Workspace")
        }),
        Menu::menu("&Build", {
            Menu::action("&Clean"),
            Menu::action("&Execute")
        }),
        Menu::menu("&Help", {
            Menu::action("&About", "F1")
        }),
    });

    MainWindow::MainWindow() {
        this->setupMenuBar();
    }

    void MainWindow::setupMenuBar() {
        this->setMenuBar(createMenuBar(this, felide::menuBar));
    }    
}
